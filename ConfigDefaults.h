#ifndef __MYSENSORS_BUTRE_CONFIG_DEFAULTS_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_CONFIG_DEFAULTS_H_INCLUDED__   

#include <stdint.h>
#include <Arduino.h>

// D0/0  RxD
// D1/1  TxD
// D2/2  
// ...
// D10/10  SS      (used by eth) 
// D11/11  MOSI    (used by eth)
// D12/12  MISO    (used by eth)
// D13/13  LED/SCK (used by eth)
// A0 / 14
// ...
// A4 / 18  SDA
// A5 / 19  SCL
// A6 
// A7 

  // Ardunio Nano analog pins A6 and A7 are weird. They can *only* be used for analogRead()
  // https://forum.arduino.cc/index.php?topic=123176.0
  // D10-D13 SPI ? (ethernets) ?
  // D0,D1 - serial
  // A0 .. A5 are pins 14..19

#ifndef BUTRE_INPUT_PINS
// TODO: Defults per platform type

// In nano: A0 .. A5 are pins 14..17,  A6=20, A7=21
#define BUTRE_INPUT_PINS {A0,A1,A2,A3,A6,A7}  
#endif // BUTRE_OUTPUT_PINS

#ifndef BUTRE_OUTPUT_PINS
// TODO: Defults per platform type
#define BUTRE_OUTPUT_PINS {2,3,4,5,6,7,8,9}
#endif // BUTRE_OUTPUT_PINS

const static uint8_t BUTRE_OUTPUT_PINS_LIST[] = BUTRE_OUTPUT_PINS ;  
const static uint8_t BUTRE_INPUT_PINS_LIST[] = BUTRE_INPUT_PINS ;

const size_t BUTRE_OUTPUTS_NUM = sizeof(BUTRE_OUTPUT_PINS_LIST) / sizeof( BUTRE_OUTPUT_PINS_LIST[0] );
const size_t BUTRE_INPUTS_NUM = sizeof(BUTRE_INPUT_PINS_LIST) / sizeof( BUTRE_INPUT_PINS_LIST[0] );


// Default Nano config: 6 inputs  ,8 outputs
// Sketch uses 9392 bytes (30%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1325 bytes (64%) of dynamic memory, leaving 723 bytes for local variables. Maximum is 2048 bytes




#endif // __MYSENSORS_BUTRE_CONFIG_DEFAULTS_H_INCLUDED__
