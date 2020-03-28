#ifndef __MYSENSORS_BUTRE_OUTPUT_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_OUTPUT_H_INCLUDED__   

#include <core/MySensorsCore.h>
#include "Utils.h"

//#include "MySensors_Butre.h"


class Output
/*
 * We mean on/off as logical states
 * We mean high/low as phisical pin state
 * If inverte  on = low, off=high
 * if not inverted (normal)   on = high,  off=low
 */
{
public:
	class Config 
	{
	public:
		//const uint16_t SWITCHBACK_DEFAULT_TIME_NEVER = 0; not used now, use switchBack() 
		uint16_t switchBackTime = 0; // SWITCHBACK_DEFAULT_TIME_NEVER; //  
		
		const uint8_t INVERTED = 0x1;
		const uint8_t SWITCHBACK = 0x2; // Use switchBackDefaultTime time to switch back to off 
		uint8_t flags = INVERTED;
		
		void setSwitchBackTime(uint16_t t) {
			switchBackTime = t;
			if (t) {
				flags |= SWITCHBACK; 
			} else {
				flags &= ~SWITCHBACK;
			}
		}
		
		void setInverted(bool inverted) {
			if (inverted) {	
				flags |= INVERTED;
			} else {
				flags &= ~INVERTED;
			}
			
		}
		bool switchback() {
			return flags & SWITCHBACK;
		}
		bool inverted() {
			return flags & INVERTED;
		}
	} config;
private:
	// uint8_t sensorId;
	// uint8_t pin;
	MyMessage msg;  // Keeps sensorId/pin
	unsigned long switchedOnTime = 0; // millis() when output was switched on

public:
    const static uint8_t INVALID= -1;  // Default invalid pin/sensor id value
    
    Output(uint8_t pin=INVALID):
      msg(pin, V_STATUS) // MyMessage (const uint8_t sensorId, const mysensors_data_t dataType)
    {}
    
    const uint8_t pin() 
    // Returns input's pin number
    {
	    return msg.sensor;
    }
    

    void configure(uint8_t pin) {
      msg.setSensor(pin);
    }

    void before() {
	uint8_t pin = msg.sensor;
      pinMode(pin, OUTPUT);
      bool is_on = false;   // TODO: Load state from EEPROM ?
      bool pin_high = is_on xor config.inverted();
      digitalWrite(pin, 1);  // Off, as inverted by default - active on 0 (drain)
    }

    void present() {
	// bool present(uint8_t childSensorId, uint8_t sensorType, const char *description, bool echo);
	::present(msg.sensor, S_BINARY,F("Output"));
    }
    
    bool isOn(){
	    uint8_t pin = msg.sensor;
	    auto pin_state = digitalRead(pin);
	    return bool(pin_state) xor config.inverted();
    }
    
    void update() {
	    if (config.switchback() and isOn() ) {
		    //  if (millis () - startTime >= interval)
		    if ( millis() - switchedOnTime >= config.switchBackTime*1000 ) {
			set(false);
		    }
	    }
    }

	void set(bool newState) {
	    // Sets logical on/off state and sends MyMessage back to controller 
		uint8_t pin = msg.sensor;
		bool pinHigh = newState xor config.inverted();
		digitalWrite(pin, pinHigh );
		// TODO: Save state to EEPROM ?
		switchedOnTime = millis();
		sendState();
	}
    
	void toggle() {
		set(not isOn() ); 
	}
    
    bool sendState() {
      uint8_t pin = msg.sensor;
      auto pin_state = digitalRead(pin);  // https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
      msg.set( pin_state xor config.inverted() ); 
      return send(msg);
    }

    bool processMessage(const MyMessage & recv_msg) {
      if (msg.sensor != recv_msg.sensor) {
        return false;
      }
      if (recv_msg.type == V_STATUS ) {  
        // TODO: && recv_msg.getCommand() == C_REQ / C_SET 
        bool val = recv_msg.getBool();
        set(val);
        return true;
      }
      return false;
    }
};







#endif // __MYSENSORS_BUTRE_OUTPUT_H_INCLUDED__   
