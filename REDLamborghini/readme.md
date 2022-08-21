# Lamborghini Blancpain RC BT toy car 

I had an old RC (40 MHz) toy car with limited functionality. The remote was only for forward backward movement and left, right turning. It was power by 4 AA 1,5 V batteries connected in series, totally 6 V, about 1000 mΑh. 

The existing electronics were removed, leaving inside only the motors. 

## Implemented features
1. variable speed (ten levels)
2. moves forward, backward, left, right
3. horn - active buzzer - only digitalWrite HIGH an LOW, not tone().
4. front lights, white colored,  on off functionality
5. back lights, Red colored, on off functionality 
6. alarm lights (non blocking blink) - back lights blink orange (RGB LED), front lights blink white
7. security function when the app closes accidentaly (a 'D' is received) or the BT module disconnect (A1 BT LED Status - LED is blinking when unconnected, LED ON when connected with the app). (allStop) - new feature
8. Stops when there is an obstacle in front (HC-SR04 ultrasonic sensor)

## Power Supply system
A new power supply system was implemented. It consists of two batteries Li Ion, size 18650, 4.2 V / 3500 mAh each, a battery charger with USB type C connector and two switches.

One switch is for switching on and off the whole system. The second switch has three positions. Center position is off with the batteries disconected from the rest of the system. This is used for long term storage of the toy car. The second position is used to connect the batteries in series when the system is in operation. That way the 8V voltage is achieved. The third position connects the batteries in parallel and thus they can be recharged with a typical 5V charger.

## Other subsystems

### BT RC subsystem
A HC-06 bluetooth module was used and it was interfaced directly with the Rx and Tx pins of the Arduino. Alternatively a HC-05 module can be used. For the module a software serial can also be used. The software serial solution allows the Arduino to be programmed with the need to remove the BT module (arduino of the UNO type). 

### H-bridge
A custom made H-bridge module was implemented using the SN754410NE IC.

### Variable speed (Speed control feature)
The application is using a slider to send eleven commands (full stop, full speed and 9 speed levels)  that can be used to control the car's motor speed. This has been realised through mapping those levels to PWM levels (1,9, 30, 230). The full range (0, 255) of the Arduino PWM wasn't used because in very low voltages the motor stayed stall something that can lead to motor burn out. The full speed (255) was corresponded to the command q that is for full speed. The level 0 was corresponded to full stop. The car always begin in full speed and the user can adjust it afterwards.  

### Simple Horn
A typical active buzzer was used as a horn and it was connected directly on the Arduino pin. It can also be connected through a transistor. 
The active buzzer can be activated using a simple digitalWrite command.

### Front and back light and alarm effect (simultaneous blink of all lights)

The alarm effect was programmed so that it doesn't block the uControler and repeat itself after a single "on" command. That way the car can move, turn and change its speed while the lights blink offering a wonderful show!

The back lights were implemented using RGB LEDs. That way the lights are normally red as backlights and turn to orange when the alarm function is used!

## Bill of Materials

* 1 Arduino board (Nano was used, but also Pro Mini, UNO, Leonardo etc can be used with almost no code correction)
* 1 HC-05 or 06 BT module (or any other module can be interfaced with Arduino) 
* 1 H-bridge custom made or of the shelve (SN754410NE IC was used to build a custom one on the same PCB with the Arduino)
* LEDs (simple and RGB) and resistances
* 2 18650 Li - Ion batteries with cases
* 1 Lithium battery charger module (with protection) like https://grobotronics.com/lithium-battery-charger-and-protection-module-1a-usb-c-tp4056.html 
* 1 active buzzer
* jumper cables
* 1 slide switch DPDT On-Off-On (or ON-ON) Circuit found https://42bots.com/resources/a-circuit-to-use-2-single-cell-li-po-li-on-batteries-in-series-and-charge-them-in-parallel/
* 1 HC-SR04 ultrasonic distance sensor or other distance sensor.  
