# Illegaly parked car alarm

The project is about an alarm system  that detects if a car that parks in a special parking place that is for disabled drivers is occupied by other drivers that shouldn't park there

## The implemented scenarios

The driver parks to the specified parking place. The car is detected, a traffic light turns orange and a timer starts to tick.

If the driver knows a pin (the driver is entitled to park there) then inserts the pin code, the traffic light turns green and the timer resets and stops.

If  the driver doesn't know the pin code (the driver shouldn't park there) then either leaves or after a few seconds the traffic light turns red and a buzzer starts to buzz indicating that 
the driver should leave the position empty.

If the driver has forgotten the pin code or didn't catch up to type it then the traffic light turns red and the buzzer buzzes but if the pin code is given later then the traffic light
turns green and the buzzer stops.

## Materials used

* Arduino Nano
* IR sensor
* RGB LED
* Active buzzer
* Push Button Normal Open
* 9V battery holder
* Switch
* Cases for button and Arduino
* Cables

