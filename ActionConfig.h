#ifndef __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__   

#include <inttypes.h>


enum action_t {
	NO_ACTION = 0,
	ACTION_ON = 1,
	ACTION_OFF = 2,
	ACTION_TOGGLE = 3,
	ACTION_SAME = 4, 
	ACTION_INVERTED = 5,
	ACTION_MASK = 7, 
	WHEN_OFF = 64,  // Means logical off/0, not pin level(high/low)
	WHEN_ON = 128, // Means logical on/1 , not pin level(high/low)
	WHEN_CHANGE = WHEN_OFF+WHEN_ON
};

class ActionConfig
{
	public:
		const static uint8_t INVALID= -1;  // Default invalid pin/sensor id value
		uint8_t inputPin = INVALID;
		uint8_t whenAction = NO_ACTION;
		uint8_t outputPin = INVALID;

		ActionConfig(const uint8_t inputPin=INVALID, uint8_t whenAction=NO_ACTION, uint8_t outputPin=INVALID):
			inputPin(inputPin), 
			whenAction(whenAction), 
			outputPin(outputPin)
		{
		}
		
		void 
		disable(){
			inputPin = INVALID;
			whenAction = NO_ACTION;
			outputPin = INVALID;
		};
		
		uint8_t action() {
			return whenAction & ACTION_MASK;
		}
		
		bool whenOn() 
		//  Action condition matches ON change state
		{
			return whenAction & WHEN_ON;
		}
		bool whenOff() 
		//  Action condition matches OFF change state
		{
			return whenAction & WHEN_OFF;
		}

};

class ActionConfigList
{
public:                                                     //  Consider private ? 
	ActionConfig * actions; 
	const uint8_t ACTIONS_NUM;

public:
	ActionConfigList( ActionConfig  * actions, const uint8_t ACTIONS_NUM):
		actions(actions), ACTIONS_NUM(ACTIONS_NUM) 
	{}

	/*
	ActionConfig & 
	operator[] (uint8_t index) {                               //  NOTE: not tested !
		if ( index >= ACTIONS_NUM) {
			// Serial_mysensors_logln("ERROR: Action index ", index);
			// Serial_mysensors_logln("ERROR: >= max ", ACTIONS_NUM);
			index = ACTIONS_NUM-1;
		}			
		return actions[index];
	}
	*/

};

#endif                                                      // __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__   
