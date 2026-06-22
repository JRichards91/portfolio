---
layout: default
title: Gracie
permalink: /projects/gracie/
---

{% include project-meta.html %}

# Gracie: Omnidirectional Autonomous Robot with Pick-and-Place Precision

I'm building Gracie to pick up where RoboRover left off — a mecanum-wheel robot that can move in any direction and use a robotic arm to find and grab objects.

---

## About the Project

Gracie is built around:

- Room mapping using LiDAR and depth sensing
- Fully omnidirectional locomotion via mecanum wheels
- Autonomous pick-and-place with a robotic arm
- Local and remote control through a 7” touch screen
- Onboard processing on a Jetson Orin Nano

I designed it to be modular — every major component mounts using custom 3D-printed hardware, so I can swap parts out as I go instead of rebuilding from scratch.

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

The hardware's done. What's left is software:

- Navigation and obstacle avoidance
- Object detection and pick-up algorithms
- Touch interface control panel
- ROS-based integration across all subsystems

I'll update this page as it comes together.
