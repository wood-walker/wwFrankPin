// *****************************************************************************
//      - - - /    I2C_bus_scanner.ino
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow
//                          2015 June 29 - version 1.0
// *****************************************************************************
// This sketch is looking for devices on the I2C bus
// and frequently prints a list of all found devices on the serial monitor

#include <Wire.h>
#include <wwFrankPin.h>

// =============================================================================
void setup() {

  prepareFrank();

  Wire.begin();
  SerialUSB.begin(9600);
  SerialUSB.println("\nI2C Scanner");

  //switch on the temp sensor
  pinModeFrank(TeEnable, OUTPUT);
  digitalWriteFrank(TeEnable, HIGH);

  //switch on the giro
  pinModeFrank(GiEnable, OUTPUT);
  digitalWriteFrank(GiEnable, HIGH);
}

// =============================================================================
void loop() {
  byte error, address;
  int nDevices;

  SerialUSB.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      SerialUSB.print("I2C device found at address 0x");
      if (address < 16) {
        SerialUSB.print("0");
      }
      SerialUSB.print(address, HEX);
      SerialUSB.println("  !");

      nDevices++;
    }
    else if (error == 4) {
      SerialUSB.print("Unknow error at address 0x");
      if (address < 16) {
        SerialUSB.print("0");
      }
      SerialUSB.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    SerialUSB.println("No I2C devices found\n");
  }
  else {
    SerialUSB.println("done\n");
  }
  delay(3000);           // wait 5 seconds for next scan
}
