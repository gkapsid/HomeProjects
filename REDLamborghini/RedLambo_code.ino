//#include <MedianFilter.h>
//#include <SharpDistSensor.h>


//gkapsid
//V4 - version with motor bridge IC for lamborgini
//the forward backward routines are changed. 4 wheeled vehicle with one motor for both back left and right wheels.
// turns left right using a second motor as steering wheel controled by the bridge also
// IC SN754410NE used for a  custom on board H-bridge
// Arduino Nano
//HC-06 Hacked Bluetooth module
// hack to export hardware, connection status pin
// more info https://mcuoneclipse.com/2013/06/19/using-the-hc-06-bluetooth-module/
// pin KEY (26) was connected to STATE pinout


//car features
//*************************************************
// variable speed (ten levels)
// moves forward, backward, left, right
// horn - active buzzer - only digitalWrite HIGH an LOW, not tone().
// front lights white on off
// back light on off -> Red
// alarm lights (non blocking blink) - back lights blink orange (RGB LED), front lights blink white
//security function when the app closes accidentaly (A 'D' is received) or the BT module disconnect (A1 BT LED Status - LED is blinking when unconnected, LED ON when connected with the app). (allStop) - new feature
// stops when there is an obstacle in front (AO -> SHARP distance sensor)
//************************************************
/*
  Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin17 (A2)
        Echo: Echo (OUTPUT) - Pin 18 (A3)
        GND: GND
 */
//latest version

char _ABVAR_1_entoli = ' ' ;

int carSpeed = 255;
const long BLINK_INTERVAL = 800;
int ledState = LOW;   // ledState used to set the LED
unsigned long previousMillis = 0;
bool alarmON = false;
//bool sirenON = false;
float sensorValueMean;
//bool obstacle = false;

int trigPin = 17;    // Trigger
int echoPin = 18;    // Echo
long duration;
long cm = 150;


# define LED_PIN 9
# define HORN 12
# define BACK_G 3 // green from RGB LED
# define BACK_R 2 // Red from RGB LED

//int isConnectedRead = 0;


// Analog pin to which the sensor is connected
//const byte sensorPin = A0;

// Window size of the median filter (odd number, 1 = no filtering)
//const byte medianFilterWindowSize = 3;

// Create an object instance of the SharpDistSensor class
//SharpDistSensor sensor(sensorPin, medianFilterWindowSize);

