# CS207- Project Files
# D&Dice Roller

This project is a dice roller made specifically for Dungeons & Dragons. When playing D&D there are a large amount of different dice needed when rolling for spells, to attack, or for damage. 

This dice roller helps the user limit the amount of dice needed and helps save time when they need to roll damage for a fireball.

The project is made with an Arduino Uno, and uses a 4x4 keypad as an input while using a LCD screen and speaker as an output.

[img_placeholder]

Repository Contents
===================

    ├── build                  # Compiled files 
    ├── img                    # Image files
    ├── lib                    # Library files
    ├── schematic              # Schematic files
    ├── src                    # Source files
    ├── LICENSE
    └── README.md

Requirements and Materials
===================
Libraries:
* LCD screen library for **I2C LiquidCrystal_I2C.zip**
* Keypad library **index.zip**

Materials:
* 1 x Arduino Uno R3
* 1 x Mini Metal Speaker w/ Wires - 8 ohm 0.5W
* 1 x 4x4 Keypad
* 1 x 16x2 LCD Screen
* 1 x 2.2k Resistor
* 1 x 10uF Capacitor
* 1 x KSP 2222A NPN Transistor
* 1 x Breadboard
* Wires

Build Instructions
===================
This will be the build guide in order to recreate the D&Dice Roller.

The schematic shown below will help identify the wires and the connections needed from each input/output to the pins on the Arduino.
[schematic_placeholder]

The breadboard diagram shown below will help give another view of the connections needed for the D&Dice Roller.
[board_placeholder]

The first step would be to solder (or some otherway of connecting) eight pins which will allow the keypad to be used as an input device. And then connecting the pins onto the digital ports from numbers 2~9.
[picture placeholder]

Next would be connecting the I2C of the LCD screen to the Arduino board
**GND -- GND**
**VCC -- 5V**
**SDA -- A4**
**SCL -- A5**

The last part will be creating the speaker amplification circuit and connecting it to digital pin 11.

Optionally you can include a power supply to connect directly to the Arduino Uno board to allow for more mobility

The completed build will look something like this
[picture placeholder 2]


Usage
===================

*

Credits
===================
