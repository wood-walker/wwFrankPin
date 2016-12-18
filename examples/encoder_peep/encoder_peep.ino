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
int speedTarget = 60;

boolean   EnLeftCount = 0;
boolean   EnRightCount = 0;

// ============================================================================
void setup() {
  prepareFrank();
  pixel.begin();
  pixel.show();   // activate the begin()
  pixel.clear();  // switch all pixels off
  pixel.show();   // activate the switch off

  // motor pins -------------------------------
  pinMode(MoRi1 ,    OUTPUT);
  pinMode(MoRi2 ,    OUTPUT);
  pinMode(MoRiPwm,   OUTPUT);
  pinMode(MoLe1,     OUTPUT);
  pinMode(MoLe2,     OUTPUT);
  pinMode(MoLePwm,   OUTPUT);
  pinMode(MoEnable,  OUTPUT);
  digitalWrite(MoEnable, 1); // switch on the motor driver

  // encoder settings ------------------------
  pinMode(EnEnable, OUTPUT);
  digitalWrite(EnEnable, HIGH); // switch on the power of the encoder LED
  pinMode(EnRight, INPUT);      // open the inputs of the left and right encoder
  pinMode(EnLeft, INPUT);
  attachInterrupt(EnRight, EnRightDetect, FALLING);
  attachInterrupt(EnLeft, EnLeftDetect, FALLING);

  // sound settings --------------------------
  pinMode(SpOut, OUTPUT);
  digitalWrite(SpEnable, HIGH);    // Audio on
  digitalWriteFrank(SpMute, LOW);  // mute speaker

  // LED settings ----------------------------
  pinMode(Led13, OUTPUT);         // activate the Led13 and LedAux
  pinMode(LedAux, OUTPUT);
  digitalWrite(LedAux, LOW);       // turn LedAUX off

  // use the feeler to start and stop the motos
  pinMode(MFRight, INPUT_PULLUP);  // activate the right feeler
}

// =============================================================================
void EnRightDetect() {
  EnRightCount = 1;
}
// =============================================================================
void EnLeftDetect() {
  EnLeftCount = 1;
}

static boolean motorStatus = 0;

// ============================================================================
void loop() {


  if (EnRightCount == 1) {
    digitalWrite(LedAux, HIGH);       // turn Led13 on
    playTone(1000);
    EnRightCount = 0;
    digitalWrite(LedAux, LOW);       // turn Led13 on
  }
  if (EnLeftCount == 1) {
    digitalWrite(Led13, HIGH);       // turn Led13 on
    playTone(200);
    EnLeftCount = 0;
    digitalWrite(Led13, LOW);       // turn Led13 on
  }
  if (digitalRead(MFRight) == 0) {  // user interaction by feeler button
    if ( motorStatus == 0)
      feetMovement(feetGoForward);
    else
      feetMovement(feetStop);
    motorStatus = !motorStatus;
    delay(200);  // for debouncing
  }
}
// ============================================================================
void playTone(int note) {
  const int volume = 30;
  const long duration = 5000;

  digitalWriteFrank(SpMute, HIGH);  // de-mute amplifier
  delay(1);                         // give the amplifier some time to open
  for (long i = 0; i < duration; i += note * 2) {
    analogWrite(SpOut, volume);
    delayMicroseconds(note);
    analogWrite(SpOut, 0);
    delayMicroseconds(note);
  }
  digitalWriteFrank(SpMute, LOW);  // mute amplifier
}
// ============================================================================
void feetMovement(int directionNew) {
  //When a motor stops, slows down abruptly or will be reversed the effect of back-EMF
  //will induce a current flow back to the motor’s power supply.
  //You have to switch off the motors before you can change the direction
  //otherwise the high motor current will currupt the system Voltage
  //and the Frankenstein-DUE would at least reset itself.
  analogWrite(MoRiPwm, 0);
  analogWrite(MoLePwm, 0);

  switch (directionNew) {
    case feetGoForward:
      digitalWrite(MoRi1, 1);
      digitalWrite(MoRi2, 0);
      digitalWrite(MoLe1, 1);
      digitalWrite(MoLe2, 0);
      break;
    case feetGoBackward:
      digitalWrite(MoRi1, 0);
      digitalWrite(MoRi2, 1);
      digitalWrite(MoLe1, 0);
      digitalWrite(MoLe2, 1);
      break;
    case feetGoRight:
      digitalWrite(MoRi1, 1);
      digitalWrite(MoRi2, 0);
      digitalWrite(MoLe1, 0);
      digitalWrite(MoLe2, 1);
      break;
    case feetGoLeft:
      digitalWrite(MoRi1, 0);
      digitalWrite(MoRi2, 1);
      digitalWrite(MoLe1, 1);
      digitalWrite(MoLe2, 0);
      break;
    case feetStop:                  //cut off the power but let the motors run down
      digitalWrite(MoRi1, 0);
      digitalWrite(MoRi2, 0);
      digitalWrite(MoLe1, 0);
      digitalWrite(MoLe2, 0);
      break;
    case feetBreak:                //shorting the motors for an immediate stop
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


