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
    <img src="./EENG 163 - Final - Schematic.png" alt="EchoLux schematic" style="width: 100%; height: 100%; object-fit: cover; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
    <p style="text-align: center; margin-top: 10px;">Circuit schematic showing microphone amp and LED strip wiring</p>
  </div>

  <!-- Project Build Photo -->
  <div style="flex: 1 1 48%; max-width: 600px;">
    <img src="./EENG 163 - Final - Picture.png" alt="EchoLux Breadboard Build" style="width: 100%; height: 100%; object-fit: cover; border-radius: 8px; box-shadow: 0 2px 6px rgba(0,0,0,0.2);" />
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

```python
# Justin Richards - Final Project

# This code will allow you to set up both a sound sensor
# and LED strip (WS2812B) on your PyBoard.
# You will be able to get a voltage reading of sound amplitude
# that you can then use to control the LED strip.

# From the github link copy the file "ws2812.py" to your PyBoard (where boot.py and RaspberryPiPico.py are located)

# Connect A0 from sensor to X1 on PyBoard
# Connect D0 from sensor to X4 on PyBoard
# Connect X8 from PyBoard to DI (data in) on LED strip (green wire)
# Run a ground wire from the PyBoard to the sensor
# Run a ground wire from the PyBoard to the LED strip
# For best results power both the sensor and LEDs using a 5v power source

# Import Module(s)
import time
from ws2812 import WS2812  # https://github.com/JanBednarik/micropython-ws2812

# Assign Pin(s)
adc = pyb.ADC("X4")  # PyBoard Pin X4, Analog signal (0 - 4096)
x1_pin = pyb.Pin("X1", pyb.Pin.IN)  # PyBoard Pin X1, Digital signal (0 or 1)
noise_meter = WS2812(spi_bus=1, led_count=15, intensity=0.05)  # PyBoard Pin X8, Data to LED strip

# LED Color Arrays (LED1 to LED15, NO_LED)
LED15 = [ (3, 126, 170), (11, 152, 171), (14, 168, 132), (29, 173, 75), (118, 192, 69),
          (190, 216, 48), (219, 222, 45), (252, 226, 40), (254, 194, 19), (249, 150, 33),
          (243, 111, 43), (241, 69, 39), (234, 29, 44), (215, 24, 111), (162, 30, 87) ]
LED14 = LED15[:14] + [(0, 0, 0)]
LED13 = LED15[:13] + [(0, 0, 0)] * 2
LED12 = LED15[:12] + [(0, 0, 0)] * 3
LED11 = LED15[:11] + [(0, 0, 0)] * 4
LED10 = LED15[:10] + [(0, 0, 0)] * 5
LED9  = LED15[:9]  + [(0, 0, 0)] * 6
LED8  = LED15[:8]  + [(0, 0, 0)] * 7
LED7  = LED15[:7]  + [(0, 0, 0)] * 8
LED6  = LED15[:6]  + [(0, 0, 0)] * 9
LED5  = LED15[:5]  + [(0, 0, 0)] * 10
LED4  = LED15[:4]  + [(0, 0, 0)] * 11
LED3  = LED15[:3]  + [(0, 0, 0)] * 12
LED2  = LED15[:2]  + [(0, 0, 0)] * 13
LED1  = LED15[:1]  + [(0, 0, 0)] * 14
NO_LED = [(0, 0, 0)] * 15

# Create Function(s)
def sound_detector():
    while True:
        time.sleep_ms(5)
        if x1_pin.value() != 0:
            print('ADC =', adc.read())
            val = adc.read()
            if val > 0: noise_meter.show(LED1)
            if val >= 150: noise_meter.show(LED2)
            if val >= 300: noise_meter.show(LED3)
            if val >= 450: noise_meter.show(LED4)
            if val >= 600: noise_meter.show(LED5)
            if val >= 750: noise_meter.show(LED6)
            if val >= 900: noise_meter.show(LED7)
            if val >= 1050: noise_meter.show(LED8)
            if val >= 1200: noise_meter.show(LED9)
            if val >= 1350: noise_meter.show(LED10)
            if val >= 1500: noise_meter.show(LED11)
            if val >= 1650: noise_meter.show(LED12)
            if val >= 1800: noise_meter.show(LED13)
            if val >= 1950: noise_meter.show(LED14)
            if val >= 2100: noise_meter.show(LED15)
        else:
            noise_meter.show(NO_LED)

# Call Function
sound_detector()
