---
layout: default
title: AquaCore
permalink: /projects/aqua-core/
---

# AquaCore: Automated Hydroponic Control System

**AquaCore** is a self-regulating hydroponics controller designed to monitor and maintain critical growing conditions for plants. Using a TM4C123GXL microcontroller, it integrates sensor data with actuator control to adjust lighting and manage water flow — helping plants thrive with minimal oversight.

Originally developed as a proof of concept, AquaCore demonstrated reliable embedded coordination between sensors, motors, and valves, and later evolved into the more advanced FloraByte platform.

---

## 🔧 About the Project

AquaCore is centered around two primary control loops:

- A **distance sensor** monitors the height between the grow light deck and the plant canopy. Based on this input, a **stepper motor** raises or lowers the lighting system to maintain optimal exposure as the plants grow.

- A **liquid level sensor** monitors the fluid in the reservoir. When the level falls below a threshold, a **solenoid valve** is opened to refill the system. Once it reaches a target level, the valve automatically closes.

An onboard temperature sensor tracks ambient conditions for future expansion. System tasks are synchronized using microcontroller timers and interrupts to ensure responsive and consistent performance.

### Features:
- Light deck automatically tracks plant height  
- Reservoir water level maintained via solenoid valve  
- Real-time feedback from distance, level, and temperature sensors  
- Stepper motor and relay control for actuation  
- Custom 3D-printed housing for sensors and electronics  

---

## 🧩 Schematic & Build Photo

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center; align-items: flex-start;">

  <!-- Schematic -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <div style="height: 650px; display: flex; align-items: center; justify-content: center; background-color: white; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2); padding: 10px;">
      <img src="./9. Schematic v2.png" alt="AquaCore schematic" style="max-height: 100%; max-width: 100%; object-fit: contain;" />
    </div>
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

👉 [Download AquaCore 3D CAD File (.3mf)](./Base-Lid-Arrow.3mf)

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

- Add humidity and CO₂ sensing  
- Integrate remote monitoring via Wi-Fi or cloud  
- Solar-powered version with battery backup  
- Upgrade to modular control with machine learning  
