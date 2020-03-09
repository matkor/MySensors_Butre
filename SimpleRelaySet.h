#ifndef __MYSENSORS_BUTRE_SIMPLE_RELAY_SET_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_SIMPLE_RELAY_SET_H_INCLUDED__   


#include "ConfigDefaults.h"
#include "SimpleRelay.h"

class SimpleRelaySet
// Set of Relays working over 
//
{
  public:
    SimpleRelay relays[RELAY_NUM];
  
  public:
    SimpleRelaySet() {
      for (int relay_idx = 0 ; relay_idx < RELAY_NUM; relay_idx ++ ) {
        uint8_t pin = RELAY_PINS[relay_idx];
        relays[relay_idx].configure(pin, pin);  // Sensor id is pin number
      }
    }
    // bool valid_id(uint8_t relay_idx) // TODO: Make static

    // MySensors operations
    
    void before() {
      for (int relay_idx = 0 ; relay_idx < RELAY_NUM; relay_idx ++ ) {
        relays[relay_idx].before();
      }
      
    }
    void present() {
      for (int relay_idx = 0 ; relay_idx < RELAY_NUM; relay_idx ++ ) {
        relays[relay_idx].present();
      }
      
    }
    void update() {
      for (int relay_idx = 0 ; relay_idx < RELAY_NUM; relay_idx ++ ) {
        relays[relay_idx].update();
      }
    }    
    
    bool process_message(const MyMessage & recv_msg) {
      for (int relay_idx = 0 ; relay_idx < RELAY_NUM; relay_idx ++ ) {
        if ( relays[relay_idx].process_message(recv_msg) ) {
          return true;
        }
      }
      return false;
    }
    
};


#endif // __MYSENSORS_BUTRE_SIMPLE_RELAY_SET_H_INCLUDED__
