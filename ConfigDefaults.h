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
//const static uint8_t RELAY_PINS[] = {2,3,4,5,6,7,8,9,A0,A1,A2,A3,A4,A5,};  


#ifndef BUTRE_OUTPUT_PINS
// TODO: Defults per platform type
#define BUTRE_OUTPUT_PINS {2,3,4,5,6,7,8,9}
#endif // BUTRE_OUTPUT_PINS

const static uint8_t RELAY_PINS[] = BUTRE_OUTPUT_PINS ;  

const static uint8_t BUTTON_PINS[] = {A0,A1,A2,A3,A6,A7};   

const size_t RELAY_NUM = sizeof(RELAY_PINS) / sizeof( RELAY_PINS[0] );
const size_t BUTTON_NUM = sizeof(BUTTON_PINS) / sizeof( BUTTON_PINS[0] );



inline bool valid_relay_idx(uint8_t relay_idx) {
  return 0 <= relay_idx < RELAY_NUM;
}


#endif // __MYSENSORS_BUTRE_CONFIG_DEFAULTS_H_INCLUDED__
