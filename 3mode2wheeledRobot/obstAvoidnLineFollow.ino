// https://circuitdigest.com/microcontroller-projects/arduino-uno-line-follower-robot
// https://www.instructables.com/Obstacle-Avoiding-Robot-Arduino-1/

/*
   Three different scenarios are implemented
   1. Follow line with two sensors. The logic is that if the left sensor sees the black line then turn left an if the right sensor sees the black line then turn right.
   If none of the two sensors see black line go straight.
   2. Obstacle avoidance using a ultrasound sensor and a servo motor. Go straight and if ther is an obstacle then turn the ultrasound sensor right and left and measure the distance
   Turn to that direction that the distance is larger.
   3. Follow line and avoid obstacle. Follow the line and if you detect an obstacle then stop. If the obstacle is removed then continue.

   The scenario is implemented using an ON - ON - OFF switch in PULLUP configuration
*/
//enA and enB jumpered to 5V (always high)
#define in1 11 //Motor1  L293 Pin in1
#define in2 10 //Motor1  L293 Pin in2
#define in3 9 //Motor2  L293Pin in3
#define in4 8 //Motor2  L293 Pin in4
#define R_S 13 // Right sensor
#define L_S 12 // Left sensor
#define  pushButtonA 1 // Used to select mode
#define  pushButtonB 2 // Used to select mode

// We need to choose between 3 modes of operation that's why two bits are necessary 

// Obstacle avoidance related

#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//sensor pins
#define trig_pin 4 //analog input 1
#define echo_pin 5 //analog input 2

#define maximum_distance 200

int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup() {

  pinMode(R_S, INPUT);
  pinMode(L_S, INPUT);
  //  pinMode(enA, OUTPUT); // enA always HIGH Hardwired
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //  pinMode(enB, OUTPUT); // enB always HIGH
  pinMode(pushButtonA, INPUT);
  pinMode(pushButtonB, INPUT);

  servo_motor.attach(3); //our servo pin

  servo_motor.write(75);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  //Read those inputs to determine mode of operation
  int buttonStateA = digitalRead(pushButtonA);
  int buttonStateB = digitalRead(pushButtonB);
  if (!buttonStateA) { //pullup configuration with external resistors
    lineFollow();
  }
  else if (!buttonStateB) {//pullup configuration with external resistors
    obstAvoid();
  }
  else { //line follow with  obstacle avoidance (stop before obstacle)
    distance = readPing();
    if (distance < 20) {
      stopAll();
    }
    else {
      lineFollow();
    }

  }

}

void lineFollow() {
  if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 1)) {
    forward();
  }
  else if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 1)) {
    turnRight();
  }
  else if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) {
    turnLeft();
  }
  else if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) {
    stopAll();
  }
}

void obstAvoid() {
  int distanceRight = 0;
  int distanceLeft = 0;
distance = readPing();
  delay(50);

  if (distance <= 25) {
    stopAll();
    delay(200);

    distanceRight = lookRight();
    delay(100);
    distanceLeft = lookLeft();
    delay(100);

    if (distance >= distanceLeft) {
      turnRight();
      delay(300); //calibrate this value according the wanted turning angle - faster motors less time
      
    }
    else {
      turnLeft();
      delay(300); //calibrate this value according the wanted turning angle - faster motors less time
    
    }
  }
  else {
    forward();
  }
 
}



void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
 digitalWrite(in1, HIGH);  //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, HIGH);  //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forword Pin
}

void turnRight() {
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void stopAll() {
  digitalWrite(in1, LOW); //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, LOW); //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forward Pin
}

// measufre distance rightside the robot
int lookRight() {
  servo_motor.write(30);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(80);
  return distance;
}

// measure distance leftside the  robot
int lookLeft() {
  servo_motor.write(140);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(80);
  return distance;
  delay(100);
}

// read distance
int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}
