#ifndef __MYSENSORS_BUTRE_OUTPUT_LIST_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_OUTPUT_LIST_H_INCLUDED__   


#include "ConfigDefaults.h"
#include "Output.h"

class OutputList
// Set of Relays working over 
//
{
  public:
    Output outputs[BUTRE_OUTPUTS_NUM];
  
  public:
    OutputList() {
      for (int output_idx = 0 ; output_idx < BUTRE_OUTPUTS_NUM; output_idx ++ ) {
        uint8_t pin = BUTRE_OUTPUT_PINS_LIST[output_idx];
        outputs[output_idx].configure(pin);  // Sensor id is pin number
      }
    }
    
	bool validIdx(uint8_t outputIdx) {
		return 0 <= outputIdx and outputIdx < BUTRE_OUTPUTS_NUM;
	}
   
    // bool valid_id(uint8_t output_idx) // TODO: Make static

    // MySensors operations
    
    void before() {
      for (int output_idx = 0 ; output_idx < BUTRE_OUTPUTS_NUM; output_idx ++ ) {
        outputs[output_idx].before();
      }
      
    }
    void present() {
      for (int output_idx = 0 ; output_idx < BUTRE_OUTPUTS_NUM; output_idx ++ ) {
        outputs[output_idx].present();
      }
      
    }
    void update() {
      for (int output_idx = 0 ; output_idx < BUTRE_OUTPUTS_NUM; output_idx ++ ) {
        outputs[output_idx].update();
      }
    }
    
    bool sendStates() {
	bool sendResult = true;
	for (int output_idx = 0 ; output_idx < BUTRE_OUTPUTS_NUM; output_idx ++ ) {
		sendResult = sendResult and outputs[output_idx].sendState();
	}
	return sendResult;
    }    
    
    bool processMessage(const MyMessage & recv_msg) {
      for (int output_idx = 0 ; output_idx < BUTRE_OUTPUTS_NUM; output_idx ++ ) {
        if ( outputs[output_idx].processMessage(recv_msg) ) {
          return true;
        }
      }
      return false;
    }
    
};


#endif // __MYSENSORS_BUTRE_OUTPUT_LIST_H_INCLUDED__
