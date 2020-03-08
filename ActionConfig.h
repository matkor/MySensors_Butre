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
		uint8_t relay_idx = 0; // Always points to sane value 0..

		void 
		disable(){
			action = NO_ACTION;
			relay_idx = 0;
		}
		void 
		set_relay_action(action_t set_action,uint8_t set_relay_idx) {
			this->action = set_action;
			this->relay_idx = set_relay_idx;
		}
		void 
		perform_action();

};


#endif                                                      // __MYSENSORS_BUTRE_ACTION_CONFIG_H_INCLUDED__   
