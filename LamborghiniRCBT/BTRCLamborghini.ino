//22/5/2021 gkapsid
//V3 - version with motor bridge IC for lamborgini
//the forward backward routines are changed. vehicle with one motor for both left and right wheels.
// turns left right using a second motor as steering wheel controled by the bridge also
// L298N module bridge was used
// Arduino Mini Pro
//HC-05 Bluetooth module

//car features
//*************************************************
// variable speed
// moves forward, backward, left, right
// siren sound horn
//alarm lights (non blocking blink)
//front lights on off
//back light on off
//************************************************

//latest version 12/6/2021


char _ABVAR_1_entoli = ' ' ;

int carSpeed = 255;
const long BLINK_INTERVAL = 800;
int ledState = LOW;   // ledState used to set the LED
unsigned long previousMillis = 0;
bool alarmON = false;
bool sirenON = false;

# define LED_PIN 9
# define HORN 13

void setup()
{
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);


  //pinMode(, OUTPUT);
}

void loop()
{

  if (( ( Serial.available() ) > ( 0 ) ))
  {
    _ABVAR_1_entoli = Serial.read();
    //******************************************************************
    // forward movement
    if (( ( _ABVAR_1_entoli ) == ( 'F' ) ))
    {
      //  Serial.print(_ABVAR_1_entoli);
      analogWrite(5, carSpeed);
      // digitalWrite(3, LOW);
      digitalWrite(6, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);

    }
    else
    {
      //backwards
      if (( ( _ABVAR_1_entoli ) == ( 'B' ) ))
      {
        // digitalWrite(3, HIGH);
        // digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        analogWrite(6, carSpeed);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
      }
      else
      {
        //left
        if (( ( _ABVAR_1_entoli ) == ( 'L' ) ))
        {

          //    digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
        }
        else
        {
          //right
          if (( ( _ABVAR_1_entoli ) == ( 'R' ) ))
          {
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(10, LOW);
            digitalWrite(11, HIGH);
          }
        }
      }
    }
    // full stop
    if (( ( _ABVAR_1_entoli ) == ( 'S' ) ))
    {
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    }

    //Forward left
    if (( ( _ABVAR_1_entoli ) == ( 'G' ) ))
    {
      //digitalWrite(4, LOW);
      digitalWrite(6, LOW);
      analogWrite(5, carSpeed);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    }
    // forward right
    if (( ( _ABVAR_1_entoli ) == ( 'I' ) ))
    {
      // digitalWrite(4, LOW);
      digitalWrite(6, LOW);
      analogWrite(5, carSpeed);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    }

    //back left
    if (( ( _ABVAR_1_entoli ) == ( 'H' ) ))
    {
      //  Serial.println(carSpeed);
      //digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      analogWrite(6, carSpeed);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    }

    // back right
    if (( ( _ABVAR_1_entoli ) == ( 'J' ) ))
    {
      //digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      analogWrite(6, carSpeed);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    }
    //********************************************************************************************************

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
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
    }
    //back lights off
    if (( ( _ABVAR_1_entoli ) == ( 'u' ) ))
    {
      // digitalWrite(10,LOW);
      digitalWrite(7, LOW);

      digitalWrite(8, LOW);
    }

    //horn on
    if ( ( _ABVAR_1_entoli ) == ( 'V' ) )
    {
      sirenON = true;
    }

    //horn off
    if (( ( _ABVAR_1_entoli ) == ( 'v' ) ))
    {
      noTone(HORN);
      digitalWrite(HORN, LOW);
      sirenON = false;
    }
    //alarm on
    if (( ( _ABVAR_1_entoli ) == ( 'X' ) ))
    {
      //non blocking blink when a pin is set to high
      digitalWrite(4, HIGH);
      alarmON = true;

    }



    if (( ( _ABVAR_1_entoli ) == ( 'x' ) )) {
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      alarmON = false;
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
    //Serial.println(carSpeed);
  }

  // helper code for horn and alarm light feature
  // increases responsiveness of the code while those two features are operating

  if (digitalRead(4) == HIGH && alarmON == true) {
    // non blocking blink
    // Serial.println("alarm on ");
    alarmLights();

  }
  else if ((digitalRead(4) == HIGH) && (alarmON == false)) {
    digitalWrite(9, HIGH);

  }
  else if ((digitalRead(7) == HIGH) && (alarmON == false)) {
    digitalWrite(8, HIGH);
  }
  else if (digitalRead(4) == LOW) {
    digitalWrite(9, LOW);
    //  digitalWrite(8, LOW);
    //  alarmON = false;
  }
  else if (alarmON == false) {
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);

  }
  else if (digitalRead(7) == LOW) {
    digitalWrite(8, LOW);
  }

  if (sirenON == true) {
    sirenHorn();
  }

}

void alarmLights() {
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
  // Serial.println("I'm in alarm");

  if (currentMillis - previousMillis >= BLINK_INTERVAL) {
    // if the LED is off turn it on and vice-versa:
    //Serial.println("I'm here");
    if (ledState == LOW) {
      ledState = HIGH;
      //Serial.print("LED :");
      //Serial.println(ledState);

    }
    else if (ledState == HIGH) {
      ledState = LOW;
      // Serial.print("LED :");
      // Serial.println(ledState);

    }
    // Serial.print("LED :");
    // Serial.println(ledState);
    // set the LED with the ledState of the variable:
    digitalWrite(LED_PIN, ledState);
    delay(2);
    digitalWrite(8, ledState);
    // save the last time you blinked the LED
    previousMillis = currentMillis;

  }
  // Serial.print("alarmON ");
  // Serial.println(alarmON);
  // Serial.println(digitalRead(4));
}

void sirenHorn() { //very blocking procedure

  int i = 0;

  for (i = 400; i < 900; i++) {
    tone(HORN, i);
    delay(5);
    if (( ( Serial.available() ) > ( 0 ) ))
    {
      break;
      _ABVAR_1_entoli = Serial.read();
      if (( ( _ABVAR_1_entoli ) == ( 'v' ) ))
      {
        // digitalWrite(10,LOW);
        noTone(HORN);
        digitalWrite(HORN, LOW);
        sirenON = false;
        break;
      }
    }
  }
  for (i = 1000; i > 400; i--) {
    tone(HORN, i);
    delay(5);
    if (( ( Serial.available() ) > ( 0 ) ))

    {
      break; //helps in multitasking

      _ABVAR_1_entoli = Serial.read();
      if (( ( _ABVAR_1_entoli ) == ( 'v' ) ))
      {
        // digitalWrite(10,LOW);
        sirenON = false;
        noTone(HORN);
        digitalWrite(HORN, LOW);
        break;
      }
    }
  }
}


