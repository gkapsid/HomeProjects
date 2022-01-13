//gkapsid
//worked 18/8/2021
//needs modification according https://docs.blynk.io/en/blynk.cloud/troubleshooting

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V0
    Value Display widget attached to V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Hvnrg0cmaGLuXdupkrCkp3y1cpg1Uylt";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "VODAFONE_7014";
char pass[] = "fbcu45a9at7auchf";
bool debug = false;
#define DHTPIN 14          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

//PT1000 calculation variables

const float vref = 3.3 ;
const float R1 = 6700;
float Rx;
float vout;
const float a = 0.00385;
const float R0 = 1000;
float temperature;
# define windowsize 10

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  calculateTemp();
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, temperature);
}

void setup()
{
  // Debug console
  if (debug) {
    Serial.begin(9600);
    Serial.println("Initializing...");
  }
  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "fra1.blynk.cloud", 80); // gkapsid: here is specified a custom service in case of Invalid auth key error
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(100000L, sendSensor);
}

void loop()

{
  // sendSensor();
  //digitalWrite(5, HIGH);
  
  if (debug) {
    Serial.println("Running Blynk");
  }
  Blynk.run();

  if (debug) {
    Serial.println("Running timer");
  }
  timer.run();

  //digitalWrite(5, LOW);
  //delay(5000);
  if (debug) {
    Serial.println("Going to sleep...");
  }
  //ESP.deepSleep(5 * 1000000);

}

void calculateTemp() {
  // Average analog input measurement
  int total = 0;
  for (int i = 0; i < windowsize ; i++) {
    int meas = analogRead(A0);
    total += meas ;
    delay(2);
  }
  
  float finalmeas = total / windowsize;

  // calculate vout
  vout = finalmeas / 1024.0;

  // calculate Rx
  Rx = R1 * (1 / (vref / vout - 1));
  
  // calculate Temp
  temperature = (Rx / R0 - 1) / a;

  if (debug) {
    Serial.print( "finalmeas ");
    Serial.println(finalmeas);
    Serial.print( "vout ");
    Serial.println(vout);
    Serial.println(Rx);
    Serial.println(temperature);
  }
}
