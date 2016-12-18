// *****************************************************************************
//      - - - /    el-web-led-simple.ino
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow
//                          2016 December 18 - version 1.0
// *****************************************************************************
// Use the web interface of the on board esp to switch on and of the Led13
// You have to install esp-link on the ESP and set it up to work with the network
// to which your computer, phone or tablett is connected.
// You have to upload the SimpleLED.html to the esp also
// Please remember to switch off the "Debug log" via the esps web interface
// >>>>>>>>>
// The debug messages will be send via SerialUSB to the serial monitor of your computer
// <<<<<<<<<

#include <Wire.h>           // necessary for the I2C Communication
#include <SPI.h>            // used for SD-card communication
#include <SD.h>             // SD-card commands
#include <wwEyes.h>      // Header with instructions for using the OLED displays
#include <wwFrankPin.h>       // Defines all pin names of the Frankenstein DUE
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h> // Neo Pixel support

#include <ELClient.h>
#include <ELClientWebServer.h>

// just the eyes *************************************************
wwEyes eye;

// flash LED on PIN 13
// Led 13 defined in wwFrankPin.h already

// Initialize a connection to esp-link
// using the SerialESP (= Serial3) for the communication between ESP and
// using the SerialUSB to send all debug info to the computers serial monitor
ELClient esp(&SerialESP,&SerialUSB);

// Initialize the Web-Server client
ELClientWebServer webServer(&esp);

bool LedStatus = true;  // remember the state of the LED, send this to the web interface
//==========================================================================================
// send the actual status of the Led to the web page
// every time when the page will be refreshed
void ledPageLoadAndRefreshCb(char * url)
{
   if(LedStatus)
   webServer.setArgString(F("text"), F("LED ist an"));
   else
   webServer.setArgString(F("text"), F("LED ist aus"));
}
//==========================================================================================
// this function will be called every time when one of the buttons was pressed
void ledButtonPressCb(char * btnId)
{
   String id = btnId;
   if( id == F("btn_on") ){
      digitalWrite(Led13, true);
      LedStatus = true;
   }
   else if( id == F("btn_off") ) {
      digitalWrite(Led13, false);
      LedStatus = false;
   }
}
//==========================================================================================
// Callback made form esp-link to notify that it has just come out of a reset.
// This means we need to initialize it!
void resetCb(void) {
   SerialESP.println("EL-Client (re-)starting!");
   bool ok = false;
   do {
      ok = esp.Sync();      // sync up with esp-link, blocks for up to 2 seconds
      if (!ok) SerialESP.println("EL-Client sync failed!");
   } while(!ok);
   SerialESP.println("EL-Client synced erfolgreich!");
   
   webServer.setup();
}
//==========================================================================================
void setup() {
   // Timer to wait for Serial USB
   uint32_t wait= millis();
   
   prepareFrank();      // wwFrankPin.h
   initializeEyes();    // Bring the eyes in a stable mode
   setupESP();          // Switch on and reset the ESP

   SerialUSB.begin(115200);
   while(!SerialUSB){
      if (millis() - wait > 10000)  // after 10 seconds we do not wait any longer
      break;
   };  
   SerialESP.begin(115200);      
   while(!SerialESP)                // we have to wait for this connection because
   ;                                // this program is useless without the connection
   URLHandler *ledHandler = webServer.createURLHandler(F("/SimpleLED.html.json"));
   ledHandler->loadCb.attach(&ledPageLoadAndRefreshCb);
   ledHandler->refreshCb.attach(&ledPageLoadAndRefreshCb);
   ledHandler->buttonCb.attach(&ledButtonPressCb);

   pinMode(Led13, OUTPUT);
   digitalWrite(Led13, true);      // turn on the LED as Status for progress indication
   LedStatus = true;
   
   esp.resetCb = resetCb;
   resetCb();
}
//==========================================================================================
void loop()
{
   esp.Process();
}

//==========================================================================================
void setupESP () {
   pinMode(WiEnable, OUTPUT);         // ESP Pins ---------------------
   digitalWrite(WiEnable, LOW);       // LOW = shut off the ESP
   pinMode(WiPin2, OUTPUT);
   pinMode(WiPin15, OUTPUT);
   pinMode(WiRst, OUTPUT);
   pinModeFrank(WiProg, OUTPUT);

   // prepare ESP pins for operation *****************************************
   digitalWrite(WiEnable, HIGH);
   digitalWrite(WiPin2, HIGH);
   digitalWrite(WiPin15, LOW);
   digitalWriteFrank(WiProg, HIGH);  // LOW for programming mode / HIGH for working mode
   // RESET the ESP -----
   delay(10);
   digitalWrite(WiRst, LOW);
   delay(10);
   digitalWrite(WiRst, HIGH);
   // *****************************************************************************
}
//==========================================================================================
void initializeEyes() {
   delay(500);         // after a power on you have to wait a while to let the eyes start
   eye.setTextColor(WHITE, BLACK);
   eye.setTextSize(2);
   eye.select(eyeLeft);
   eye.stopscroll();
   eye.begin();
   eye.display();      // show an empty screen
   eye.select(eyeRight);
   eye.stopscroll();
   eye.begin();
   eye.display();      // show an empty screen
}
