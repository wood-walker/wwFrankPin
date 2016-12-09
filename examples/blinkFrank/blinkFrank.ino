// *****************************************************************************
//      - - - /    blinkFrank.ino
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow
//                          2015 June 29 - version 1.v5
// *****************************************************************************
// This sketch let the Led13 and LedAux blink for ever

#include <wwFrankPin.h>  //includes definition 'Led13' and 'LedAux' (LOW = on)

// =============================================================================
void setup() {
  prepareFrank(); // set up the board for general use
  // switch off the ESP for instance
  

  pinMode(Led13, OUTPUT);    // initialize pin Led13
  pinMode(LedAux, OUTPUT);  //  and LedAux as output
}
// =============================================================================
void loop() {
  digitalWrite(Led13, HIGH); // turn Led13  on
  digitalWrite(LedAux, LOW); // turn LedAUX off
  delay(1000);               // wait a second

  digitalWrite(Led13, LOW);
  digitalWrite(LedAux, HIGH);
  delay(1000);
}
// *****************************************************************************


