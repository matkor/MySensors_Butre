
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
#include "Button.h"
#include "SimpleRelay.h"
#include "SimpleRelaySet.h"
#include "InputList.h"


extern SimpleRelaySet relay_set;
extern ButtonSet button_set;


class Butre {
private:
	MyMessage msg;
public: 
	void present(const char * sketchName, const char * version) 
	{
		// bool sendSketchInfo(const char *name, const char *version, bool echo);
		sendSketchInfo(sketchName, version);
		button_set.present();
		relay_set.present();
		
		// bool present(uint8_t childSensorId, uint8_t sensorType, const char *description, bool echo);
		::present(250,S_INFO,F("Status/config"));
	}
	
	void loop() {
		bool static inital_msgs_sent = false; // Flag if initial state messages ware sent
		if ( ! inital_msgs_sent ) {
			button_set.send_states(); 
			relay_set.update();
			msg.setType(V_TEXT);
			msg.setSensor(250);
			msg.set(F("Presentation done"));
			send(msg);
			inital_msgs_sent = true;
		}
		button_set.update();
	}
	
};

extern Butre butre;




#endif // __MYSENSORS_BUTRE_H_INCLUDED__
