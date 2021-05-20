//19/5/2021 gkapsid 
//V2 - second version with motor bridge IC
//the forward backward routines are changed. vehicle with one motor for both left and right wheels.
// turns left right using a servo motor as steering wheel (like normal cars, not diffential car)
//SN754410 bridge was used https://www.ti.com/lit/ds/symlink/sn754410.pdf
// any other H-Bridge can be used adapting the code for forward and backward movement appropriately

// tested ok!

#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 2 // Popular NeoPixel ring size

char _ABVAR_1_entoli = ' ' ;
void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

Servo servo_pin_9;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  servo_pin_9.attach(9);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

void loop() 
{
    pixels.clear(); // Set all pixel colors to 'off'

  if (( ( Serial.available() ) > ( 0 ) ))
  {
    _ABVAR_1_entoli = Serial.read();
    if (( ( _ABVAR_1_entoli ) == ( 'F' ) ))
    {
      Serial.print(_ABVAR_1_entoli);
            __ardublockDigitalWrite(5, LOW);

      __ardublockDigitalWrite(4, HIGH);
              servo_pin_9.write( 90 );

    }
    else
    {
      if (( ( _ABVAR_1_entoli ) == ( 'B' ) ))
      {
        __ardublockDigitalWrite(4, LOW);
        __ardublockDigitalWrite(5, HIGH);
        servo_pin_9.write( 90 );
      }
      else
      {
        if (( ( _ABVAR_1_entoli ) == ( 'L' ) ))
        {
          servo_pin_9.write( 20 );
        }
        else
        {
          //right
          if (( ( _ABVAR_1_entoli ) == ( 'R' ) ))
          {
            servo_pin_9.write( 150 );
          }
        }
      }
    }
    // full stop
    if (( ( _ABVAR_1_entoli ) == ( 'S' ) ))
        {
 __ardublockDigitalWrite(4, LOW);
        __ardublockDigitalWrite(5, LOW);
        servo_pin_9.write( 90 );        }
   //Forward left
    if (( ( _ABVAR_1_entoli ) == ( 'G' ) ))
        {
 __ardublockDigitalWrite(4, HIGH);
        __ardublockDigitalWrite(5, LOW);
        servo_pin_9.write( 20 );        }
    // forward right
    if (( ( _ABVAR_1_entoli ) == ( 'I' ) ))
        {
 __ardublockDigitalWrite(4, HIGH);
        __ardublockDigitalWrite(5, LOW);
        servo_pin_9.write( 150 );        }
     //back left
      if (( ( _ABVAR_1_entoli ) == ( 'H' ) ))
        {
 __ardublockDigitalWrite(4, LOW);
        __ardublockDigitalWrite(5, HIGH);
        servo_pin_9.write( 20 );        }
     // back right
         if (( ( _ABVAR_1_entoli ) == ( 'J' ) ))
        {
 __ardublockDigitalWrite(4, LOW);
        __ardublockDigitalWrite(5, HIGH);
        servo_pin_9.write( 150 );        }
   //front lights on
    if (( ( _ABVAR_1_entoli ) == ( 'W' ) ))
        {
     // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.
  }
     // front lights off
  }
    if (( ( _ABVAR_1_entoli ) == ( 'w' ) ))
        {
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.
  }
  
  }
    //back lights on
  if (( ( _ABVAR_1_entoli ) == ( 'U' ) ))
        {
__ardublockDigitalWrite(10, HIGH);
  }
    //lights off
    if (( ( _ABVAR_1_entoli ) == ( 'u' ) ))
        {
         // digitalWrite(10,LOW);
         __ardublockDigitalWrite(10, LOW);
  }
    
    //horn on
if (( ( _ABVAR_1_entoli ) == ( 'V' ) ))
        {
__ardublockDigitalWrite(11, HIGH);
  }
    
    //horn off
    if (( ( _ABVAR_1_entoli ) == ( 'v' ) ))
        {
         // digitalWrite(10,LOW);
         __ardublockDigitalWrite(11, LOW);
  }
    //alarm on
  if (( ( _ABVAR_1_entoli ) == ( 'X' ) ))
        {
__ardublockDigitalWrite(10, HIGH);
         __ardublockDigitalWrite(11, HIGH);

delay(500);
         __ardublockDigitalWrite(10, LOW);
                  __ardublockDigitalWrite(11, LOW);

         delay(500);

  }
   //alarm off
    if (( ( _ABVAR_1_entoli ) == ( 'x' ) ))
        {
         // digitalWrite(10,LOW);
         __ardublockDigitalWrite(10, LOW);
                  __ardublockDigitalWrite(11, LOW);

  }
}
}
