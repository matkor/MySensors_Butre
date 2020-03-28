#ifndef __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__   

#include <inttypes.h>


enum action_t {
	NO_ACTION = 0,
	ACTION_ON = 1,
	ACTION_OFF = 2,
	ACTION_TOGGLE = ACTION_ON+ACTION_OFF,
	ACTION_SAME = 5, 
	ACTION_INVERT = 6, 
	WHEN_OFF = 64, 
	WHEN_ON = 128,
	WHEN_CHANGE = WHEN_OFF+WHEN_ON
};

class ActionConfig
{

	public:
		const static uint8_t INVALID= -1;  // Default invalid pin/sensor id value
		uint8_t inputPin = INVALID;
		uint8_t action = NO_ACTION;
		uint8_t outputPin = INVALID;

		ActionConfig(const uint8_t inputPin=INVALID, uint8_t action=NO_ACTION, uint8_t outputPin=INVALID)
		{
		}
		
		void 
		disable(){
			inputPin = INVALID;
			action = NO_ACTION;
			outputPin = INVALID;
		};
		/*
		void 
		setAction(action_t actionNew,uint8_t outputIdxNew) {
			action = actionNew;
			outputIdx = outputIdxNew;
		};
		*/
		// void 
		// performAction();

};

class ActionConfigList
{
private:
	ActionConfig * actions; 
	const uint8_t ACTIONS_NUM;

public:
	ActionConfigList( ActionConfig  * actions, const uint8_t ACTIONS_NUM):
		actions(actions), ACTIONS_NUM(ACTIONS_NUM) 
	{}
	

};

#endif                                                      // __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__   
