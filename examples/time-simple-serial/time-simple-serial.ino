// ****************************************************************************
//      - - - /    time-simple-serial.ino
//    -( W-W )        www.wood-walker.org - Rainer Radow
//      - - - \          Jan 21, 2017, version 1.v6
// ****************************************************************************
// Explanation of the basic functions of the ATMELSAM3X8 internal RTC
// Please remember that the precision of the RTC will be influenced by many
// factors like temperature changes and aging which are not compensated here!

void setup() {
  SerialUSB.begin(9600);
  while (!SerialUSB)   // wait for the connection to the PC's serial monitor
    ;
  SerialUSB.println("Setup");
  pmc_switch_sclk_to_32kxtal(PMC_OSC_XTAL); // switch clock to external cristal
  while (!pmc_osc_is_ready_32kxtal());      // wait till the cristall is swinging
  RTC_SetHourMode(RTC, 0);                  // 0 = 24-hour mode, 1 = 12-hour mode
  RTC_SetTime(RTC, 5, 4, 50);               // set the time to 05:04:50 
  RTC_SetDate(RTC, 2017, 1, 21, 4);  //year, month, day, week
}

void loop() {
  static uint8_t secondsp;                          //flag for last displayed second - has to be static!
  uint8_t hour, minute, second;
  uint16_t year;
  uint8_t month, day, week;
  RTC_GetTime(RTC,  &hour, &minute, &second);       //Get the actual time

  if (second != secondsp) { // update only every second
    RTC_GetDate( RTC, &year, &month, &day, &week);    //Get the actual date
    SerialUSB.print(year);
    SerialUSB.print('-');
    SerialUSB.print(month);
    SerialUSB.print('-');
    SerialUSB.print(day);
    SerialUSB.print(' ');
    SerialUSB.print(week);
    SerialUSB.print(' ');
    SerialUSB.print(hour);
    SerialUSB.print(':');
    SerialUSB.print(minute);
    SerialUSB.print(':');
    SerialUSB.println(second);
    secondsp = second;
  }
}
