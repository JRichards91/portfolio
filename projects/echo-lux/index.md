---
layout: default
title: EchoLux
permalink: /projects/echo-lux/
---

{% include project-meta.html %}

# EchoLux: Real-Time Audio Reactive Light Show

I built EchoLux for a class final: an LED strip that reacts to live sound in real time, whether that's clapping, music, or just talking near the mic.

---

## About the Project

I used an analog microphone breakout and a WS2812 LED strip, controlled by a PyBoard running MicroPython. The mic signal gets amplified, sampled, and mapped to brightness and animation patterns on the strip.

Most of the actual work was in tuning the mic gain and frame timing so the LEDs responded cleanly without flickering — a good first project for analog signal conditioning and real-time embedded control.

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

## If I Came Back to This

I'm not planning to revisit EchoLux, but if I did, FFT-based frequency visualization and beat detection would be the obvious next steps, along with a proper 3D-printed enclosure with a diffusion panel.
