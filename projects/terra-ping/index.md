---
layout: default
title: TerraPing
permalink: /projects/terra-ping/
---

{% include project-meta.html %}

# TerraPing: Smart Soil Sensor

TerraPing is a battery-powered soil sensor I'm prototyping on the Nordic nRF54L15-DK, aimed at pairing directly with Apple HomeKit, Google Home, and Alexa over Matter — no extra bridge device required. It's currently on hold.

---

## Overview

The goal is a compact, energy-efficient sensor you can drop into any pot or garden bed that reports soil data wirelessly. I picked the nRF54L15 SoC specifically for its BLE/Matter support, which is what makes the direct hub pairing possible in the first place.

---

## Planned Features

- Ultra-low power operation, built for long-term deployment on a single battery
- Capacitive moisture sensing with stable readings regardless of soil conductivity
- Matter-based wireless connectivity for Apple Home, Google Home, and Alexa
- OTA updates through Nordic's SDK
- Compact, sealed enclosure for outdoor use with corrosion-resistant sensor pads

---

## Where I Left It

I was using the nRF54L15-DK to prototype firmware and the communication stack before moving to a custom PCB. That covered:
- Low-power sleep scheduling and wake-on-measurement routines
- BLE/Matter service advertisement and pairing for cross-platform home integration
- Sensor calibration and analog front-end testing on the DK's onboard ADC

---

## If I Pick This Back Up

The next steps would be a custom probe PCB with integrated capacitive sensor pads, battery voltage monitoring and power path management, and a HomeKit-native prototype to test on iOS.

---

## On Hold

TerraPing is paused while I focus on other things. I plan to come back to it — when I do, I'll post schematics, enclosure renders, and a working demo here.
