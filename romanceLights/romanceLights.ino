//gkapsid 23/5/2022 code works 
// maybe wifimanager to be added 

/*
   -- romanceLights --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB
#include <ESP8266WiFi.h>

#include <RemoteXY.h>
#include <Adafruit_NeoPixel.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "yourSSID"
#define REMOTEXY_WIFI_PASSWORD "yourPassword"
#define REMOTEXY_SERVER_PORT 6377

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    0

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 8

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)



// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 77 bytes
  { 255,4,0,0,0,46,0,16,200,1,6,0,15,42,40,40,2,26,3,2,
  12,6,10,28,2,26,129,0,30,10,18,6,17,87,105,70,105,0,129,0,
  30,24,18,6,17,82,97,105,110,98,111,119,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t rgb_1_r; // =0..255 Red color value 
  uint8_t rgb_1_g; // =0..255 Green color value 
  uint8_t rgb_1_b; // =0..255 Blue color value 
  uint8_t select_1; // =0 if select position A, =1 if position B, =2 if position C, ... 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(115200);
  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  if (RemoteXY.select_1 == 0) {
   // Serial.println("wifi controlled");
      colorWipe(strip.Color(RemoteXY.rgb_1_r, RemoteXY.rgb_1_g  ,RemoteXY.rgb_1_b), 50); // Red

   // delay(2000); 
  }
  else if (RemoteXY.select_1==1) {
    //Serial.println("light effect");
    //delay(2000);
    rainbow(10);
  }
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}


// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}



// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
 
   // gkapsid: the rainbow effect could make the app irresponsive. the firstPixelHue value changed from 5*65536 to 65536.
   // it improved connectivity and responsiveness when the rainbow effect was used
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) { 
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new content
   
    if (RemoteXY.select_1 == 0) break; // the rainbow loop is long, it improves responsiveness (UX)
    
    delay(wait);  // Pause for a moment
  }
}