void setup()
{
  Serial.begin(9600);
 // Set sensor model
 // sensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
  
  pinMode(2, OUTPUT); // back Red LED from RGB
  pinMode(3, OUTPUT); // back Green LED from RGB
  pinMode(4, OUTPUT); //helper pin to activate alarm lights
  pinMode(5, OUTPUT); // motor 1 TTL Logic
  pinMode(6, OUTPUT); // motor 1 TTL Logic
  pinMode(7, OUTPUT); //helper pin for back lights and alarm function
  pinMode(8, OUTPUT); //NC
  pinMode(9, OUTPUT); // front lights
  pinMode(10, OUTPUT); // motor 2 TTL Logic
  pinMode(11, OUTPUT); // motor 2 TTL Logic
  pinMode(12, OUTPUT); // horn buzzer
  // pinMode(13, OUTPUT);
pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{

  if ((  Serial.available()  > ( 0 ) ))
  {
    _ABVAR_1_entoli = Serial.read();

    //******************************************************************
    // forward movement
    if (( ( _ABVAR_1_entoli ) == ( 'F' ) ))
    {
      forward();

    }
    else
    {
      //backwards
      if (( ( _ABVAR_1_entoli ) == ( 'B' ) ))
      {

        backward();
      }
      else
      {
        //left
        if (( ( _ABVAR_1_entoli ) == ( 'L' ) ))
        {


          left();
        }
        else
        {
          //right
          if (( ( _ABVAR_1_entoli ) == ( 'R' ) ))
          {
            right();
          }
        }
      }
    }
    // full stop
    // 1. When the user doesn't use any of the arrows - an 'S' is transmitted
    // 2. When there is an obstacle in front of the  car.
    // 3. When the app disconnects - a 'D' is transmitted before disconnection
    // 4. When the BT is not connected (A1 pin)

    if ((( _ABVAR_1_entoli ) == ( 'S' )) || (( _ABVAR_1_entoli ) == ( 'D' ))) //|| (analogRead(A1) > 500)  ) //before the app disconnects from BT HC-0x sends a D as a protection switch
    {
      stopAll();
    }


    //Forward left
    if (( ( _ABVAR_1_entoli ) == ( 'G' ) ))
    {

      forwLeft();
    }
    // forward right
    if (( ( _ABVAR_1_entoli ) == ( 'I' ) ))
    {

      forwRight();
    }

    //back left
    if (( ( _ABVAR_1_entoli ) == ( 'H' ) ))
    {

      backLeft();
    }

    // back right
    if (( ( _ABVAR_1_entoli ) == ( 'J' ) ))
    {

      backRight();
    }
    //********************************************************************************************************

    // LIGHTS ****************************************************************************************************
    //front lights on
    if (( ( _ABVAR_1_entoli ) == ( 'W' ) ))
    {
      digitalWrite(4, HIGH);
      digitalWrite(9, HIGH);

    }
    // front lights off

    if (( ( _ABVAR_1_entoli ) == ( 'w' ) ))
    {
      digitalWrite(4, LOW);
      digitalWrite(9, LOW);
    }


    //back lights on
    if (( ( _ABVAR_1_entoli ) == ( 'U' ) ))
    {
      digitalWrite(BACK_R, HIGH); // Red LED ON from RGB LED
      digitalWrite(BACK_G, LOW); // Green OFF
      digitalWrite(7, HIGH); // is it necessary?
    }
    //back lights off
    if (( ( _ABVAR_1_entoli ) == ( 'u' ) ))
    {

      digitalWrite(BACK_R, LOW);
      digitalWrite(BACK_G, LOW);
      digitalWrite(7, LOW);
    }

    //alarm on
    if (( ( _ABVAR_1_entoli ) == ( 'X' ) ))
    {
      //non blocking blink when a pin is set to high
      digitalWrite(4, HIGH);
      alarmON = true;

    }

    //alarm lights off
    if (( ( _ABVAR_1_entoli ) == ( 'x' ) )) {
      //  digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      // digitalWrite(BACK_R, LOW);
      digitalWrite(BACK_G, LOW);
      alarmON = false;
    }
    // LIGHTS END **********************************************************************************************

    //horn on
    if ( ( _ABVAR_1_entoli ) == ( 'V' ) )
    {
      digitalWrite(HORN, HIGH); // pin 12
    }

    //horn off
    if (( ( _ABVAR_1_entoli ) == ( 'v' ) ))
    {

      digitalWrite(HORN, LOW);
    }

    //speed control --------------------------------------------------------------------------------------------------------------------------------------
    if (( ( _ABVAR_1_entoli ) == 'q') || ( ( _ABVAR_1_entoli ) == '0') || ( ( _ABVAR_1_entoli ) == '1') || (( _ABVAR_1_entoli ) == '2' ) || (( _ABVAR_1_entoli ) == '3' ) || (( _ABVAR_1_entoli ) == '4' ) || (( _ABVAR_1_entoli ) == '5' ) || (( _ABVAR_1_entoli ) == '6' ) || (( _ABVAR_1_entoli ) == '7' ) || (( _ABVAR_1_entoli ) == '8' ) || (( _ABVAR_1_entoli ) == '9' ))
    {
      // full speed
      if ( ( _ABVAR_1_entoli ) == 'q') {
        carSpeed = 255;

      }
      // full stop
      else if ( ( _ABVAR_1_entoli ) == '0') {
        carSpeed = 0;

      }
      // speed level to PWM level mapping
      else {
        int rcvSpeed = _ABVAR_1_entoli - '0';
        carSpeed = map(rcvSpeed, 1, 9, 50, 230);

      }
    }
    // end speed control -------------------------------------------------------------------------------------------------------------------------------------
 
  //  distanceMeas();
 //Serial.println(cm);
  // if (cm <25) park();
  
  }

  distanceMeas();
 //Serial.println(cm);
  if (cm <25) park();
 



/*unsigned int distance = sensor.getDist();
//Serial.println(distance);
delay(10);
  // if obstacle  is detected in front of the car stop
if ((distance > 160) && (distance < 230)) { // needs a flag variable that will be reset when a key (like front or back) is used
   // obstacle = true;
   // if (obstacle) {
     Serial.print(distance );
  Serial.println(" parking");
      park();
  //  }*/
  
//  } else {
 //   obstacle = false;
 // }

  //Stop if BT connection is lost
 /* checkBTConnectivity();

  //isConnectedRead = analogRead(A1);
  if ( sensorValueMean < 620) {
    stopAll();
  }
*/
  // helper code for horn and alarm light feature
  // increases responsiveness of the code while those two features are operating

  if (digitalRead(4) == HIGH && alarmON == true) {
    // non blocking blink - initiate alarm function
    alarmLights();

  }
  else if ((digitalRead(4) == HIGH) && (alarmON == false)) {
    digitalWrite(9, HIGH); //turn on FRONT lights

  }
  else if ((digitalRead(7) == HIGH) && (alarmON == false)) {
    digitalWrite(BACK_R, HIGH); // to be the RED light
    digitalWrite(BACK_G, LOW);
    digitalWrite(7, LOW);
  }
  else if (digitalRead(4) == LOW) {
    digitalWrite(9, LOW); //turn off front lights after alarm function
    //  digitalWrite(8, LOW);
    //  alarmON = false;
  }
  // turn off alarm function and all lights are off
  else if (alarmON == false) {
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(BACK_R, LOW);
    digitalWrite(BACK_G, LOW);

  }
  else if (digitalRead(7) == LOW) {
    digitalWrite(BACK_R, LOW); //turn off back light
    digitalWrite(BACK_G, LOW);
  }

  /*  if (sirenON == true) {
      sirenHorn();
    }*/

}

void alarmLights() {
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
  int GREEN_VAL = 0;

  if (currentMillis - previousMillis >= BLINK_INTERVAL) {
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      GREEN_VAL = 120;

    }
    else if (ledState == HIGH) {
      ledState = LOW;
      GREEN_VAL = 0;

    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_PIN, ledState); //front lights
    delay(2);

    digitalWrite(BACK_R, ledState); // backRED pin from RGB
    analogWrite(BACK_G, GREEN_VAL); // backGREEN pin from RGB

    // save the last time you blinked the LED
    previousMillis = currentMillis;

  }

}

