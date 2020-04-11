# CS207- Project Files
# D&Dice Roller

This project is a dice roller made specifically for Dungeons & Dragons. When playing D&D there are a large amount of different dice needed when rolling for spells, to attack, or for damage. 

This dice roller helps the user limit the amount of dice needed and helps save time when they need to roll damage for a fireball.

The project is made with an Arduino Uno, and uses a 4x4 keypad as an input while using a LCD screen and speaker as an output.

![Complete](https://github.com/pandacake59/CS207-Files/blob/master/img/Complete.jpg)

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
![Project_schematic](https://github.com/pandacake59/CS207-Files/blob/master/img/Project_schematic.jpg)

The breadboard diagram shown below will help give another view of the connections needed for the D&Dice Roller.
![CS207_BoardSchematic](https://github.com/pandacake59/CS207-Files/blob/master/img/CS207_BoardSchematic.png)

The first step would be to solder (or some otherway of connecting) eight pins which will allow the keypad to be used as an input device. And then connecting the pins onto the digital ports from numbers 2~9.
![Keypad](https://github.com/pandacake59/CS207-Files/blob/master/img/Speaker.jpg)

Next would be connecting the I2C of the LCD screen to the Arduino board
**GND -- GND**
**VCC -- 5V**
**SDA -- A4**
**SCL -- A5**

![LCD](https://github.com/pandacake59/CS207-Files/blob/master/img/LCD.jpg)

The last part will be creating the speaker amplification circuit and connecting it to digital pin 11.

Optionally you can include a power supply to connect directly to the Arduino Uno board to allow for more mobility

The completed build will look something like this
![Speaker](https://github.com/pandacake59/CS207-Files/blob/master/img/Speaker.jpg)


Usage
===================
1.	On the keypad pick the amount of dice you would like to roll between 1-99.
2.	Press the D key to input the amount of dice.
3.	Pick the sided dice you would like to roll between 1-99.
4.	(Optional) press the + or – key on the keypad if you would like to add any modifiers to the roll.
5.	Press the enter key to roll your dice.
6.	Press the C key afterwards or during any time when inputting the values.
7.	Press the backspace key if any mistakes were made.

*

Credits
===================
Michael Smith - Speaker output for Arduino

Junez Riyaz - Audio Amplifier using transistor
