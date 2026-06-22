---
layout: default
title: Gracie
permalink: /projects/gracie/
---

{% include project-meta.html %}

# Gracie: Omnidirectional Autonomous Robot with Pick-and-Place Precision

**Gracie** is an advanced mobile robot platform designed to navigate dynamic environments, identify and retrieve objects, and interact with its surroundings. Built on a mecanum wheel chassis for full holonomic movement, Gracie combines precision mobility with intelligent manipulation through an integrated robotic arm.

---

## About the Project

Gracie was engineered as a versatile robotics platform capable of:

- Room mapping using LiDAR and depth sensing
- Fully omnidirectional locomotion via mecanum wheels
- Autonomous pick-and-place with a robotic arm
- Local and remote control interface using a 7” touch screen
- Onboard processing powered by the Jetson Orin Nano

The platform was designed from the ground up with modularity and customization in mind — all major components are securely mounted using custom 3D-printed hardware.

---

## Showcase Photos

<div class="project-gallery">
  <figure>
    <img src="./Gracie 1.png" alt="Gracie robot view 1" />
    <figcaption>Side view of Gracie with Jetson and mounted screen</figcaption>
  </figure>
  <figure>
    <img src="./Gracie 2.png" alt="Gracie robot view 2" />
    <figcaption>Top-down view of Gracie with mounted arm and LiDAR</figcaption>
  </figure>
</div>

---

## Download 3D Models

All mechanical mounts were custom designed for this project. Download them below to explore, remix, or print your own:

- [USB Hub Mount (STL)](./USB%20Hub%20Mount%20v1.stl)
- [Power Button Mount (STL)](./Power%20Button%20Mount%20v1.stl)
- [Touch Screen Mount (STL)](./Touch%20Screen%20Mount%20v1.stl)
- [Jetson Orin Nano Mount (STL)](./Jetson%20Orin%20Nano%20Mount%20v1.stl)

---

## Software Development in Progress

Gracie’s hardware is complete, and the software is actively being developed. Key tasks include:

- Navigation and obstacle avoidance
- Object detection and pick-up algorithms
- Touch interface control panel
- ROS-based integration for all subsystems

Stay tuned as this robotic platform comes to life!
