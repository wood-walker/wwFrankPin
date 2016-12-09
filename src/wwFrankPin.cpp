// *****************************************************************************
//      - - - /    FrankPin.cpp
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow 
//                          2016 December 09 - for Frankenstein DUE v0.7 and up
// ***************************************************************************** 
// This library defines the names for all the pins used for the Wood-Walker
// It also establish functions to communicate with non Arduino DUE pins

#include "wwFrankPin.h"

extern void prepareFrank() {

	pinMode(SpEnable, OUTPUT);      // Audio Pin
	digitalWrite(SpEnable, LOW);    // Audio off - disable amplifier

	// ESP LED liegt am GPIO 14 des ESP und kann nur über den ESP gesteuert werden!	
	pinMode(WiEnable, OUTPUT);
	digitalWrite(WiEnable, HIGH);	
	
	// wenn kein BT Modul verbaut ist, sollte man das hier weg lassen
	// Pin liegt über 10 k auf GND
    // BT LED liegt am PIO 1 des BT Chip und kann nur über das BT gesteuert werden!
	// man kann eine Brücke von BT Enable legen und dann diese LED frei benutzen...
	//pinModeFrank(BtEnable, OUTPUT);    // Make the non DUE pin an output	
	//digitalWriteFrank(BtEnable, HIGH); // HIGH = switch OFF the BT = energy saving	
}

/*
 * Pins descriptions
 */
