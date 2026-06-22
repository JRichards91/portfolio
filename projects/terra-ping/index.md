---
layout: default
title: TerraPing
permalink: /projects/terra-ping/
---

{% include project-meta.html %}

# TerraPing: Next-Generation Smart Soil Sensor

**TerraPing** is a new battery-powered soil sensor platform I’m developing using the **Nordic nRF54L15-DK**. It’s designed to make precision plant monitoring effortless — blending ultra-low-power wireless operation with seamless integration into modern smart home ecosystems like **Apple HomeKit**, **Google Home**, and **Amazon Alexa**.

---

## Overview

The goal of TerraPing is to create a **compact, energy-efficient soil sensor** that can be dropped into any pot or garden bed and wirelessly report real-time soil data. Using the **nRF54L15 SoC**, the prototype leverages advanced BLE and Matter connectivity for direct pairing with your favorite smart home assistant — no extra bridges required.

---

## Key Features (Planned)

- **Ultra-Low Power Operation** — optimized for long-term deployment on a single battery  
- **Precision Capacitive Moisture Sensing** — stable readings independent of soil conductivity  
- **Matter-Enabled Wireless Connectivity** — compatible with Apple Home, Google Home, and Alexa  
- **Over-the-Air Updates (OTA)** — supported through Nordic’s SDK and development tools  
- **Compact, Sealed Design** — engineered for outdoor use with corrosion-resistant sensor pads  

---

## Current Development

I’m currently using the **nRF54L15-DK** to prototype the firmware and communication stack before transitioning to a custom PCB design. The firmware development focuses on:
- Low-power sleep scheduling and wake-on-measurement routines  
- BLE/Matter service advertisement and pairing for cross-platform home integration  
- Sensor calibration and analog front-end testing using the DK’s onboard ADC  

---

## What’s Next

Upcoming work includes:
- Designing the **custom probe PCB** with integrated capacitive sensor pads  
- Implementing **battery voltage monitoring** and power path management  
- Developing a **HomeKit-native prototype** for seamless testing with iOS devices  

---

## Stay Tuned

TerraPing is still in active development — hardware schematics, enclosure renders, and live demos will be published here as the design matures.  

Check back soon for updates!
