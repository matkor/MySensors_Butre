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
  Input * inputs;  // TODO: make private
  const uint8_t INPUTS_NUM;
  
  public:
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
    
    bool sendSensorState(uint8_t sensorId) {
        for (int inputIdx = 0 ; inputIdx < INPUTS_NUM; inputIdx ++ ) {
            if ( inputs[inputIdx].sensorId() == sensorId ) {
                // Serial_mysensors_logln("sendSensorState(): sending sensorId: ",sensorId);
                return inputs[inputIdx].sendState();
            }
        }
        return false;
    }
    /*
    for (int outputIdx = 0 ; outputIdx < OUTPUTS_NUM; outputIdx ++ ) {
      if ( butre.outputList[outputIdx].sensorId() == lastSendSensorId ) {
        Serial_mysensors_logln("Periodical sending state() for sensorId: ",lastSendSensorId);
        butre.outputList[outputIdx].sendState();
        break;
      }
    }*/
        
    void update(Butre & butre);
    
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
    
    // TODO: Add operator[] to avoid inputs.inputs[X] ?
    
};



#endif // __MYSENSORS_BUTRE_INPUT_LIST_H_INCLUDED__  
