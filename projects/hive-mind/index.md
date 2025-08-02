---
layout: default
title: HiveMind
permalink: /projects/hive-mind/
---

# HiveMind: Multi-Agent Route Optimization in Python

**HiveMind** is a Python-based implementation of the Multi-Traveling Salesman Problem (mTSP), designed to optimize the path planning of multiple agents across a shared set of waypoints. This model simulates coordination between autonomous agents tasked with covering distinct routes efficiently — a critical problem in logistics, robotics, and swarm systems.

---

## 🔧 About the Project

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

## 💻 Code

<div style="position: relative;">

  <!-- Copy Button -->
  <button onclick="copyCode(this)" style="
    position: absolute;
    top: 8px;
    right: 8px;
    background-color: #3c3c3c;
    color: #fff;
    border: none;
    padding: 4px 8px;
    font-size: 0.75rem;
    border-radius: 4px;
    cursor: pointer;
    z-index: 1;
  ">Copy</button>

  <div id="codeBlock" style="
    max-height: 500px;
    overflow: auto;
    background-color: #1e1e1e;
    color: #d4d4d4;
    font-size: 0.85rem;
    font-family: SFMono-Regular, Consolas, Liberation Mono, Menlo, monospace;
    border-radius: 6px;
    padding: 16px;
    box-shadow: 0 2px 6px rgba(0,0,0,0.2);
    margin-top: 1em;
  ">
    {% highlight python %}
    {% include_relative FinalProject.py %}
    {% endhighlight %}
  </div>
</div>

<script>
function copyCode(button) {
  const codeBlock = button.nextElementSibling;
  const text = codeBlock.innerText;
  navigator.clipboard.writeText(text).then(() => {
    button.innerText = "Copied!";
    setTimeout(() => { button.innerText = "Copy"; }, 1500);
  }).catch(() => {
    button.innerText = "Failed!";
  });
}
</script>

---

## 🔬 Future Extensions

- Integration with A* or genetic algorithms
- Real-world map support via GPS coordinates
- GUI interface for city and agent input
- Dynamic task reallocation based on agent availability
- Simulation with physical robots or drone swarms

---

## 📦 Applications

- Warehouse pick-path planning
- Drone delivery scheduling
- Multi-robot exploration
- Disaster response and area search

---

Stay tuned as this solver grows into a more complete multi-agent coordination platform.
