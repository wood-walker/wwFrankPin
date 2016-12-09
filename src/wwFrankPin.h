// *****************************************************************************
//      - - - /    wwFrankPin.h
//    -( W-W )        CC Attribution 4.0 International License
//      - - - \          www.wood-walker.org - Rainer Radow 
//                          2016 December 09 - for Frankenstein DUE v0.7 and up
// ***************************************************************************** 
// This library defines the names for all the pins used for the Wood-Walker
// It also establish functions to communicate with non Arduino DUE pins

#ifndef WW_PIN_H
#define WW_PIN_H

#include "Arduino.h"

#define SerialBT      Serial2
#define SerialESP     Serial3

// Number of pins defined in PinDescription array
#define PINS_C 11
// Definition of NONE Arduino-Due Pins ==========
static const uint8_t MiEnable = 1;
static const uint8_t LiEnable = 2;
static const uint8_t PB4 = 3;
static const uint8_t TeEnable = 4;
static const uint8_t IrEnLeft = 5;
static const uint8_t IrEnRight = 6;
static const uint8_t WiProg = 7;
static const uint8_t BtEnable = 8;
static const uint8_t BtReset = 9;
static const uint8_t GiEnable = 10;

// Definition of Arduino-Due Pins ================
static const uint8_t MoRiPwm = 11;  //
static const uint8_t MoLePwm = 12;  //
static const uint8_t Led13 = 13;    //
static const uint8_t WiRst = 23;    //
static const uint8_t WiPin2 = 24;   //
static const uint8_t WiPin15 = 25;  //
static const uint8_t WiEnable = 26; //
static const uint8_t WiPin13 = 27;  //
static const uint8_t WiPin12 = 28;  //
static const uint8_t MFRight = 30;  //
static const uint8_t NeoData = 32;  //
static const uint8_t SdDetect = 33; //
static const uint8_t EnRight = 34;  //
static const uint8_t EnLeft = 35;   //
static const uint8_t GiInter = 36;  //
static const uint8_t LedAux = 37;   //
static const uint8_t VibSwitch = 39;//
static const uint8_t EnEnable = 40; //
static const uint8_t MoEnable = 44; //
static const uint8_t MoRi1 = 45;    //
static const uint8_t MoRi2 = 46;    //
static const uint8_t MFLeft = 47;   //
static const uint8_t MoLe2 = 48;    //
static const uint8_t SpEnable = 49; //
static const uint8_t SpMute = 73;	//
static const uint8_t MoLe1 = 50;	//
static const uint8_t SdCS = 51;     //
static const uint8_t ShutDown = 58; //
static const uint8_t LiFront = 59;  //
static const uint8_t IrLeft = 60;   //
static const uint8_t IrRight = 61;  //
static const uint8_t SysCur = 62;   //
static const uint8_t SysVcc = 63;   //
static const uint8_t RawVcc = 64;   //  
static const uint8_t MiInput = 65;  //


extern void prepareFrank(); 

// struct used to hold the descriptions for the "non arduino" pins.
// from the Arduino.h files
extern const PinDescription nonDuePinDescription[] ;
extern void pinModeFrank( uint32_t ulPin, uint32_t ulMode );
extern void digitalWriteFrank( uint32_t ulPin, uint32_t ulVal );
extern int digitalReadFrank( uint32_t ulPin);
extern void analogWriteFrank(uint32_t ulPin, uint32_t ulValue);
extern void analogOutputFrank();

#endif /* WW_PIN_H */

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
Added pin names for the Frankenstein-board of the Wood-Walker
James
11.06.2015

Changed the naming for the Frankenstein-DUE v5 board of the Wood-Walker
Rainer Radow
10.10.2015
*/

