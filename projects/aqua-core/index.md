---
layout: default
title: AquaCore
permalink: /projects/aqua-core/
---

# AquaCore: Automated Hydroponic Control System

**AquaCore** is a fully automated hydroponics controller built around the TM4C123GXL microcontroller. Designed as a proof of concept, it became the foundation for the more advanced FloraByte system. AquaCore integrates sensor readings and actuator control to maintain optimal growing conditions — with no manual intervention required.

---

## 🔧 About the Project

This system intelligently manages plant irrigation and nutrient delivery by sensing water level, optical distance to fluid, and ambient temperature. Using that input, it operates a stepper motor to position a feeder arm and toggles a solenoid valve via relay.

It uses:
- ADC for distance sensor input
- I2C for temperature reading
- GPIO for level sensing, relay, and motor control
- SysTick and timer interrupts to handle tasks efficiently

### Features:
- Fully automated watering sequence
- Real-time fluid and temperature sensing
- Stepper-driven nutrient positioning
- Relay-controlled solenoid valve
- Efficient interrupt-based design
- 3D-printed modular enclosure

---

## 🧩 Schematic & Build

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center; align-items: flex-start;">

  <!-- Schematic -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./Schematic-v2.png" alt="AquaCore schematic" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
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
    <p style="text-align: center; margin-top: 10px;">Exploded CAD view of enclosure and mechanical system</p>
  </div>

  <!-- CAD View 2 -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./Drawing-without-lid.png" alt="CAD model - assembled" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Assembled 3D model of AquaCore enclosure</p>
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

- Add humidity and CO₂ sensors
- Remote monitoring via Wi-Fi or cloud
- Solar power with battery backup
- Machine-learning driven irrigation
