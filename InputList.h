#ifndef __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  

#include "ConfigDefaults.h"
#include "Input.h"

class InputList
// Inputs manager
//
{
  public:
     Input inputs[BUTTON_NUM];
  
  public:
    InputList() {
      for (int input_idx = 0 ; input_idx < BUTTON_NUM; input_idx ++ ) {
        uint8_t pin = BUTTON_PINS[input_idx];
        inputs[input_idx].configure(pin, pin);  // Sensor id is pin number
      }
    }
    
//    void before() {
//      for (int input_idx = 0 ; input_idx < BUTTON_NUM; input_idx ++ ) {
//        inputs[input_idx].before();
//      }      
//    }
    
    void present() {
      for (int input_idx = 0 ; input_idx < BUTTON_NUM; input_idx ++ ) {
        inputs[input_idx].present();
      }
    }
      
    void send_states() {
      for (int input_idx = 0 ; input_idx < BUTTON_NUM; input_idx ++ ) {
        inputs[input_idx].send_state();
      }
    }    
    void update() {
      for (int input_idx = 0 ; input_idx < BUTTON_NUM; input_idx ++ ) {
        inputs[input_idx].update();
      }
    }    
    
    bool processMessage(const MyMessage & recv_msg) {
      for (int input_idx = 0 ; input_idx < BUTTON_NUM; input_idx ++ ) {
        if ( inputs[input_idx].processMessage(recv_msg) ) {
          return true;
        }
      }
      return false;
    }


    bool valid_input_idx(uint8_t input_idx){
      return 0 <= input_idx < BUTTON_NUM;
    }
    
    void configure_action_pushed(uint8_t input_idx, action_t action, uint8_t relay_idx) {
      if ( valid_input_idx(input_idx) and valid_relay_idx(relay_idx) ) {
        inputs[input_idx].pushed_config.set_relay_action(action,relay_idx);
      }
    }
    
};



#endif // __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  
