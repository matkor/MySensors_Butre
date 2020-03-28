#ifndef __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  

#include "ConfigDefaults.h"
#include "Input.h"

// https://stackoverflow.com/questions/26269777/passing-unknown-array-to-function-by-reference-c


// template<size_t INPUTS_NUM>
class InputList
// Inputs manager
//
{
  // Input (& inputs) [INPUTS_NUM];  // TODO: convert to operator[] to avoid inputs.inputs[X] ?
  Input * inputs;  // TODO: make private
  const uint8_t INPUTS_NUM;
  
  public:
	  /*
    InputList() {
      for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
        uint8_t pin = BUTRE_INPUT_PINS_LIST[inputIdx];
        inputs[inputIdx].configure(pin, pin);  // Sensor id is pin number
      }
    }
    */
  
  /*
  InputList( Input (& inputs) [INPUTS_NUM]):
	inputs(inputs)
  {
		
  }
  */
  InputList( Input  * inputs, const uint8_t INPUTS_NUM):
	inputs(inputs), INPUTS_NUM(INPUTS_NUM) 
	{}
  
    
    void before() 
	// initialisations that needs to take place before MySensors transport has been setup (eg: SPI devices).    
    {
      for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
        inputs[inputIdx].before();
      }
    }
//    void before() {
//      for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
//        inputs[inputIdx].before();
//      }      
//    }
    
    void present() {
      for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
        inputs[inputIdx].present();
      }
    }
      
    bool sendStates() {
	bool sendResult = true;
	for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
		sendResult = sendResult and inputs[inputIdx].sendState();
	}
	return sendResult;
    }
    
    void update(Butre & butre);
    /* {
      for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
        inputs[inputIdx].update(butre);
      }
    }  */  
    
    bool processMessage(const MyMessage & recv_msg) {
      for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
        if ( inputs[inputIdx].processMessage(recv_msg) ) {
          return true;
        }
      }
      return false;
    }


    bool validIdx(uint8_t inputIdx){
      return 0 <= inputIdx and inputIdx < INPUTS_NUM;
    }
    
    /*
    void configureOnAction(uint8_t inputIdx, action_t action, uint8_t outputIdx) {
	if ( validIdx(inputIdx)  ) { // and outputs.validIdx(outputIdx)
		inputs[inputIdx].onConfig.setAction(action,outputIdx);
	}
    }
    */
    
};



#endif // __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  
