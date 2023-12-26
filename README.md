# Pico Wheel
 
DIY sim racing wheel using a Raspberry Pi Pico and an AS5600 magnetic encoder

## Parts list

- Pi Pico (or Pico W)
- Micro USB cable
- [AS5600 magnetic encoder](https://www.amazon.com/MELIFE-Magnetic-Induction-Measurement-Precision/dp/B0B8ZDSH9Z/)
- 4x2mm diametric magnet
- [2x 6x6x4.3mm momentary push button](https://www.amazon.com/4-3mm-Momentary-Tactile-Button-Switch/dp/B0796QL57S/)
- 2x 608ZZ bearings
- 24x M3x8 bolts
- 2-4x M3x4 bolts
- 2x M3x20 bolts
- 2x M3x10 bolts
- 7x M3 nuts
- 1x M3x25 bolt
- 2-4x M2x4 bolts
- ~6x "Rainbow Loom" bands

## Firmware

The firmware is written in Arduino using the Arduino IDE and [arduino-pico](https://github.com/earlephilhower/arduino-pico)

The following libraries are used:

- [RobTillaart/AS5600](https://github.com/RobTillaart/AS5600)
- [benjaminaigner/Joystick](https://github.com/benjaminaigner/Joystick)
