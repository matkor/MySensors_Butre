#ifndef __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__   

#include <inttypes.h>


enum action_t {
	NO_ACTION = 0,
	ACTION_ON = 1,
	ACTION_OFF = 2,
	ACTION_TOGGLE = 3,
};

class ActionConfig
{
	public:
		uint8_t action = NO_ACTION;
		uint8_t outputIdx = 0; // Always points to sane value 0..

		void 
		disable(){
			action = NO_ACTION;
			outputIdx = 0;
		};
		
		void 
		setAction(action_t actionNew,uint8_t outputIdxNew) {
			action = actionNew;
			outputIdx = outputIdxNew;
		};
		// void 
		// performAction();

};


#endif                                                      // __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__   
