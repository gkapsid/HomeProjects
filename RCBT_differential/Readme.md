# BT remote controlled car with features

This is another BT remote controlled car project. 

The features implemented are: 

- Differential drive (two motors, one per wheel)
- BT controlled
- Forward backward left right move
- Speed control (Slow, progressive faster, max speed) using a slider
- Front and back lights
- Alarm light on off (police lights implemented with another device with 555 IC)
- Horn (active buzzer)

The car is powered by two 18650 batteries.

Bill of materials: 

- Arduino micro
- HC-05 (or 06) bluetooth module
- LED's
- motor bridge (motor bridge IC SN754410 was used but L298N H-Bridge Stepper Motor Driver Module can be used)
- 18650 battery holder
- transistors (like 2N2222) used as switch for the police lights

Police lights details can be found  https://www.tinkercad.com/things/l7k0AJErPYV  and https://www.youtube.com/watch?v=nB_cS-tixzw. 
