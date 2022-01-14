//22/5/2021 gkapsid
//V4 - version with motor bridge IC SN754410  https://www.ti.com/lit/ds/symlink/sn754410.pdf
// two wheeled vehicle one motor per wheel
//sketch for the oldest robot platform

//control android app https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en&gl=US

//latest version 01/06/2021

//car features
// BT controlled HC-05 or 06
// lights
//Alarm light on off (police lights implemented with another device with 555 IC)
//Horn (active buzzer)
// Speed control
//forward backward left right move
//differential drive (two motors one per wheel)

//Arduino pro mini implementation
char _ABVAR_1_entoli = ' ' ;

int carSpeed;

void setup()
{
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

}

void loop()
{

  if (( ( Serial.available() ) > ( 0 ) ))

  {
    _ABVAR_1_entoli = Serial.read();
    Serial.println(_ABVAR_1_entoli);
// forward move
    if (( ( _ABVAR_1_entoli ) == ( 'F' ) ))
    {
      //  Serial.print(_ABVAR_1_entoli);
      digitalWrite(3, LOW);
      analogWrite(5, carSpeed);
      analogWrite(6, carSpeed);
      digitalWrite(9, LOW);

    }
    else
    {
      //backwards move
      if (( ( _ABVAR_1_entoli ) == ( 'B' ) ))
      {
        analogWrite(3, carSpeed);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        analogWrite(9, carSpeed);
      }
      else
      {
        // move left
        if (( ( _ABVAR_1_entoli ) == ( 'L' ) ))
        {
          digitalWrite(3, LOW);
          analogWrite(5, carSpeed);
          digitalWrite(6, LOW);
          analogWrite(9, carSpeed);
        }
        else
        {
          //right
          if (( ( _ABVAR_1_entoli ) == ( 'R' ) ))
          {
            analogWrite(3, carSpeed);
            digitalWrite(5, LOW);
            analogWrite(6, carSpeed);
            digitalWrite(9, LOW);
          }
        }
      }
    }
    // full stop
    if (( ( _ABVAR_1_entoli ) == ( 'S' ) ))
    {
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(9, LOW);
    }

    //Forward left
    if (( ( _ABVAR_1_entoli ) == ( 'G' ) ))
    {
      digitalWrite(3, LOW);
      analogWrite(5, carSpeed);
      digitalWrite(6, LOW);
      digitalWrite(9, LOW);
    }
    // forward right
    if (( ( _ABVAR_1_entoli ) == ( 'I' ) ))
    {
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      analogWrite(6, carSpeed);
      digitalWrite(9, LOW);
    }

    //back left
    if (( ( _ABVAR_1_entoli ) == ( 'H' ) ))
    {
      analogWrite(3, carSpeed);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
    }

    // back right
    if (( ( _ABVAR_1_entoli ) == ( 'J' ) ))
    {
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      analogWrite(9, carSpeed);
    }


    //front lights on
    if (( ( _ABVAR_1_entoli ) == ( 'W' ) ))
    {
      analogWrite(10, 255);

    }
    // front lights off

    if (( ( _ABVAR_1_entoli ) == ( 'w' ) ))
    {
      digitalWrite(10, LOW);
    }


    //back lights on
    if (( ( _ABVAR_1_entoli ) == ( 'U' ) ))
    {
      analogWrite(10, 80);
    }
    //back lights off
    if (( ( _ABVAR_1_entoli ) == ( 'u' ) ))
    {
      
      digitalWrite(10, LOW);
    }

    //horn on
    if (( ( _ABVAR_1_entoli ) == ( 'V' ) ))
    {
      digitalWrite(11, HIGH);
    }

    //horn off
    if (( ( _ABVAR_1_entoli ) == ( 'v' ) ))
    {
      
      digitalWrite(11, LOW);
    }
    //alarm lights on
    if (( ( _ABVAR_1_entoli ) == ( 'X' ) ))
    {
      digitalWrite(12, HIGH);

    }
    // alarm lights off
    if (( ( _ABVAR_1_entoli ) == ( 'x' ) ))
    {
      digitalWrite(12, LOW);

    }

// speed control
    if (( ( _ABVAR_1_entoli ) == 'q') || ( ( _ABVAR_1_entoli ) == '0') || ( ( _ABVAR_1_entoli ) == '1') || (( _ABVAR_1_entoli ) == '2' ) || (( _ABVAR_1_entoli ) == '3' ) || (( _ABVAR_1_entoli ) == '4' ) || (( _ABVAR_1_entoli ) == '5' ) || (( _ABVAR_1_entoli ) == '6' ) || (( _ABVAR_1_entoli ) == '7' ) || (( _ABVAR_1_entoli ) == '8' ) || (( _ABVAR_1_entoli ) == '9' ))
    {

      if ( ( _ABVAR_1_entoli ) == 'q') {
        carSpeed = 255;

      }
      else if ( ( _ABVAR_1_entoli ) == '0') {
        carSpeed = 0;

      }

      else {
        int rcvSpeed = _ABVAR_1_entoli - '0';
        //  int rcvSpeed = Serial.parseInt();
        //Serial.println(rcvSpeed);
        carSpeed = map(rcvSpeed, 1, 9, 50, 230);
        //Serial.println(carSpeed);
      }
    }

  }
}
