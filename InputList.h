#ifndef __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  

#include "ConfigDefaults.h"
#include "Input.h"

class InputList
// Inputs manager
//
{
  public:
     Input inputs[BUTRE_INPUTS_NUM];  // TODO: convert to operator[] to avoid inputs.inputs[X] ?
  
  public:
    InputList() {
      for (int inputIdx = 0 ; inputIdx < BUTRE_INPUTS_NUM; inputIdx ++ ) {
        uint8_t pin = BUTRE_INPUT_PINS_LIST[inputIdx];
        inputs[inputIdx].configure(pin, pin);  // Sensor id is pin number
      }
    }
    
//    void before() {
//      for (int inputIdx = 0 ; inputIdx < BUTRE_INPUTS_NUM; inputIdx ++ ) {
//        inputs[inputIdx].before();
//      }      
//    }
    
    void present() {
      for (int inputIdx = 0 ; inputIdx < BUTRE_INPUTS_NUM; inputIdx ++ ) {
        inputs[inputIdx].present();
      }
    }
      
    void sendStates() {
      for (int inputIdx = 0 ; inputIdx < BUTRE_INPUTS_NUM; inputIdx ++ ) {
        inputs[inputIdx].sendState();
      }
    }    
    void update() {
      for (int inputIdx = 0 ; inputIdx < BUTRE_INPUTS_NUM; inputIdx ++ ) {
        inputs[inputIdx].update();
      }
    }    
    
    bool processMessage(const MyMessage & recv_msg) {
      for (int inputIdx = 0 ; inputIdx < BUTRE_INPUTS_NUM; inputIdx ++ ) {
        if ( inputs[inputIdx].processMessage(recv_msg) ) {
          return true;
        }
      }
      return false;
    }


    bool validIdx(uint8_t inputIdx){
      return 0 <= inputIdx and inputIdx < BUTRE_INPUTS_NUM;
    }
    
    void configureOnAction(uint8_t inputIdx, action_t action, uint8_t outputIdx) {
	if ( validIdx(inputIdx)  ) { // and outputs.validIdx(outputIdx)
		inputs[inputIdx].onConfig.setAction(action,outputIdx);
	}
    }
    
};



#endif // __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  
