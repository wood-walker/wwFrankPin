// ****************************************************************************
//      - - - /    feeler_simple.ino
//    -( W-W )        www.wood-walker.org - Rainer Radow 
//      - - - \          December 10, 2016 version 1.0
// ****************************************************************************
#include <wwFrankPin.h>

//=============================================================================
void setup()   {
  prepareFrank(); // set up the board for general use

  pinMode(MFRight, INPUT_PULLUP);
  pinMode(MFLeft, INPUT_PULLUP);

  // initialize pin Led13 and LedAux as output.
  pinMode(Led13, OUTPUT); 
  pinMode(LedAux, OUTPUT);   
}
//=============================================================================
void loop() {
  // is one of the feeler pressed?
  if (digitalRead(MFRight) == 0) {
    digitalWrite(Led13, HIGH); // turn Led13  on
    digitalWrite(LedAux, LOW); // turn LedAUX off
    delay(200);     // debounce the button
  }
  if (digitalRead(MFLeft) == 0) {
    digitalWrite(Led13, LOW);
    digitalWrite(LedAux, HIGH);
    delay(200);     // debounce the button
  }
}
// ****************************************************************************
