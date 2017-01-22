// ****************************************************************************
//      - - - /    time-unix-serial.ino
//     ( W-W )        www.wood-walker.org - Rainer Radow
//      - - - \          Jan 21, 2017, version 1.v6
// ****************************************************************************
// Converts the ATMEL SAM 3x8 RTC time and date to UNIX Time Stamp and v/v
void setup()
{
    SerialUSB.begin(115200);
    while (!SerialUSB)   // wait for the connection to the PC's serial monitor
        ;
    SerialUSB.println("Setup");

    pmc_switch_sclk_to_32kxtal(PMC_OSC_XTAL); // switch clock to external cristal
    while (!pmc_osc_is_ready_32kxtal())      // wait till the cristall is swinging
        ;
    RTC_SetHourMode(RTC, 0);                  // 0 = 24-hour mode, 1 = 12-hour mode
    //RTC_SetTime(RTC, 20, 0, 0); //set the time to 05:04:50
    //RTC_SetDate(RTC, 2017, 1, 20, 1);  //year, month, day, week

    //RTC_SetByUnixTime(1484913600, 1); //2017-01-20 13:00:00 UTC +1
    //RTC_SetByUnixTime(1514721600, 1); //2017-12-31 13:00:00 UTC +1
    RTC_SetByUnixTime(1582891922, 1); //2020-02-28 13:12:02 UTC +1
}
// ================================================================================
void loop()
{
    static uint8_t secondsp;                          //flag for last displayed second - has to be static!
    uint8_t hour, minute, second;
    uint16_t year;
    uint8_t month, day, week;

    RTC_GetTime(RTC, &hour, &minute, &second); // get the actual time
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

        SerialUSB.println(RTC_GetUnixTime());
        secondsp = second;
    }
}
// ================================================================================
uint32_t RTC_GetUnixTime()
{
    uint8_t daysInMonth [] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint8_t hour, minute, second;
    uint16_t year;
    uint8_t month, day, week;
    uint16_t days;

    RTC_GetDate( RTC, &year, &month, &day, &week);    //Get the actual date
    days = day-1;                          // we will count todays seconds via todays hour, minute, second
    for (int i = 1; i < month; ++i)        // look up the days per month and add
        days += daysInMonth[i - 1];        // days of the month of this year excluding actual month
    if (month > 2 && year % 4 == 0)        // every year which can be devided by 4 has a 29th of February to add (valid till 2100 ;-)
        ++days;
    year   = year - 1970;                  // Start counting the seconds from 1970
    days += 365 * year + (year + 1) / 4;   // Add extra days for the additional 29th of February in every 4th year.

    RTC_GetTime(RTC, &hour, &minute, &second); // get the actual time
    return ((days * 24 + hour) * 60 + minute) * 60 + second; // seconds from 01.01.1970 00:00:00
}
// ================================================================================
// Please remember the unixTime in general is calculated as UTC 0!!!
uint8_t RTC_SetByUnixTime(uint32_t unixTime, uint8_t UTC)
{
    uint8_t hour, minute, second;
    uint16_t year, years_Unix;
    uint8_t month, day, week;

    uint32_t days_Unix, days_LastYear, minutes_LastDay, secs_LastDay, leap;

    unixTime += UTC*60*60;                  // add or subtract the necessary seconds for the given UTC

    secs_LastDay = unixTime % (24*60*60);   // calculate how many seconds are left in the last day
    second = secs_LastDay % 60;             // calculate how many seconds are left in the last minute
    minutes_LastDay = secs_LastDay / 60;    // calculate how many full minutes are left in the last day
    minute = minutes_LastDay % 60;          // calculate how many minutes are left in the last hour
    hour = minutes_LastDay / 60;            // calculate how many full hours are left in the last day
    RTC_SetTime(RTC, hour, minute, second); //set the time to 05:04:50

    days_Unix = unixTime/(24 * 60 * 60);           // calculate how many full days fits into the given time
    years_Unix = (((days_Unix * 4) + 2) / 1461);   // calculate how many full years this full days make
    year = years_Unix + 70;                        // add this because of the Unix start in 1970

    leap = !(year & 3);
    days_Unix -= ((years_Unix * 1461) + 1) / 4;    // calculate how many full days are left in the last year
    days_Unix += (days_Unix > 58 + leap) ? ((leap) ? 1 : 2) : 0;
    month = ((days_Unix * 12) + 6)/367;            //generates month counting from 0 to 11
    day = days_Unix + 1 - ((month * 367) + 5)/12;
    month += 1;                                    // generate month counting from 1 to 12
    year = year + 1900;                            // add the missing 1900 years

    RTC_SetDate(RTC, year, month, day, 1);         // I do not care about the weeks here...

    return 0;
}
// ================================================================================
// ================================================================================

