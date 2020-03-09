
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
#include "SimpleRelay.h"
#include "SimpleRelaySet.h"
#include "InputList.h"


extern SimpleRelaySet relay_set;
extern ButtonSet button_set;



#endif // __MYSENSORS_BUTRE_H_INCLUDED__
