import torch.nn as nn
import torch.optim as optim
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.widgets import Button
import matplotlib.animation as animation
import heapq

# Ensure the interactive backend is set
plt.ion()
matplotlib.use('TkAgg')

# Define the Q-learning parameters
alpha = 0.5  # Increased learning rate
gamma = 0.99  # Increased discount factor
epsilon = 1.0  # Starting exploration rate
epsilon_min = 0.25  # Minimum exploration rate
epsilon_decay = 0.95  # Decay rate for exploration rate
q_table = {}

# Prioritized Experience Replay (PER) parameters
buffer_size = 10000
batch_size = 64
alpha_per = 0.6  # How much prioritization is used (0 - no prioritization, 1 - full prioritization)
beta_start = 0.4  # Importance sampling weight
beta_increment = 0.001
replay_buffer = []


# Initialize the Q-table
def initialize_q_table(grid_size, num_actions):
    for x in range(grid_size):
        for y in range(grid_size):
            for action in range(num_actions):
                q_table[((x, y), action)] = 0


# Define the neural network model
class MTSPNet(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(MTSPNet, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        out = self.fc1(x)
        out = self.relu(out)
        out = self.fc2(out)
        return out


# Initialize the model, loss function, and optimizer
input_size = 10  # Example input size
hidden_size = 50
output_size = 10  # Example output size (number of cities)

model = MTSPNet(input_size, hidden_size, output_size)
criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

# Example grid world setup
grid_size = 10
num_actions = 4  # Up, Down, Left, Right
world_number = 1

# Initialize the Q-table
initialize_q_table(grid_size, num_actions)

# Initial number of cities and salesmen
num_salesmen = 4
num_cities = 5

# Generate fixed positions for cities
cities_positions = np.random.randint(0, grid_size, (num_cities, 2))

# Generate random initial positions for salesmen
salesmen_positions = np.random.randint(0, grid_size, (num_salesmen, 2))

# Initialize visit tracking and rewards
visit_counts = np.zeros((num_cities, num_salesmen))
agents_visited_cities = np.zeros(num_salesmen)
agents_last_position = np.zeros((num_salesmen, 2), dtype=int)
agents_visited_squares = [set() for _ in range(num_salesmen)]
agent_moves = np.zeros(num_salesmen, dtype=int)

# Define the corner (bottom right) for agents to move to after finishing their task
finish_corner = (grid_size - 1, grid_size - 1)


# Q-learning function to choose an action
def choose_action(state):
    global epsilon
    if np.random.uniform(0, 1) < epsilon:
        action = np.random.choice(num_actions)
    else:
        q_values = [q_table[(state, a)] for a in range(num_actions)]
        action = np.argmax(q_values)
    return action


# Q-learning function to update the Q-table
def update_q_table(state, action, reward, next_state):
    td_target = reward + gamma * max([q_table[(next_state, a)] for a in range(num_actions)])
    td_error = td_target - q_table[(state, action)]
    q_table[(state, action)] += alpha * td_error
    return abs(td_error)


# Replay buffer functions
def add_to_replay_buffer(state, action, reward, next_state, done):
    td_error = update_q_table(state, action, reward, next_state)
    priority = (abs(td_error) + 1e-5) ** alpha_per
    if len(replay_buffer) < buffer_size:
        heapq.heappush(replay_buffer, (-priority, (state, action, reward, next_state, done)))
    else:
        heapq.heappushpop(replay_buffer, (-priority, (state, action, reward, next_state, done)))


def sample_from_replay_buffer():
    priorities, experiences = zip(*heapq.nlargest(batch_size, replay_buffer))
    total = sum(-p for p in priorities)
    sampling_probabilities = [-p / total for p in priorities]
    return experiences, sampling_probabilities


def update_positions():
    global salesmen_positions

    new_positions = salesmen_positions.copy()
    for i in range(len(salesmen_positions)):
        if agents_visited_cities[i] < 2:  # Agent should visit two unique cities first
            state = tuple(salesmen_positions[i])
            action = choose_action(state)
            if action == 0:  # Up
                new_positions[i, 1] = max(0, salesmen_positions[i, 1] - 1)
            elif action == 1:  # Down
                new_positions[i, 1] = min(grid_size - 1, salesmen_positions[i, 1] + 1)
            elif action == 2:  # Left
                new_positions[i, 0] = max(0, salesmen_positions[i, 0] - 1)
            elif action == 3:  # Right
                new_positions[i, 0] = min(grid_size - 1, salesmen_positions[i, 0] + 1)
            next_state = tuple(new_positions[i])
            reward = calculate_reward(i, salesmen_positions[i], next_state)
            done = check_objective()
            add_to_replay_buffer(state, action, reward, next_state, done)
            agents_last_position[i] = new_positions[i]
            agents_visited_squares[i].add(tuple(new_positions[i]))
            agent_moves[i] += 1
        else:  # Agent should move to the bottom right corner
            new_positions[i] = move_to_corner(salesmen_positions[i])
    salesmen_positions = new_positions


def move_to_corner(current_position):
    target_corner = finish_corner
    new_position = list(current_position)

    if new_position[0] < target_corner[0]:
        new_position[0] += 1
    elif new_position[0] > target_corner[0]:
        new_position[0] -= 1

    if new_position[1] < target_corner[1]:
        new_position[1] += 1
    elif new_position[1] > target_corner[1]:
        new_position[1] -= 1

    return tuple(new_position)


def calculate_reward(agent_index, current_position, next_position):
    reward = -1  # Default time penalty for each step

    # Check for penalties
    for j, position in enumerate(salesmen_positions):
        if j != agent_index and np.array_equal(next_position, position):
            reward -= 100  # Penalty for standing on another agent
            break

    for i, city in enumerate(cities_positions):
        if np.array_equal(city, next_position):
            reward -= 50  # Penalty for standing on a city
            if visit_counts[i].sum() >= 2:
                return reward  # No additional reward if the city has already been visited by 2 agents
            if visit_counts[i, agent_index] == 0:  # First visit
                agents_visited_cities[agent_index] += 1
                reward += 20
            elif visit_counts[i, agent_index] == 1:  # Second visit
                reward += 50
            visit_counts[i, agent_index] += 1

    if np.array_equal(next_position, current_position):
        reward -= 200  # Standing still penalty
    elif tuple(next_position) not in agents_visited_squares[agent_index]:
        reward += 10  # New square
    else:
        reward -= 2  # Old square

    return reward


fig, ax = plt.subplots(figsize=(10, 10))
plt.subplots_adjust(left=0.1, right=0.9, top=0.85, bottom=0.2)
ax.set_xlim(-1, grid_size)
ax.set_ylim(-1, grid_size)

# Create button
axcolor = 'lightgoldenrodyellow'
ax_button = plt.axes([0.8, 0.05, 0.1, 0.04])

button = Button(ax_button, 'New World', color=axcolor, hovercolor='0.975')


def update(val):
    global cities_positions, num_salesmen, num_cities, grid_size, visit_counts, epsilon

    update_positions()
    epsilon = max(epsilon * epsilon_decay, epsilon_min)  # Decay epsilon

    ax.clear()
    ax.set_xlim(-1, grid_size)
    ax.set_ylim(-1, grid_size)

    # Plot cities
    for i, city in enumerate(cities_positions):
        color = 'darkblue' if (visit_counts[i] > 0).sum() < 2 else 'green'
        ax.add_patch(patches.Circle((city[0], city[1]), radius=0.3, color=color, label='City'))

    # Plot salesmen
    for i, salesman in enumerate(salesmen_positions):
        circle = patches.Circle((salesman[0], salesman[1]), radius=0.3, color='red')
        ax.add_patch(circle)
        ax.text(salesman[0], salesman[1], str(i + 1), color='white', ha='center', va='center', fontsize=12,
                weight='bold')

    # Draw grid lines
    for x in range(grid_size):
        ax.axhline(x, lw=0.4, color='gray', linestyle='--')
        ax.axvline(x, lw=0.4, color='gray', linestyle='--')

    # Update title with world number and move counts
    ax.set_title(f'World {world_number}', fontsize=14)

    fig.canvas.draw_idle()


def check_objective():
    global visit_counts, num_salesmen
    total_visits = visit_counts.sum()
    if total_visits >= num_salesmen * 2:
        new_world(None)
        return True
    return False


def animate(i):
    if not check_objective():
        update(i)


def new_world(event):
    global cities_positions, visit_counts, agents_visited_cities, agents_visited_squares, agent_moves, world_number, epsilon
    world_number += 1
    cities_positions = np.random.randint(0, grid_size, (num_cities, 2))
    visit_counts = np.zeros((num_cities, num_salesmen))
    agents_visited_cities = np.zeros(num_salesmen)
    agents_visited_squares = [set() for _ in range(num_salesmen)]
    agent_moves = np.zeros(num_salesmen, dtype=int)
    salesmen_positions[:] = np.random.randint(0, grid_size, (num_salesmen, 2))
    epsilon = 1.0  # Reset epsilon to encourage exploration in the new world
    update(0)


button.on_clicked(new_world)

# Initial plot
update(0)

ani = animation.FuncAnimation(fig, animate, frames=np.arange(0, 200), interval=1000 / 120, repeat=True)  # 120 fps

plt.show(block=True)
