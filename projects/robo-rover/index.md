---
layout: default
title: RoboRover
permalink: /projects/robo-rover/
---

{% include project-meta.html %}

# RoboRover: Autonomous ROS2 Jetson Robot

I built RoboRover from scratch (not a kit) over a six-lab course sequence, using it to learn SLAM, autonomous navigation, and teleoperation on a Jetson Orin Nano. It's also what convinced me to build *Gracie* next.

---

## About the Project

It runs Ubuntu and ROS2 on a Jetson Orin Nano, flashed via NVMe on Jetpack 6.2. The bulk of the work was:

1. Running and adapting ROS2 tutorial nodes  
2. Building a teleop system to control the robot with a keyboard  
3. Developing custom ROS2 nodes for line following using computer vision  
4. Creating obstacle avoidance logic using sensor feedback and SLAM

This is the project that got me interested in mobile manipulation, not just navigation.

---

## Build Photos

<div class="project-gallery">
  <figure><img src="./Top Down - Chassis.png" alt="Robot view 1"></figure>
  <figure><img src="./Top Down - 3D Mounts.png" alt="Robot view 2"></figure>
  <figure><img src="./Top Down - Components.png" alt="Robot view 3"></figure>
  <figure><img src="./Side View - Jetson.png" alt="Robot view 4"></figure>
</div>

---

## Showcase Photos

<div class="project-gallery">
  <figure><img src="./Top Down - Done.png" alt="RoboRover assembled"></figure>
  <figure><img src="./Front View - Done.png" alt="Close-up wiring"></figure>
</div>

---

## Demo Videos

<div style="display: flex; flex-direction: column; gap: 20px;">

<iframe width="100%" height="315" src="https://www.youtube.com/embed/3Ol4f7IO_aY" title="Line Following A" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/l5Tz1ksXPA4" title="Line Following B" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/qwQZIoRHT18" title="Room Mapping - Escaping" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/luvHeXtz5bk" title="Room Mapping - Navigation" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/En79nlPJ7sA" title="Room Mapping - Completion" frameborder="0" allowfullscreen></iframe>

</div>

---

## 3D Printed Components

<div style="display: flex; flex-direction: column; gap: 10px; font-size: 1rem;">
  <p>Want to reuse or remix the mechanical design?</p>
  <ul>
    <li><a href="./Jetson Mount v2.stl" download>Jetson Mount v2 (.stl)</a></li>
    <li><a href="./Camera Mount.stl" download>Camera Mount (.stl)</a></li>
    <li><a href="./Battery Mount.stl" download>Battery Mount (.stl)</a></li>
  </ul>
</div>

---

## System Summary

- **Main Board:** Jetson Orin Nano (8GB)
- **OS / SDK:** Jetpack 6.2 w/ ROS2
- **Development:** All nodes built using Python and C++ (custom)
- **Features:** Teleop, Line Following, Obstacle Avoidance, SLAM
- **Build:** Fully custom (not from a kit)

---

## If I Came Back to This

RoboRover did what I needed it to do, and I moved on to Gracie instead of continuing this one. If I had kept going, the next steps would've been a real depth camera and basic object recognition for grasp planning.
