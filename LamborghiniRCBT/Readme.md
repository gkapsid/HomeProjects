# Lamborghini Blancpain RC BT toy car 

I had an old RC (40 MHz) toy car with limited functionality. The remote was only for forward backward movement and left, right turning. It was power by 5 AA 1,5 V batteries connected in series, totally 7,5 V, about 1000 mΑh. 

The existing electronics were removed, leaving inside only the motors. 

## Power Supply system
A new power supply system was implemented. It consists of two batteries Li Ion, size 18650, 4.2 V / 3500 mAh each, a battery charger with USB type C connector, two switches and a board to distribute raw 8.2 V and 5 V (through a 7805 voltage regulator) power to each board.

One switch is for switching on and off the whole system. The second switch has three positions. Center position is off with the batteries disconected from the rest of the system. This is used for long term storage of the toy car. The second position is used to connect the batteries in series when the system is in operation. That way the 8V voltage is achieved. The third position connects the batteries in parallel and thus they can be recharged with a typical 5V charger.

## Other subsystems
