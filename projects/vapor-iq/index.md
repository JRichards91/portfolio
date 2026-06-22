---
layout: default
title: VaporIQ
permalink: /projects/vapor-iq/
---

{% include project-meta.html %}

# VaporIQ: SF₆ Gas Density Monitoring System

I built VaporIQ on a TM4C123 LaunchPad to model how electric utilities monitor SF₆ gas density in high-voltage breakers — potentiometers simulate pressure and temperature, the Ideal Gas Law computes density, and the result shows up on a 7-segment readout with a mode switch and alarm system.

---

## About the Project

SF₆ is used in high-voltage circuit breakers for its dielectric strength, but it's also a potent greenhouse gas, so utilities monitor it continuously for both safety and environmental reasons.

VaporIQ calculates percent density by comparing measured pressure and temperature against an expected "ideal" pressure value:

**P = sT**, where `s = 0.17065` and `T` is temperature in Kelvin.

You can switch the display between density, pressure, and temperature with a button. If density drops below a set threshold, an LED alarm triggers automatically.

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

- Tiva C TM4C123GXL LaunchPad
- Two potentiometers (simulate pressure and temperature)
- 3-digit 7-segment display (Port D 0–3 and Port E 1–3)
- Mode indicator using onboard LEDs
- Alarm LED (Port D pin 6)
- Mode selector pushbutton (SW1)
- ADCs on pins:
  - Pressure: Port B pin 5 (AIN11)
  - Temperature: Port E pin 5 (AIN8)

---

## If I Came Back to This

VaporIQ was a simulation exercise — the potentiometers stand in for real sensors. If I revisited it, swapping those for actual pressure/temperature sensors and adding UART or CAN output would be the obvious next step, along with data logging and a wireless alert option.
