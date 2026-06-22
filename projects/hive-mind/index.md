---
layout: default
title: HiveMind
permalink: /projects/hive-mind/
---

{% include project-meta.html %}

# HiveMind: Multi-Agent Route Optimization in Python

I wrote HiveMind to solve the multi-agent traveling salesman problem — splitting a shared set of waypoints across several agents so each one ends up with an efficient route.

---

## About the Project

I used k-means clustering to split cities between agents, then 2-opt and greedy heuristics to optimize each agent's route within its cluster. The objective balances two things: total travel cost and how evenly the workload is split across agents.

It started as a way to get hands-on with multi-agent coordination rather than just reading about it.

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

## If I Came Back to This

I'm not planning to extend HiveMind further, but the natural next steps would be GPS-based real maps, a GUI for setting up agents and cities, and dynamic task reallocation if an agent drops out mid-route.

---

## Applications

- Warehouse pick-path planning
- Drone delivery scheduling
- Multi-robot exploration
- Disaster response and area search

---
