#ifndef __MYSENSORS_BUTRE_SIMPLE_RELAY_SET_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_SIMPLE_RELAY_SET_H_INCLUDED__   


#include "ConfigDefaults.h"
#include "Output.h"

class OutputList
// Set of Relays working over 
//
{
  public:
    Output outputs[RELAY_NUM];
  
  public:
    OutputList() {
      for (int output_idx = 0 ; output_idx < RELAY_NUM; output_idx ++ ) {
        uint8_t pin = RELAY_PINS[output_idx];
        outputs[output_idx].configure(pin, pin);  // Sensor id is pin number
      }
    }
    // bool valid_id(uint8_t output_idx) // TODO: Make static

    // MySensors operations
    
    void before() {
      for (int output_idx = 0 ; output_idx < RELAY_NUM; output_idx ++ ) {
        outputs[output_idx].before();
      }
      
    }
    void present() {
      for (int output_idx = 0 ; output_idx < RELAY_NUM; output_idx ++ ) {
        outputs[output_idx].present();
      }
      
    }
    void update() {
      for (int output_idx = 0 ; output_idx < RELAY_NUM; output_idx ++ ) {
        outputs[output_idx].update();
      }
    }    
    
    bool processMessage(const MyMessage & recv_msg) {
      for (int output_idx = 0 ; output_idx < RELAY_NUM; output_idx ++ ) {
        if ( outputs[output_idx].processMessage(recv_msg) ) {
          return true;
        }
      }
      return false;
    }
    
};


#endif // __MYSENSORS_BUTRE_SIMPLE_RELAY_SET_H_INCLUDED__
