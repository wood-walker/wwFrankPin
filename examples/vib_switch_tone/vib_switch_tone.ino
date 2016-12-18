// *****************************************************************************
//      - - - /    vibration_tone.ino
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow
//                          2016 Dec 11 - version 1.0
// *****************************************************************************
// play a tone if the mechanical vibration switch was triggered

#include <wwFrankPin.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(3, NeoData, NEO_GRB + NEO_KHZ800);

boolean knockknock = 0;

// =============================================================================
void setup() {
  prepareFrank();
  pixel.begin();
  pixel.show();   // activate the begin()
  pixel.clear();  // switch all pixels off
  pixel.show();   // activate the switch off
  pinMode(SpOut, OUTPUT);
  digitalWrite(SpEnable, HIGH);    // Audio on

  pinMode(Led13, OUTPUT);         // activate the Led13 and LedAux
  pinMode(LedAux, OUTPUT);
  digitalWrite(LedAux, LOW);       // turn LedAUX off

  pinMode(VibSwitch, INPUT_PULLUP);
  attachInterrupt(VibSwitch, knockdetect, FALLING);
}
// =============================================================================
void knockdetect() {
  knockknock = 1;
}
// =============================================================================
void playTone() {
  const int volume = 30;
  const long duration = 50000;
  const int note = 500;

  digitalWrite(Led13, LOW);       // turn Led13 on
  digitalWrite(LedAux, HIGH);       // turn LedAUX on
  digitalWriteFrank(SpMute, HIGH);  // de-mute amplifier
  delay(1);                         // give the amplifier some time to open
  for (long i = 0; i < duration; i += note * 2) {
    analogWrite(SpOut, volume);
    delayMicroseconds(note);
    analogWrite(SpOut, 0);
    delayMicroseconds(note);
  }
  digitalWriteFrank(SpMute, LOW);  // mute amplifier
  digitalWrite(LedAux, LOW);       // turn LedAUX on
}
// =============================================================================
void loop() {
  static unsigned long timerA, timeNow;
  static boolean toggle;
  const int blinkTime = 500; // ms

  if (knockknock == 1) {
    playTone();
    knockknock = 0;
  }
  timeNow = millis();
  if (timerA + blinkTime < timeNow) { // look up if it is time to blink the LED
    if (toggle == true) {
      digitalWrite(Led13, LOW);       // turn Led13 on
    } else {
      digitalWrite(Led13, HIGH);      // turn Led13 on
    }
    toggle = !toggle;
    timerA = timeNow;                 // save the new time for comparison
  }
}
// *****************************************************************************


