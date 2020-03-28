
#ifndef __MYSENSORS_BUTRE_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_H_INCLUDED__   

// https://forum.mysensors.org/topic/11005/how-can-one-use-mymessage-class-in-library/2
// #define MY_CORE_ONLY
// #include <MySensors.h>

#include <core/MySensorsCore.h>
// #include <MySensors/core/MyMessage.h>

// #include <MyMessage.h>  // Needs  ~/Arduino/libraries/MySensors_Butre$ ln -s ../MySensors/core/MyMessage.h MyMessage.h

// #include <MySensors/core/MyMessage.h> // ln -s ../MySensors MySensors  
// #include <MySensors/core/MySensorsCore.h> // ln -s ../MySensors MySensors  


#include "Utils.h"
#include "Input.h"
#include "Output.h"
#include "InputList.h"
#include "OutputList.h"


// template<size_t INPUTS_NUM>
class Butre {
public:
	InputList & inputList;
	// InputList<INPUTS_NUM> & inputList;
	// OutputList outputs;
	OutputList & outputList;
	ActionConfigList & actionList;
	
private:
	bool inital_msgs_sent = false; // Flag if initial state messages ware sent , or was requested again
	MyMessage msg;
public:	
	// Butre(InputList<INPUTS_NUM> & inputList):
	Butre(InputList & inputList, OutputList & outputList, ActionConfigList & actionList):
		inputList(inputList),
		outputList(outputList),
		actionList(actionList)
	{
		
	}
		
	void before() 
	// initialisations that needs to take place before MySensors transport has been setup (eg: SPI devices).
	{
		inputList.before();
		outputList.before();
	}
		
	void present(const char * sketchName, const char * version) 
	{
		// bool sendSketchInfo(const char *name, const char *version, bool echo);
		sendSketchInfo(sketchName, version);
		inputList.present();
		outputList.present();
		
		// bool present(uint8_t childSensorId, uint8_t sensorType, const char *description, bool echo);
		::present(250,S_INFO,F("Status/config"));
	}
	
	void sendStatusConfig(const char * txt) {
		msg.setType(V_TEXT);
		msg.setSensor(250);
		msg.set(txt);
		send(msg);
	}
	
	void sendStatusConfig(const __FlashStringHelper * txt) {
		msg.setType(V_TEXT);
		msg.setSensor(250);
		msg.set(txt);
		send(msg);
	}
	
	void loop() {
		
		// bool static inital_msgs_sent = false; // Flag if initial state messages ware sent
		if ( ! inital_msgs_sent ) {
			// Serial_mysensors_logln("not inital_msgs_sent, sending states.");
			bool sendResult = true;
			sendResult &= inputList.sendStates(); 
			sendResult &= outputList.sendStates();
			/*
			msg.setType(V_TEXT);
			msg.setSensor(250);
			msg.set(F("Presentation done"));
			send(msg);
			*/
			if (sendResult) {
				sendStatusConfig(F("Presentation done"));
				inital_msgs_sent = true;
				// Serial_mysensors_logln("inital_msgs_sent = true;");
			} else {
				// Serial_mysensors_logln("inital_msgs_sent = false;");
			}
		}
		inputList.update(*this);
		outputList.update();
	}
	
	bool processMessage(const MyMessage &message) {
		
		if ( inputList.processMessage(message) ) {
			return true; 
		} else if ( outputList.processMessage(message) ) {
			return true;
		}
		// Serial_mysensors_logln("Unprocessed message type:",message.type);
		return false;
	}
	
	
	void configureInputOn(uint8_t inputPin, action_t action, uint8_t outputPin) {
		
		/*
		if ( inputs.validIdx(inputIdx) and outputList.validIdx(outputIdx) ) {
			inputs.inputs[inputIdx].onConfig.setAction(action,outputIdx);
			// sendStatusConfig("configure valid");
		} else {
			sendStatusConfig(F("nonvalid input/output idxs"));
		}
		*/
	}
	
	void configureInputOff(uint8_t inputPin, action_t action, uint8_t outputPin) {
		/*
		if ( inputs.validIdx(inputIdx) and outputList.validIdx(outputIdx) ) {
			inputs.inputs[inputIdx].offConfig.setAction(action,outputIdx);
			// sendStatusConfig("configure valid");
		} else {
			sendStatusConfig(F("nonvalid input/output idxs"));
		}
		*/
	}
};

// extern Butre butre;




#endif // __MYSENSORS_BUTRE_H_INCLUDED__
