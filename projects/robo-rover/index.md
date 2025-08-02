---
layout: default
title: RoboRover
permalink: /projects/robo-rover/
---

# RoboRover: Autonomous ROS2 Jetson Robot

**RoboRover** is a custom-built autonomous robot platform powered by the Jetson Orin Nano and ROS2. Built entirely from sourced components (not a kit), this robot was designed to explore SLAM, autonomous navigation, and teleoperation techniques. It was completed as part of a six-lab experience and directly inspired the creation of *Gracie*, my personal follow-up robot.

---

## 🔧 About the Project

The robot runs Ubuntu and ROS2 on a Jetson Orin Nano, flashed via NVMe using Jetpack 6.2. The main development efforts involved:

1. Running and adapting ROS2 tutorial nodes  
2. Building a teleop system to control the robot with a keyboard  
3. Developing custom ROS2 nodes for line following using computer vision  
4. Creating obstacle avoidance logic using sensor feedback and SLAM

This project formed the foundation for my interest in mobile manipulation and AI-powered robotics.

---

## 🖼️ Build Photos

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center;">
  <img src="./Top Down - Chassis.png" style="width: 45%; border-radius: 8px;" alt="Robot view 1">
  <img src="./Top Down - 3D Mounts.png" style="width: 45%; border-radius: 8px;" alt="Robot view 2">
  <img src="./Top Down - Components.png" style="width: 45%; border-radius: 8px;" alt="Robot view 3">
  <img src="./Side View - Jetson.png" style="width: 45%; border-radius: 8px;" alt="Robot view 4">
</div>

---

## 🌟 Showcase Photos

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center;">
  <img src="./Top Down - Done.png" style="width: 45%; border-radius: 8px;" alt="RoboRover assembled">
  <img src="./Front View - Done.png" style="width: 45%; border-radius: 8px;" alt="Close-up wiring">
</div>

---

## 🎥 Demo Videos

<div style="display: flex; flex-direction: column; gap: 20px;">

<iframe width="100%" height="315" src="https://www.youtube.com/embed/3Ol4f7IO_aY" title="Line Following A" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/l5Tz1ksXPA4" title="Line Following B" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/qwQZIoRHT18" title="Room Mapping - Escaping" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/luvHeXtz5bk" title="Room Mapping - Navigation" frameborder="0" allowfullscreen></iframe>

<iframe width="100%" height="315" src="https://www.youtube.com/embed/En79nlPJ7sA" title="Room Mapping - Completion" frameborder="0" allowfullscreen></iframe>

</div>

---

## 📦 3D Printed Components

<div style="display: flex; flex-direction: column; gap: 10px; font-size: 1rem;">
  <p>Want to reuse or remix the mechanical design?</p>
  <ul>
    <li><a href="./Jetson Mount v2.stl" download>Jetson Mount v2 (.stl)</a></li>
    <li><a href="./Camera Mount.stl" download>Camera Mount (.stl)</a></li>
    <li><a href="./Battery Mount.stl" download>Battery Mount (.stl)</a></li>
  </ul>
</div>

---

## 🔩 System Summary

- **Main Board:** Jetson Orin Nano (8GB)
- **OS / SDK:** Jetpack 6.2 w/ ROS2
- **Development:** All nodes built using Python and C++ (custom)
- **Features:** Teleop, Line Following, Obstacle Avoidance, SLAM
- **Build:** Fully custom (not from a kit)

---

## 🧠 Next Steps

- Upgrade to full 3D Depth Sense Camera
- Integrate object recognition and grasp planning
- Deploy custom-built manipulator arm from Gracie
