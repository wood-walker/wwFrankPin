// *****************************************************************************
//      - - - /    melody_simple.ino
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.com - Rainer Radow
//                          2016 Dec 10 - version 1.0
// *****************************************************************************
// plays a little melody on the speaker
// inspired by //https://www.arduino.cc/en/tutorial/melody
// =============================================================================
#include <wwFrankPin.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(3, NeoData, NEO_GRB + NEO_KHZ800);
// -----------------------------------------------------------------------------
int noteCount = 13; // the number of notes

struct composition {
  char  note;
  int   duration;
};
// -----------------------------------------------------------------------------
composition weihnachtsmann[] = {
  'c', 1, 'c', 1, 'g', 1, 'g', 1, 'a', 1, 'a', 1, 'g', 2, 'f', 1, 'f', 1, 'e', 1, 'e', 1, 'd', 2, 'c', 2
};
// -----------------------------------------------------------------------------
const int tempo = 200;
const int volume = 300;
// ============================================================================
void playTone(int tone, int duration) {
  digitalWriteFrank(SpMute, HIGH);  // de-mute amplifier
  delay(1);                         // give the amplifier some time to open
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    analogWrite(SpOut, volume);
    delayMicroseconds(tone);
    analogWrite(SpOut, 0);
    delayMicroseconds(tone);
  }
  digitalWriteFrank(SpMute, LOW);  // mute amplifier
}
// ============================================================================
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
// ============================================================================
void setup() {
  prepareFrank();
  pixel.begin();
  pixel.show();   // activate the begin()
  pixel.clear();  // switch all pixels off
  pixel.show();   // activate the switch off
  pinMode(SpOut, OUTPUT);
  analogWriteResolution(12);
  digitalWrite(SpEnable, HIGH);    // Audio on
  delay(100);
  digitalWriteFrank(SpMute, HIGH);  // de-mute amplifier
  delay(1);                         // give the amplifier some time to open
  playTone(3000, 200);
  digitalWriteFrank(SpMute, LOW);  // mute amplifier
  pinMode(MFRight, INPUT_PULLUP);  // activate the right feeler
}
// ============================================================================
void loop() {
  while (digitalRead(MFRight) == HIGH); //Wait till the right feller is pressed
  for (int i = 0; i < noteCount; i++) {
    if (weihnachtsmann[i].note == ' ') {
      delay(weihnachtsmann[i].duration * tempo); // rest
    } else {
      playNote(weihnachtsmann[i].note, weihnachtsmann[i].duration * tempo);
    }
    // pause between notes
    delay(weihnachtsmann[i].duration * tempo);
  }
}
// *****************************************************************************
