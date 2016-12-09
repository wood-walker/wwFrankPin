// *****************************************************************************
//      - - - /    neo_pixel_simple.ino
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow
//                          2015 July 06 - version 1.v5
// *****************************************************************************
// This sketch lights up each of the 3 Neo_pixels in a different color
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <wwFrankPin.h>
 
// Parameter 1 = number of pixels in the strip (3 on Frankenstein-DUE board)
// Parameter 2 = Arduino pin number = NeoData 
// Parameter 3 = pixel type flags, add together:
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ800  800 KHz bitstream
Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, NeoData, NEO_GRB + NEO_KHZ800);
     
// ============================================================================ 
void setup() {
	
	prepareFrank(); // set up the board for general use
                    // switch off the ESP for instance
	
    strip.begin();
    strip.show();   // activate the begin() 
     
    //strip.setPixelColor(n, red, green, blue);
    strip.setPixelColor(0, 255,    0,   0);
    strip.setPixelColor(1,   0,    0, 255);
    strip.setPixelColor(2,   0,  250,   0);
    strip.show();   // push the data to the pixels
}
// ============================================================================  
void loop() {
}
// *****************************************************************************

