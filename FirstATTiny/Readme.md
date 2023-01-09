# First ATTiny projects

## Introduction

This folder contains my first two projects with the ATTiny 25/45/85 series ucontroller.

## Description

The first project implements a car and pedestrian traffic light (5 outputs) without any input from the user. The ATTiny45 uprocessor was used timed at the default 1 MHz. 

The delay() function seems to work different here propably due to different clocks between the Arduino (16 MHz) and the ATTiny. That why the times in the delay function seem to be considerably long. So, test the delay times and check appropriate values. 

The second project is the control of two NEOPIXELs and the read of a custom light sensor. If the light is above some value the lights are on and light according a "rainbow" effect. Other effects can also be implemented. 

The ATTiny45 uprocessor that was used was set to operate at 8 MHz internal clock instead the default 1 MHz.

Both projects are modification of older implementations, replacing the Arduino boards that were used back then. That way an Arduino micro and an Arduino Leonardo were spared for future, larger projects. 

The third project was added later and it was designed from scratch on a ATTiny85 μC. 

It is a decorative light. It can switch between 3 plain colors (white, red and blue) and a rainbow effect. This time a rotary encoder with switch was used to achieve the different operations. The switch is used to move from one color (or effect) to the other. The rotary function of the encoder is used to change the brightness of the LEDs.

The code can be used for many other colors and effects. 

The code to use  the rotary encoder with the ATTiny85 was from http://angryyak.co.uk/blog/using-a-rotary-encoder-with-arduino-or-attiny85/ 

The original idea was from https://www.hackster.io/alvaroportu4/bed-light-neopixel-2e75e3 


## More Info

The first two projects are presented in brief in the YT video: https://www.youtube.com/watch?v=c2E2xMsiNzU

The Decorative Light is presented in the video: https://youtu.be/ds3N2ZJQoPE .

They are also  implemented and simulated in Tinkercad where someone can find information about the connections between the elements and the code that it was used. 

Project 1 Traffic Light [Tinkercad](https://www.tinkercad.com/) link: https://www.tinkercad.com/things/kTIhfkIL52w 

Project 2 NEOPIXEL light [Tinkercad](https://www.tinkercad.com/) link: https://www.tinkercad.com/things/2pyHOAFEE6E 

Project 3 ATTiny decorative light [Tinkercad](https://www.tinkercad.com/) link: https://www.tinkercad.com/things/11Gc88x2S0x

The code is also available here in github.

Procedure for bootloader burning and ATTiny programming: https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829


## Bill of materials

### Project 1 Traffic Light

1. ATTiny45
2. IC holder (8 pins, optional)
3. LEDs different colours (2xRed, 2xGreen, 1xYellow)
4. Coin Battery holder and the appropriate coin battery. 
5. A prototyping board
6. Cables
7. Case

### Project 2 NEOPIXEL LED lamp

1. ATTiny45
2. IC holder (8 pins, optional)
3. NEOPIXEL addressable LEDs (a few)
4. Light Dependent Resistor (LDR) and simple resistors (a few 1k)
5. 5 V power supply
6. A prototyping board
7. Cables
8. Case


### Poject 3 Decorative Light

1. ATTiny85
2. IC holder (8 pins, optional)
3. NEOPIXEL addressable LEDs (a few)
4. Rotary encoder with switch
5. 5 V power supply
6. A prototyping board
7. Cables
8. Case
