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

# Constant Variable(s)
LED15 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (254, 194, 19),
    (249, 150, 33),
    (243, 111, 43),
    (241, 69, 39),
    (234, 29, 44),
    (215, 24, 111),
    (162, 30, 87)
]  # LEDs 1 - 15
LED14 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (254, 194, 19),
    (249, 150, 33),
    (243, 111, 43),
    (241, 69, 39),
    (234, 29, 44),
    (215, 24, 111),
    (0, 0, 0)
]  # LEDs 1 - 14
LED13 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (254, 194, 19),
    (249, 150, 33),
    (243, 111, 43),
    (241, 69, 39),
    (234, 29, 44),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 13
LED12 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (254, 194, 19),
    (249, 150, 33),
    (243, 111, 43),
    (241, 69, 39),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 12
LED11 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (254, 194, 19),
    (249, 150, 33),
    (243, 111, 43),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 11
LED10 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (254, 194, 19),
    (249, 150, 33),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 10
LED9 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (254, 194, 19),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 9
LED8 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (252, 226, 40),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 8
LED7 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (219, 222, 45),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 7
LED6 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (190, 216, 48),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 6
LED5 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (118, 192, 69),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 5
LED4 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (29, 173, 75),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 4
LED3 = [
    (3, 126, 170),
    (11, 152, 171),
    (14, 168, 132),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 - 3
LED2 = [
    (3, 126, 170),
    (11, 152, 171),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs 1 & 2
LED1 = [
    (3, 126, 170),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LED 1
NO_LED = [
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0),
    (0, 0, 0)
]  # LEDs off


# Create Function(s)
def sound_detector():
    while True:  # Indefinite loop
        time.sleep_ms(5)
        if x1_pin.value() != 0:  # Check digital signal
            print('ADC =', adc.read())  # Print adc value (0 - 4096)
            if adc.read() > 0:
                noise_meter.show(LED1)  # One LED on
            if adc.read() >= 150:
                noise_meter.show(LED2)  # Two LEDs on
            if adc.read() >= 300:
                noise_meter.show(LED3)  # Three LEDs on
            if adc.read() >= 450:
                noise_meter.show(LED4)  # Four LEDs on
            if adc.read() >= 600:
                noise_meter.show(LED5)  # Five LEDs on
            if adc.read() >= 750:
                noise_meter.show(LED6)  # Six LEDs on
            if adc.read() >= 900:
                noise_meter.show(LED7)  # Seven LEDs on
            if adc.read() >= 1050:
                noise_meter.show(LED8)  # Eight LEDs on
            if adc.read() >= 1200:
                noise_meter.show(LED9)  # Nine LEDs on
            if adc.read() >= 1350:
                noise_meter.show(LED10)  # Ten LEDs on
            if adc.read() >= 1500:
                noise_meter.show(LED11)  # Eleven LEDs on
            if adc.read() >= 1650:
                noise_meter.show(LED12)  # Twelve LEDs on
            if adc.read() >= 1800:
                noise_meter.show(LED13)  # Thirteen LEDs on
            if adc.read() >= 1950:
                noise_meter.show(LED14)  # Fourteen LEDs on
            if adc.read() >= 2100:
                noise_meter.show(LED15)  # Fifteen LEDs on
        else:
            noise_meter.show(NO_LED)  # Zero LEDs on


# Call Function
sound_detector()
