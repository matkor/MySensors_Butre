
#ifndef __MYSENSORS_BUTRE_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_H_INCLUDED__   

// https://forum.mysensors.org/topic/11005/how-can-one-use-mymessage-class-in-library/2
// #define MY_CORE_ONLY
// #include <MySensors.h>

#include <core/MySensorsCore.h>
// #include <MySensors/core/MyMessage.h>

// #include <MyMessage.h>  // Needs  ~/Arduino/libraries/MySensors_Butre$ ln -s ../MySensors/core/MyMessage.h MyMessage.h

// #include <MySensors/core/MyMessage.h> // ln -s ../MySensors MySensors  
// #include <MySensors/core/MySensorsCore.h> // ln -s ../MySensors MySensors  


#include "Utils.h"
#include "Button.h"


const static uint8_t RELAY_PINS[] = {53,51,49,47,};  
const static uint8_t BUTTON_PINS[] = {A1,A2,A3,A4,};  // 55 56 57 58 

const size_t RELAY_NUM = sizeof(RELAY_PINS) / sizeof( RELAY_PINS[0] );
const size_t BUTTON_NUM = sizeof(BUTTON_PINS) / sizeof( BUTTON_PINS[0] );



#endif // __MYSENSORS_BUTRE_H_INCLUDED__
