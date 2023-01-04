//gkapsid
//tested 8/11/2022 OK
// rotary encoder code from http://angryyak.co.uk/blog/using-a-rotary-encoder-with-arduino-or-attiny85/


#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 0
#define PIXELS 15
#define DELAYVAL 1000 // Time (in milliseconds) to pause between pixels
//# define LS 3 //LDR light sensor

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_RGB);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

#include "avr/interrupt.h"

/*
  ATTiny 85 rotary encoder sample

  pin  port   usage
  2    PB3    Channel B
  3    PB4    Channel A
  6    PB1    LED PWM output
  7    PB2    Button and external interrupt
*/

#define BUTTON 1
#define wheelA 3
#define wheelB 4

bool previousB = false;
volatile int portReading = 0;
volatile int value = 0;
volatile bool update = true;
int bright = 120; //set default brightness
int count = 0;

//variables from strantest_nodelay example
unsigned long pixelPrevious = 0;        // Previous Pixel Millis
unsigned long patternPrevious = 0;      // Previous Pattern Millis
int           patternCurrent = 0;       // Current Pattern Number
int           patternInterval = 5000;   // Pattern Interval (ms)
int           pixelInterval = 50;       // Pixel Interval (ms)
int           pixelQueue = 0;           // Pattern Pixel Queue
int           pixelCycle = 0;           // Pattern Pixel Cycle
uint16_t      pixelCurrent = 0;         // Pattern Current Pixel Number
uint16_t      pixelNumber = PIXELS;  // Total Number of Pixels

void setup() {
  pinMode(BUTTON, INPUT_PULLUP); //Rotary encoder switch
  pinMode(wheelA, INPUT_PULLUP); //Inputs for rotary channels
  pinMode(wheelB, INPUT_PULLUP);
  pinMode(PIN, OUTPUT); //NEOPIXEL pin

  GIMSK = 0b00100000; //turn on pin change
  PCMSK = 0b00011000; //turn on interrupts for pin 2 (PB3) and 3 (PB4)
  sei(); //turn interrupts on



  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


}

void loop() {
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t green = strip.Color(255, 0, 0);

  uint32_t red = strip.Color(0, 255, 0);
  uint32_t white = strip.Color(255, 255, 255);
  uint32_t black = strip.Color(0, 0, 0);

  if (digitalRead(BUTTON) == LOW) {
    count ++ ;
  }
  if (count == 0) {
    // light white colour


    strip.fill(white);

    strip.show();
    delay(1000);

  }
  else if (count == 1) {
    //light red color


    strip.fill(red);
    strip.show();
    delay(1000);
  }
  else if (count == 2) {
    //light blue color


    strip.fill(blue);
    strip.show();
    delay(1000);
  }
  else if  (count == 3) {
    rainbowb(100);
    // strip.fill();
    //strip.show();
    delay(1000);
  }
  /*   else if (count== 4) {
     rainbow(100);
     //   strip.fill(white);
    // strip.show();
    // delay(1000);
     //  count = 0;
    //    delay(1000);
     }
     else if (count== 5) {
    /*   colorWipe(red, 600);
       colorWipe(blue, 200);
       colorWipe(white, 1000);
       // strip.fill(white);
     //strip.show();
    // delay(1000);
    //   count = 0;
    //    delay(1000);
     }
      else if (count== 6) {
      theaterChaseRainbow(100);
     }*/
  else if (count > 3) {
    strip.fill(white);
    strip.show();
    delay(1000);
    count = 0;
    //    delay(1000);
  }
  if (update) {
    update = false;
   
    if (value > 250) value = 250;
    if (value < 10) value = 10;

    strip.setBrightness(value);
   
  }
}

/* Pin change interrupt vector */
ISR (PCINT0_vect) {

  //read the port quickly, masking out other pins
  portReading = PINB & 24;

  //read channel A
  if ( (portReading & (1 << wheelA)) == 0) {

    //determine what part of the waveform we are on
    if (previousB)
      value = value + 10;
    else
      value = value - 10;
  } else {
    if (previousB)
      value = value - 10;
    else
      value = value + 10;
  }

  //record b channel for use next time round
  previousB = (portReading & (1 << wheelB)) == 0;

  update = true; //tell the main loop that a rotation has happened

}
//Rainbow from strandtest_nodelay example
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(uint8_t wait) {
  if (pixelInterval != wait)
    pixelInterval = wait;
  for (uint16_t i = 0; i < pixelNumber; i++) {
    strip.setPixelColor(i, Wheel((i + pixelCycle) & 255)); //  Update delay time
  }
  strip.show();                             //  Update strip to match

  pixelCycle++;                             //  Advance current cycle
  if (pixelCycle >= 256)
    pixelCycle = 0;                         //  Loop the cycle back to the begining
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    //int sensorValue = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    //float voltage = sensorValue * (5.0 / 1023.0);  // print out the value you read:
    //Serial.println(voltage);

  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++) { // Repeat 30 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}


// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbowb(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).

    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    if (digitalRead(BUTTON) == LOW) {
      break ;
    }
    delay(wait);  // Pause for a moment 
  }
}
