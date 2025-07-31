---
layout: default
title: EchoLux
permalink: /projects/echo-lux/
---

# EchoLux: Real-Time Audio Reactive Light Show

**EchoLux** is an interactive sound-to-light system that transforms live audio input into vibrant LED animations. Designed around a microphone module and a WS2812 LED strip, the system reacts dynamically to sound intensity — clapping, music, or speech — creating a mesmerizing ambient display.

---

## 🔧 About the Project

EchoLux was built using an analog microphone breakout and a digital LED strip, controlled by a PyBoard running MicroPython. When sound is detected, the analog signal is amplified and sampled, then mapped to brightness levels and animation patterns on the LED strip.

This project combines analog signal conditioning, real-time data processing, and visual output — making it ideal for learning about audio signal acquisition, LED control, and embedded systems programming.

### Features:
- Real-time analog audio sampling
- Dynamic LED response (brightness and animation)
- Microphone gain tuning
- Efficient frame rate control to reduce flicker
- Fully MicroPython-compatible

---

## 🧩 Schematic & Build Photo

<div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: center; align-items: flex-start;">

  <!-- Schematic Image -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./EENG 163 - Final - Schematic.png" alt="EchoLux schematic" style="width: 100%; height: auto; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Circuit schematic showing microphone amp and LED strip wiring</p>
  </div>

  <!-- Project Build Photo -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./EENG 163 - Final - Picture.png" alt="EchoLux Breadboard Build" style="width: 100%; height: auto; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Breadboard prototype of the EchoLux system</p>
  </div>

</div>

---

## 🎥 Demo Video

<iframe width="100%" height="400"
  src="https://www.youtube.com/embed/rCREi2waXuE"
  title="EchoLux Demo Video"
  frameborder="0"
  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
  allowfullscreen>
</iframe>

---

## 💻 Code

{% highlight python %}
{% include_relative echo-lux.py %}
{% endhighlight %}

---

## 🛠️ Hardware Used

- PyBoard Microcontroller
- Analog Microphone Module (e.g., KY-037)
- WS2812B NeoPixel LED Strip (15 LEDs)
- Breadboard & jumper wires
- 5V regulated power input

---

## 🧠 Future Ideas

- Add FFT for frequency-based visualizations
- Implement beat/tempo detection
- Design a 3D-printed enclosure with diffusion panel
- Add remote control via MQTT or BLE
