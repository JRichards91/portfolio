---
layout: default
title: VaporIQ
permalink: /projects/vapor-iq/
---

# VaporIQ: SF₆ Gas Density Monitoring System

**VaporIQ** is a simplified gas density monitor built using the Tiva C Series TM4C123GH6PM microcontroller. Inspired by real-world applications used by electric utilities, this project simulates pressure and temperature sensing for SF₆ gas using analog potentiometers and computes gas density using the Ideal Gas Law. The result is displayed on a 3-digit 7-segment display, with a mode switch, status LEDs, and an automated alarm system.

---

## 🔧 About the Project

SF₆ is widely used in high-voltage circuit breakers for its superior dielectric strength. But due to its high global warming potential and critical role in safety, continuous monitoring is essential.

VaporIQ calculates percent density based on measured temperature and pressure, comparing real-time readings to an expected “ideal” pressure value using:

**P = sT**, where `s = 0.17065` and `T` is temperature in Kelvin.

The user can switch display modes between **Density**, **Pressure**, and **Temperature**. If density drops below a critical threshold, an LED alarm triggers.

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

  <!-- Code Container -->
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
    {% include_relative vapor-iq.c %}
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

## 🧠 Future Ideas

- Add real pressure and temperature sensors instead of pots
- Transmit data via UART or CAN for real-world integration
- Add data logging to EEPROM or external storage
- Integrate wireless alerts or dashboard via Bluetooth or RF
