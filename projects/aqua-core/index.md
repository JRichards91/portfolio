---
layout: default
title: AquaCore
permalink: /projects/aquacore/
---

# AquaCore: Automated Hydroponic Control System

**AquaCore** is a fully automated hydroponics controller built around the TM4C123GXL microcontroller. It integrates sensor data and actuator control to maintain optimal growing conditions for plants with minimal manual input.

---

## 🔧 About the Project

Designed for precision irrigation and environmental control, AquaCore monitors plant bed water level, nutrient distance, and temperature. Based on sensor feedback, it dynamically controls a stepper motor to position a nutrient feeder and opens or closes a solenoid valve via relay.

It uses:
- ADC for optical distance sensing
- I2C to read ambient temperature
- Digital GPIO for liquid level sensing and actuator control
- SysTick and timer interrupts to coordinate system behavior

The system was prototyped and tested with 3D-printed enclosures and performed successfully across all core tasks.

### Features:
- Automated irrigation control
- Real-time distance + temperature sensing
- Intelligent stepper motor logic
- Relay-driven valve actuation
- Fully interrupt-driven logic

---

## 🧩 Schematic & Build

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center; align-items: flex-start;">

  <!-- Schematic -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./Schematic v2.png" alt="AquaCore schematic" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
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
    <img src="./Drawing - w: Lid.png" alt="CAD model - exploded view" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Exploded CAD view of enclosure and mechanical system</p>
  </div>

  <!-- CAD View 2 -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./Drawing w:out Lid.png" alt="CAD model - assembled" style="width: 100%; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Assembled 3D model of AquaCore enclosure</p>
  </div>

</div>

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
