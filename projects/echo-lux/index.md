---
layout: default
title: EchoLux
permalink: /projects/echo-lux/
---

{% include project-meta.html %}

# EchoLux: Real-Time Audio Reactive Light Show

**EchoLux** is an interactive sound-to-light system that transforms live audio input into vibrant LED animations. Designed around a microphone module and a WS2812 LED strip, the system reacts dynamically to sound intensity — clapping, music, or speech — creating a mesmerizing ambient display.

---

## About the Project

EchoLux was built using an analog microphone breakout and a digital LED strip, controlled by a PyBoard running MicroPython. When sound is detected, the analog signal is amplified and sampled, then mapped to brightness levels and animation patterns on the LED strip.

This project combines analog signal conditioning, real-time data processing, and visual output — making it ideal for learning about audio signal acquisition, LED control, and embedded systems programming.

### Features:
- Real-time analog audio sampling
- Dynamic LED response (brightness and animation)
- Microphone gain tuning
- Efficient frame rate control to reduce flicker
- Fully MicroPython-compatible

---

## Schematic & Build Photo

<div class="project-gallery">
  <figure>
    <img src="./EENG 163 - Final - Schematic.png" alt="EchoLux schematic" />
    <figcaption>Circuit schematic showing microphone amp and LED strip wiring</figcaption>
  </figure>
  <figure>
    <img src="./EENG 163 - Final - Picture.png" alt="EchoLux Breadboard Build" />
    <figcaption>Breadboard prototype of the EchoLux system</figcaption>
  </figure>
</div>

---

## Demo Video

<iframe width="100%" height="400"
  src="https://www.youtube.com/embed/rCREi2waXuE"
  title="EchoLux Demo Video"
  frameborder="0"
  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
  allowfullscreen>
</iframe>

---

## Code

<div class="code-block-wrap">
  <button class="copy-btn" data-copy-code>Copy</button>
  <div class="code-block">
    {% highlight python %}
    {% include_relative echo-lux.py %}
    {% endhighlight %}
  </div>
</div>

---

## Hardware Used

- PyBoard Microcontroller
- Analog Microphone Module (e.g., KY-037)
- WS2812B NeoPixel LED Strip (15 LEDs)
- Breadboard & jumper wires
- 5V regulated power input

---

## Future Ideas

- Add FFT for frequency-based visualizations
- Implement beat/tempo detection
- Design a 3D-printed enclosure with diffusion panel
- Add remote control via MQTT or BLE
