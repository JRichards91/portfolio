---
layout: default
title: AquaCore
permalink: /projects/aqua-core/
---

{% include project-meta.html %}

# AquaCore: Automated Hydroponic Control System

I built AquaCore to test whether a TM4C123 microcontroller could run a hydroponics setup on its own — adjusting grow light height and refilling the reservoir without me touching it.

It was a proof of concept, not a finished product, but it proved the core idea worked: sensors, motors, and valves all coordinating reliably. That's the foundation FloraByte was built on.

---

## About the Project

AquaCore runs on two control loops:

- A **distance sensor** tracks the gap between the grow light deck and the plant canopy. A **stepper motor** raises or lowers the lighting to keep exposure consistent as the plants grow.

- A **liquid level sensor** watches the reservoir. When it drops below a threshold, a **solenoid valve** opens to refill it, then closes once it hits target level.

There's also an onboard temperature sensor, though I never wired it into the control logic — it just logs ambient conditions. I used microcontroller timers and interrupts to keep everything synchronized instead of polling in a loop.

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

## If I Came Back to This

I don't plan on revisiting AquaCore directly — FloraByte is the project that actually moved forward. But if I did, I'd add humidity/CO₂ sensing, hook up remote monitoring over Wi-Fi, and look at a solar-powered version with battery backup.