extern const PinDescription nonDuePinDescription[]= {
	{PIOB, PIO_PB1,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 0 = not used
	{PIOB, PIO_PB1,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 1 = MiEnable  = PB1
	{PIOB, PIO_PB3,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 2 = LiEnable  = 
	{PIOB, PIO_PB4,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 3 = PB4
	{PIOB, PIO_PB2,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 4 = TeEnable  = PB2
	{PIOB, PIO_PB6,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 5 = IrEnLeft  = PB6
	{PIOB, PIO_PB8,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 6 = IrEnRight = PB8
	{PIOB, PIO_PB23, ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 7 = WiProg    = PB23
	{PIOB, PIO_PB24, ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 8 = BtEnable  = PB24
	{PIOC, PIO_PC27, ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  // 9 = BtReset   = PC27
	{PIOB, PIO_PB5,  ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL, NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },  //10 = GiEnable  = PB5
  // END
	{NULL, 0, 0, PIO_NOT_A_PIN, PIO_DEFAULT, 0, NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }
} ;

/*
pinModeNonDue
copied from the pinMode function within wiring-digital.c file, part of the arduino core.
Allows a non "Arduino Due" PIO pin to be setup.
*/
extern void pinModeFrank( uint32_t ulPin, uint32_t ulMode )
{
    if ( nonDuePinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
    {
        return ;
    }

    switch ( ulMode )
    {
        case INPUT:
            /* Enable peripheral for clocking input */
            pmc_enable_periph_clk( nonDuePinDescription[ulPin].ulPeripheralId ) ;
            PIO_Configure(
            	nonDuePinDescription[ulPin].pPort,
            	PIO_INPUT,
            	nonDuePinDescription[ulPin].ulPin,
            	0 ) ;
        break ;

        case INPUT_PULLUP:
            /* Enable peripheral for clocking input */
            pmc_enable_periph_clk( nonDuePinDescription[ulPin].ulPeripheralId ) ;
            PIO_Configure(
            	nonDuePinDescription[ulPin].pPort,
            	PIO_INPUT,
            	nonDuePinDescription[ulPin].ulPin,
            	PIO_PULLUP ) ;
        break ;

        case OUTPUT:
            PIO_Configure(
            	nonDuePinDescription[ulPin].pPort,
            	PIO_OUTPUT_1,
            	nonDuePinDescription[ulPin].ulPin,
            	nonDuePinDescription[ulPin].ulPinConfiguration ) ;

            /* if all pins are output, disable PIO Controller clocking, reduce power consumption */
            if ( nonDuePinDescription[ulPin].pPort->PIO_OSR == 0xffffffff )
            {
                pmc_disable_periph_clk( g_APinDescription[ulPin].ulPeripheralId ) ;
            }
        break ;

        default:
        break ;
    }
}

/*
digitalWriteNonDue
copied from the digitalWrite function within wiring-digital.c file, part of the arduino core.
Allows digital write to a non "Arduino Due" PIO pin that has been setup as output with pinModeUndefined
*/

extern void digitalWriteFrank( uint32_t ulPin, uint32_t ulVal )
{
  /* Handle */
  if ( nonDuePinDescription[ulPin].ulPinType == PIO_NOT_A_PIN ) 
 {
    return ;
  }

  if ( PIO_GetOutputDataStatus( nonDuePinDescription[ulPin].pPort, nonDuePinDescription[ulPin].ulPin ) == 0 )
  {
    PIO_PullUp( nonDuePinDescription[ulPin].pPort, nonDuePinDescription[ulPin].ulPin, ulVal ) ;
  }
  else
  {
    PIO_SetOutput( nonDuePinDescription[ulPin].pPort, nonDuePinDescription[ulPin].ulPin, ulVal, 0, PIO_PULLUP ) ;
  }
}

/*
digitalReadNonDue
copied from the digitalRead function within wiring-digital.c file, part of the arduino core.
Allows digital read of a non "Arduino Due" PIO pin that has been setup as input with pinModeUndefined
*/
extern int digitalReadFrank( uint32_t ulPin )
{
	if ( nonDuePinDescription[ulPin].ulPinType == PIO_NOT_A_PIN )
    {
        return LOW ;
    }

	if ( PIO_Get( nonDuePinDescription[ulPin].pPort, PIO_INPUT, nonDuePinDescription[ulPin].ulPin ) == 1 )
    {
        return HIGH ;
    }

	return LOW ;
}

static uint8_t PWMEnabled = 0;
static uint8_t pinEnabled[PINS_C];

/*
analog write helper functions
*/
void analogOutputNonDueInit(void) {
	uint8_t i;
	for (i=0; i<PINS_C; i++)
		pinEnabled[i] = 0;
}

/*
analogWriteNonDue
copied from the analogWrite function within wiring-analog.c file, part of the arduino core.
Allows analog write to a non "Arduino Due" PWM pin. Note this does not support the other functions of
the arduino analog write function such as timer counters and the DAC. Any hardware PWM pin that is defined as such
within the unDefPinDescription[] struct should work, and non hardware PWM pin will default to digitalWriteUndefined
*/

void analogWriteFrank(uint32_t ulPin, uint32_t ulValue) {
	uint32_t attr = nonDuePinDescription[ulPin].ulPinAttribute;
  if ((attr & PIN_ATTR_PWM) == PIN_ATTR_PWM) {
    if (!PWMEnabled) {
      // PWM Startup code
        pmc_enable_periph_clk(PWM_INTERFACE_ID);
        PWMC_ConfigureClocks(PWM_FREQUENCY * PWM_MAX_DUTY_CYCLE, 0, VARIANT_MCK);
        analogOutputNonDueInit();
      PWMEnabled = 1;
    }
    uint32_t chan = nonDuePinDescription[ulPin].ulPWMChannel;
    if (!pinEnabled[ulPin]) {
      // Setup PWM for this pin
      PIO_Configure(nonDuePinDescription[ulPin].pPort,
          nonDuePinDescription[ulPin].ulPinType,
          nonDuePinDescription[ulPin].ulPin,
          nonDuePinDescription[ulPin].ulPinConfiguration);
      PWMC_ConfigureChannel(PWM_INTERFACE, chan, PWM_CMR_CPRE_CLKA, 0, 0);
      PWMC_SetPeriod(PWM_INTERFACE, chan, PWM_MAX_DUTY_CYCLE);
      PWMC_SetDutyCycle(PWM_INTERFACE, chan, ulValue);
      PWMC_EnableChannel(PWM_INTERFACE, chan);
      pinEnabled[ulPin] = 1;
    }

    PWMC_SetDutyCycle(PWM_INTERFACE, chan, ulValue);
    return;
  }
	// Defaults to digital write
	pinModeFrank(ulPin, OUTPUT);
	if (ulValue < 128)
		digitalWriteFrank(ulPin, LOW);
	else
		digitalWriteFrank(ulPin, HIGH);
}

/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
Code from wiring-digital.c and from variant.cpp from the arduino software
This allows access to the pins on the SAM3X8E that are not defined in the Arduino
pin description.

At this point it only implements pinMode and digitalWrite on pin PA5 and PC27
(also on PA0,PA1,PA7 as a further example, ahtough these are defined by the Arduino software)
Note the pin numbers of "0" and "1"
*/

/*
Changed the naming for the Frankenstein-board of the Wood-Walker
Rainer Radow
11-06.2015
*/

