---
layout: default
title: AquaCore
permalink: /projects/aqua-core/
---

{% include project-meta.html %}

# AquaCore: Automated Hydroponic Control System

**AquaCore** is a self-regulating hydroponics controller designed to monitor and maintain critical growing conditions for plants. Using a TM4C123GXL microcontroller, it integrates sensor data with actuator control to adjust lighting and manage water flow — helping plants thrive with minimal oversight.

Originally developed as a proof of concept, AquaCore demonstrated reliable embedded coordination between sensors, motors, and valves, and later evolved into the more advanced FloraByte platform.

---

## About the Project

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

## Schematic & Build Photo

<div class="project-gallery">
  <figure>
    <img src="./9. Schematic v2.png" alt="AquaCore schematic" />
    <figcaption>Wiring schematic showing sensor/actuator pin mapping</figcaption>
  </figure>
  <figure>
    <img src="./IMG_1887.png" alt="AquaCore breadboard prototype" />
    <figcaption>Prototype circuit built on breadboard</figcaption>
  </figure>
</div>

---

## CAD Renderings

<div class="project-gallery">
  <figure>
    <img src="./Drawing-with-lid.png" alt="CAD model - exploded view" />
    <figcaption>CAD view of lid</figcaption>
  </figure>
  <figure>
    <img src="./Drawing-without-lid.png" alt="CAD model - assembled" />
    <figcaption>CAD view of enclosure</figcaption>
  </figure>
</div>

---

## Download 3D Model

Want to explore or print the custom 3D enclosure?

[Download AquaCore 3D CAD File (.3mf)](./Base-Lid-Arrow.3mf)

---

## Code

<div class="code-block-wrap">
  <button class="copy-btn" data-copy-code>Copy</button>
  <div class="code-block">
{% highlight c %}
{% include_relative main.c %}
{% endhighlight %}
  </div>
</div>

---

## Hardware Used

- TM4C123GXL LaunchPad  
- Optical Distance Sensor (Analog → PB5)  
- Non-contact Liquid Level Sensor (PB0)  
- Temperature Sensor (I2C: PB2/SCL, PB3/SDA)  
- Stepper Motor + Easy Driver (PC4–PC7)  
- Solenoid Valve via Relay (PD2)  
- 3D-printed enclosure (Fusion 360)  

---

## Future Ideas

- Add humidity and CO₂ sensing  
- Integrate remote monitoring via Wi-Fi or cloud  
- Solar-powered version with battery backup  
- Upgrade to modular control with machine learning  
