# Arduino-WS2812b-Strip-IR-controlled
Code for my arduino prototyped board to controll WS2812b strip by IR controll.
This code combines the Neopixel library from Adafruit and the IRLremote library to create a remote controllable LED strip.
# Actually, we need two arduino microcontrollers
I discovered that to make an arduino plate to control these LEDs using the NeoPixel library and the IR-library we need two arduinos.

This is due to the fact that these two libraries do not work very well if we add complicated animations to LEDs. In this case, the first microcontroller will be responsible for managing and changing the animations, and the second will receive IR signals regardless of what the first one does.
