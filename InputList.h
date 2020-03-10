#ifndef __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  

#include "ConfigDefaults.h"
#include "Button.h"

class ButtonSet
// Set of buttons
//
{
  public:
     PushButton buttons[BUTTON_NUM];
  
  public:
    ButtonSet() {
      for (int button_idx = 0 ; button_idx < BUTTON_NUM; button_idx ++ ) {
        uint8_t pin = BUTTON_PINS[button_idx];
        buttons[button_idx].configure(pin, pin);  // Sensor id is pin number
      }
    }
    
//    void before() {
//      for (int button_idx = 0 ; button_idx < BUTTON_NUM; button_idx ++ ) {
//        buttons[button_idx].before();
//      }      
//    }
    
    void present() {
      for (int button_idx = 0 ; button_idx < BUTTON_NUM; button_idx ++ ) {
        buttons[button_idx].present();
      }
    }
      
    void send_states() {
      for (int button_idx = 0 ; button_idx < BUTTON_NUM; button_idx ++ ) {
        buttons[button_idx].send_state();
      }
    }    
    void update() {
      for (int button_idx = 0 ; button_idx < BUTTON_NUM; button_idx ++ ) {
        buttons[button_idx].update();
      }
    }    
    
    bool processMessage(const MyMessage & recv_msg) {
      for (int button_idx = 0 ; button_idx < BUTTON_NUM; button_idx ++ ) {
        if ( buttons[button_idx].processMessage(recv_msg) ) {
          return true;
        }
      }
      return false;
    }


    bool valid_button_idx(uint8_t button_idx){
      return 0 <= button_idx < BUTTON_NUM;
    }
    
    void configure_action_pushed(uint8_t button_idx, action_t action, uint8_t relay_idx) {
      if ( valid_button_idx(button_idx) and valid_relay_idx(relay_idx) ) {
        buttons[button_idx].pushed_config.set_relay_action(action,relay_idx);
      }
    }
    
};



#endif // __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  
