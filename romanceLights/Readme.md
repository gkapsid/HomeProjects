# Romance Light Project

This project is about a light controled by a smartphone app using WiFi locally.   
Two modes of operation were implemented:   
### WiFi mode 
The Neopixel LEDs are all light up at the same color, that is controlled by the smartphone app. White light and lights off are also available.   

### Rainbow mode (effect mode)   
The Neopixel LEDs implement a rainbow light effect. Other effects can be implemented. The examples of the Neopixel library give many suggestions.



## Hardware 

The project needs only a  few components, like an microcontroller, LEDs etc

The list of materials include:

1. ESP8266-01: It is sufficient for the current project, others can be used without any or much changes in the code like -12 or NODEMCU.
2. 3V3 voltage regulator like LD33V, 1117 (AMS1117, LM1117 etc) with the appropriate capacitors
3. The appropriate capacitors (2 for the regulator, 1 for the Neopixel stripe, 100 μF/16V, but anything higher than 10 μF can be used)
4. Neopixel strand (use as many LEDs can the power supply afford) 
5. A switch to turn the device on / off
6. pin headers
7. PCB

## Software   

The smartphone app was realized using the [RemoteXY](https://remotexy.com/) web based interface. It is free with the constrain that only 4 elements can be used in each app. The interface is included in the produced .ino file and it send to the RemoteXY app every time the module is connected with the app.
There are four alternatives for a project like that:   
1. The device is working as client to the existing WiFi network and can be controlled through the cloud from everywhere
2. The device is working as client to the existing WiFi network and can be controlled only locally.
3. The device is working as an access point and the smartphone is connected there as a client.
4. The device can be controlled using a Bluetooth connection (for Arduino based projects this can be easier to implement)

The configuration that is used for the second case is :    
- Ethernet wired and wireless
- ESP8266 based board
- WiFi on chip
- Arduino IDE

The resulting app has a radio button to select between two modes of operation and a module to select between color, white light, grey light and lights off operation.   

![remoteXYapp](https://user-images.githubusercontent.com/9993080/171569090-cd53ffad-1b51-4825-abc7-73ff495f0e73.png)
