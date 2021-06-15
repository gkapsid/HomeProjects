# Lamborghini Blancpain RC BT toy car 

I had an old RC (40 MHz) toy car with limited functionality. The remote was only for forward backward movement and left, right turning. It was power by 5 AA 1,5 V batteries connected in series, totally 7,5 V, about 1000 mΑh. 

The existing electronics were removed, leaving inside only the motors. 

## Power Supply system
A new power supply system was implemented. It consists of two batteries Li Ion, size 18650, 4.2 V / 3500 mAh each, a battery charger with USB type C connector, two switches and a board to distribute raw 8.2 V and 5 V (through a 7805 voltage regulator) power to each board.

One switch is for switching on and off the whole system. The second switch has three positions. Center position is off with the batteries disconected from the rest of the system. This is used for long term storage of the toy car. The second position is used to connect the batteries in series when the system is in operation. That way the 8V voltage is achieved. The third position connects the batteries in parallel and thus they can be recharged with a typical 5V charger.

## Other subsystems

### BT RC subsystem
A HC-05 bluetooth module was used and it was interfaced directly with the Rx and Tx pins of the Arduino. Alternatively a HC-06 module can be used. For the module a software serial can also be used. The software serial solution allows the Arduino to be programmed with the need to remove the BT module (arduino of the UNO type). 

### H-bridge
A ready made L298D H-bridge module was used that is widely available and can easily be interfaced with Arduino boards. The board was given raw voltage (8V) so the motors work with at least 6V voltage across their leads. 

### Siren Horn
A typical active buzzer was used as a horn and it was connected directly on the Arduino pin. It can also be connected through a transistor. The sound is produced by the μControler using a for loop and increasing and decreasing the frequency of a tone. There are two problems here. The first problem is that this procedure is blocking. That means that while the sound is ascending or descending the μControler can't "hear" other commands. The second problem is that the sound production depends on what is received in the serial port of the μControler. So a command is received, the siren sounds and then stops. A new command should be given to continue its operation. 

Both problems were addressed with proper code so the car is still responsive while the siren is on and to repeat itself with a single "on" command and stop with an "off" command.

### Front and back light and alarm effect (simultaneous blink of all lights)
