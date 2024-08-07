# Two Wheeled robot car with 3 modes of operation

## Intro

This folder contains info about the construction (hardware and software) of a wheeled robot that has three modes of operation.
The modes are:
1. Simple obstacle avoidance
2. Line follower
3. Line follower with simple obstacle avoidance

## Modes of operation
Modes are selected through a mode selection hardware switch. The switch is of the ON - ON - OFF kind.
### Simple obstacle avoidance
The implemented algorithm  is simple yet effective. The robot goes forward. If the ultrasonic sensor detects an obstacle  then:
1. The robot stops
2. Turns the ultrasonic sensor right and left and detects the distance.
3. Compares the measured distance and turns towards the direction of the bigger value.

### Line follower
A simple follow line algorithm is implemented. Two sensors at the front part of the robot are used.

### Line follower with simple obstacle avoidance
The robot follows a line but if the ultrasonic detector detects an obstacle then stops. If the obstacle is removed the robot continues to follow the line.

## Video presentation
[Two Wheeled robot car with 3 modes of operation](https://youtu.be/xsDr1Te-Kb8)
