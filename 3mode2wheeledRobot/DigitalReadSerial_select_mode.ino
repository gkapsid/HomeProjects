/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButtonA = 2;
int pushButtonB = 1;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButtonA, INPUT);
  pinMode(pushButtonB, INPUT);
  pinMode(13, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonStateA = digitalRead(pushButtonA);
  int buttonStateB = digitalRead(pushButtonB);
  // print out the state of the button:
 // Serial.println(buttonStateA);
 // delay(100);        // delay in between reads for stability
 
  // print out the state of the button:
 // Serial.println(buttonStateB);
 // Serial.println();
 // delay(100);        // delay in between reads for stability
 if (!buttonStateA) {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100); 
 }
 else if (!buttonStateB) {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
 }
 else {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
 }
}
