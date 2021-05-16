#include "Input.h"
#include "MySensors_Butre.h"

// MyMessage (const uint8_t sensorId, const mysensors_data_t dataType)
MyMessage Input::msg(Input::INVALID,V_STATUS);

bool 
Input::update(Butre & butre)
    // Calculate current button state, send update msg if change detected
    // Execute butre actions if defined
{
	if (debouncer.update()) {
		// Serial_mysensors_logln("pin: ", msg.sensor, " level change: ", debouncer.read());
		bool state;
		sendState(state);
	
		if (state) {
			//Serial_mysensors_logln("state - pushed pin: ",pin() );
			// onConfig.performAction();
			//return PUSHED;
			for (uint8_t actionIdx = 0 ; actionIdx < butre.actionList.ACTIONS_NUM; actionIdx++ ) {
				ActionConfig & action = butre.actionList.actions[actionIdx];
				// Check conditions
				// Serial_mysensors_logln("checking action action.inputPin: ",action.inputPin );
				if ( action.inputPin != pin() ) {
					continue;
				}
				// Serial_mysensors_logln("Action matches pin actionIdx: ",actionIdx );
				if (! action.whenOn() ) {
					continue;
				}
				// Perform actions
				// Serial_mysensors_logln("action.action: ",action.action );
				if (action.action() == ACTION_ON) {
					butre.outputList.set(action.outputPin,true);
				} else if (action.action() == ACTION_OFF) {
					// Serial_mysensors_logln("action off setting off pin: ",action.outputPin );
					butre.outputList.set(action.outputPin,false);
				} else if (action.action() == ACTION_TOGGLE) {
					butre.outputList.toggle(action.outputPin);
				} else if (action.action() == ACTION_SAME) {
					butre.outputList.set(action.outputPin,true);
				} else if (action.action() == ACTION_INVERTED) {
					butre.outputList.set(action.outputPin,false);
				}
			}
		} else {
			// Serial_mysensors_logln("not state - released");
			// offConfig.performAction();
			//return RELEASED;
			for (uint8_t actionIdx = 0 ; actionIdx < butre.actionList.ACTIONS_NUM; actionIdx++ ) {
				ActionConfig & action = butre.actionList.actions[actionIdx];
				// Check conditions
				// Serial_mysensors_logln("checking action action.inputPin: ",action.inputPin );
				if ( action.inputPin != pin() ) {
					continue;
				}
				// Serial_mysensors_logln("Action matches pin actionIdx: ",actionIdx );
				if (! action.whenOff() ) {
					continue;
				}
				// Perform actions
				// Serial_mysensors_logln("action.action: ",action.action );
				if (action.action() == ACTION_ON ) {
					butre.outputList.set(action.outputPin,true);
				} else if (action.action() == ACTION_OFF) {
					// Serial_mysensors_logln("action off setting off pin: ",action.outputPin );
					butre.outputList.set(action.outputPin,false);
				} else if (action.action() == ACTION_TOGGLE) {
					butre.outputList.toggle(action.outputPin);
				} else if (action.action() == ACTION_SAME) {
					butre.outputList.set(action.outputPin,false);
				} else if (action.action() == ACTION_INVERTED) {
					butre.outputList.set(action.outputPin,true);
				}
			}
		}
		return true;
	}
	// return NO_CHANGE;
	return false;
};
