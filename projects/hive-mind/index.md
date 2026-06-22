---
layout: default
title: HiveMind
permalink: /projects/hive-mind/
---

{% include project-meta.html %}

# HiveMind: Multi-Agent Route Optimization in Python

**HiveMind** is a Python-based implementation of the Multi-Traveling Salesman Problem (mTSP), designed to optimize the path planning of multiple agents across a shared set of waypoints. This model simulates coordination between autonomous agents tasked with covering distinct routes efficiently — a critical problem in logistics, robotics, and swarm systems.

---

## About the Project

This project solves the multi-agent variant of the classic TSP using custom heuristics, clustering algorithms, and matplotlib-based visualizations. Each agent receives a subset of cities to visit, and the solution aims to minimize both the total travel cost and the workload variance between agents.

This system was developed as a foundation for exploring multi-agent coordination and distributed planning.

### Features:
- Random or user-defined city maps
- Customizable number of agents
- Euclidean cost metrics between nodes
- k-means clustering for route partitioning
- 2-opt and greedy heuristics for intra-route optimization
- Real-time matplotlib visualization of agent paths

---

## Code

<div class="code-block-wrap">
  <button class="copy-btn" data-copy-code>Copy</button>
  <div class="code-block">
    {% highlight python %}
    {% include_relative FinalProject.py %}
    {% endhighlight %}
  </div>
</div>

---

## Future Extensions

- Integration with A* or genetic algorithms
- Real-world map support via GPS coordinates
- GUI interface for city and agent input
- Dynamic task reallocation based on agent availability
- Simulation with physical robots or drone swarms

---

## Applications

- Warehouse pick-path planning
- Drone delivery scheduling
- Multi-robot exploration
- Disaster response and area search

---
