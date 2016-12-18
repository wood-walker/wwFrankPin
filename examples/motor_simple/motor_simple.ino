/// *****************************************************************************
//      - - - /    motor_simple.ino
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow
//                          2016 Dec 11 - version 1.0
// *****************************************************************************
// Explains the general concept of the motor movement 
// use this as a start for your projects
// Try out the other examples for more precise direction and distance control
// ============================================================================
#include <wwFrankPin.h>         // general board definitions and setup
#include <Wire.h>
#include <Adafruit_NeoPixel.h>  // we need this to switch off the Pixel
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(3, NeoData, NEO_GRB + NEO_KHZ800);

// definition of direction code to keep the software easy to read for us humans
#define feetStop       0
#define feetBreak      1
#define feetGoForward  2
#define feetGoBackward 3
#define feetGoRight    4
#define feetGoLeft     5

// the target speed that should be reached after the acceleration time
int speedTarget = 255;

// ============================================================================
void setup() {
  prepareFrank();
  pixel.begin();
  pixel.show();   // activate the begin()
  pixel.clear();  // switch all pixels off
  pixel.show();   // activate the switch off

  SerialUSB.begin(9600);

  // motor pins -------------------------------
  pinMode(MoRi1 ,    OUTPUT);
  pinMode(MoRi2 ,    OUTPUT);
  pinMode(MoRiPwm,   OUTPUT);
  pinMode(MoLe1,     OUTPUT);
  pinMode(MoLe2,     OUTPUT);
  pinMode(MoLePwm,   OUTPUT);
  pinMode(MoEnable,  OUTPUT);
  digitalWrite(MoEnable, 1); // switch on the motor driver
}
// ============================================================================
void loop() {
  const int runtime = 2000;

  feetMovement(feetGoForward);
  delay(runtime);
  feetMovement(feetGoBackward);
  delay(runtime);
  feetMovement(feetStop);
  delay(runtime);
  feetMovement(feetGoRight);
  delay(runtime);
  feetMovement(feetGoLeft);
  delay(runtime);
  feetMovement(feetBreak);
  delay(runtime);
}
// ============================================================================
void feetMovement(int directionNew) {
  static int directionOld = feetStop;
  //When a motor stops, slows down abruptly or will be reversed the effect of back-EMF
  //will induce a current flow back to the motor’s power supply.
  //You have to switch off the motors before you can change the direction
  //otherwise the high motor current will currupt the system Voltage
  //and the Frankenstein-DUE would at least reset itself.
  analogWrite(MoRiPwm, 0);
  analogWrite(MoLePwm, 0);

  switch (directionNew) {
    case feetGoForward:
      SerialUSB.println("foreward");
      digitalWrite(MoRi1, 1);
      digitalWrite(MoRi2, 0);
      digitalWrite(MoLe1, 1);
      digitalWrite(MoLe2, 0);
      break;
    case feetGoBackward:
      SerialUSB.println("backward");
      digitalWrite(MoRi1, 0);
      digitalWrite(MoRi2, 1);
      digitalWrite(MoLe1, 0);
      digitalWrite(MoLe2, 1);
      break;
    case feetGoRight:
      SerialUSB.println("right");
      digitalWrite(MoRi1, 1);
      digitalWrite(MoRi2, 0);
      digitalWrite(MoLe1, 0);
      digitalWrite(MoLe2, 1);
      break;
    case feetGoLeft:
      SerialUSB.println("left");
      digitalWrite(MoRi1, 0);
      digitalWrite(MoRi2, 1);
      digitalWrite(MoLe1, 1);
      digitalWrite(MoLe2, 0);
      break;
    case feetStop:                  //cut off the power but let the motors run down
      SerialUSB.println("stop");
      digitalWrite(MoRi1, 0);
      digitalWrite(MoRi2, 0);
      digitalWrite(MoLe1, 0);
      digitalWrite(MoLe2, 0);
      break;
    case feetBreak:
      SerialUSB.println("break");   //shorting the motors for an immediate stop
      digitalWrite(MoRi1, 1);
      digitalWrite(MoRi2, 1);
      digitalWrite(MoLe1, 1);
      digitalWrite(MoLe2, 1);
  }
  //it's always a good idea to ramp up the motor voltage for a smooth run
  //this eliminate current peaks and guarantees a stable system voltage 
  for (int i = 0; i <= speedTarget; i++) {
    analogWrite(MoRiPwm, i);
    analogWrite(MoLePwm, i);
    delay(2);
  }
}
// *****************************************************************************