void stopAll() {
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void forward() {
 // obstacle = false;
  analogWrite(10, carSpeed);
  digitalWrite(11, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

}

void backward() {
  //obstacle = false;
  digitalWrite(10, LOW);
  analogWrite(11, carSpeed);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

}

void left() {
  //obstacle = false;
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void right() {
  //obstacle = false;
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void forwLeft() {
  //obstacle = false;
  digitalWrite(11, LOW);
  analogWrite(10, carSpeed);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void forwRight() {
  //obstacle = false;
  digitalWrite(11, LOW);
  analogWrite(10, carSpeed);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void backLeft() {
 // obstacle = false;
  digitalWrite(10, LOW);
  analogWrite(11, carSpeed);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void backRight() {
 // obstacle = false;
  digitalWrite(10, LOW);
  analogWrite(11, carSpeed);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}

void distanceMeas() {
   // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
}
void park() {
 
 stopAll();
backward();
  /*digitalWrite(10, LOW);
  analogWrite(11, carSpeed);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);*/
  delay(50);
 stopAll();
//  obstacle = false;

}
/*void checkBTConnectivity() {
  int sensorValue = analogRead(A1);
  float sensorSum = 0;
  for (int i = 0; i < 5; i++) {
    sensorValue = analogRead(A1);
    sensorSum = pow(sensorValue, 2) + sensorSum;
    //Serial.println(sensorSum);
    delay(10);
  }
 
  sensorValueMean = sqrt(sensorSum / 5);
}*/
