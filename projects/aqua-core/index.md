---
layout: default
title: AquaCore
permalink: /projects/aqua-core/
---

# AquaCore: Automated Hydroponic Control System

**AquaCore** is a microcontroller-based proof-of-concept for an automated hydroponic system. Built entirely with low-level C and the TM4C123GXL LaunchPad, it integrates multiple sensors and actuators to manage water distribution and nutrient delivery with no AI or advanced logic — just efficient embedded design.

This project laid the foundation for its more advanced successor, **FloraByte**, which builds on AquaCore’s core concepts with greater scalability and intelligence.

---

## 🔧 About the Project

AquaCore was developed to explore how a microcontroller could coordinate real-world sensors and actuators in a hydroponic environment using nothing but hardcoded logic in C.

It monitors:
- **Water level** using a digital float sensor  
- **Reservoir distance** using an optical ADC sensor  
- **Ambient temperature** over I2C  

Based on sensor input, it:
- **Rotates a stepper motor** to align a nutrient arm  
- **Opens/closes a solenoid valve** via a relay  

System timing and decision logic are handled using **SysTick and hardware timer interrupts**, making AquaCore a great demonstration of low-level embedded systems in a real-world application.

### Features:
- No AI or machine learning — just bare-metal C  
- Automated pump and valve control based on real-time input  
- Stepper motor targeting with multi-step logic  
- Structured timing with SysTick + GPIO-based actuation  
- Modular 3D-printed design for easy deployment  

---

## 🧩 Schematic & Build

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center; align-items: flex-start;">

  <!-- Schematic -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./9. Schematic-v2.png" alt="AquaCore schematic" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Wiring schematic showing sensor/actuator pin mapping</p>
  </div>

  <!-- Breadboard -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./IMG_1887.png" alt="AquaCore breadboard prototype" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Prototype circuit built on breadboard</p>
  </div>

</div>

---

## 🖼️ CAD Renderings

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center; align-items: flex-start;">

  <!-- CAD View 1 -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./Drawing-with-lid.png" alt="CAD model - exploded view" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">CAD view of lid</p>
  </div>

  <!-- CAD View 2 -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./Drawing-without-lid.png" alt="CAD model - assembled" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">CAD view of enclosure</p>
  </div>

</div>

---

## 🧾 Download 3D Model

Want to explore or print the custom 3D enclosure?

👉 [Download AquaCore 3D CAD File (.3mf)](./Base-Lid-Arrow.3mf.zip)

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
{% highlight c %}
{% include_relative main.c %}
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

## 🛠️ Hardware Used

- TM4C123GXL LaunchPad  
- Optical Distance Sensor (Analog → PB5)  
- Non-contact Liquid Level Sensor (PB0)  
- Temperature Sensor (I2C: PB2/SCL, PB3/SDA)  
- Stepper Motor + Easy Driver (PC4–PC7)  
- Solenoid Valve via Relay (PD2)  
- 3D-printed enclosure (Fusion 360)  

---

## 🧠 Future Ideas

- Add AI/ML logic to enable adaptive watering  
- Incorporate cloud or Wi-Fi remote control  
- Expand sensor suite with humidity/CO₂ monitoring  
- Design a solar/battery power system for off-grid use  
