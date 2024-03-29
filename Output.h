#ifndef __MYSENSORS_BUTRE_OUTPUT_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_OUTPUT_H_INCLUDED__   

#include <core/MySensorsCore.h>
#include "ConfigDefaults.h"
#include "Utils.h"

//#include "MySensors_Butre.h"


class Output
/*
 * We mean on/off as logical states
 * We mean high/low as physical pin state
 * If inverted  on = low, off=high
 * if not inverted (normal)   on = high,  off=low
 */
{
public:
	class Config 
	{
	public:
		//const uint16_t SWITCHBACK_DEFAULT_TIME_NEVER = 0; not used now, use switchback() 
		uint16_t switchBackTime = 0; // SWITCHBACK_DEFAULT_TIME_NEVER; 
                                             // Switchback time in seconds
		
		const uint8_t INVERTED = 0x1;   // Inverted set means active low
                                                // Inverted _not_ set means active high
                                                // Default is inverted 
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
        static MyMessage msg;
	unsigned long switchedOnTime = 0; // millis() when output was switched on
	// uint8_t sensorId;
	uint8_t _pin;
	//MyMessage msg;  // Keeps sensorId/pin  , 
                        // TODO: Consider using one MyMessage for all inputs/outputs ?
public:
    const static uint8_t INVALID= -1;  // Default invalid pin/sensor id value
    
    /*
    Output(uint8_t pin=INVALID):
      msg(pin, V_STATUS) // MyMessage (const uint8_t sensorId, const mysensors_data_t dataType)
    {}*/
    
    Output(uint8_t pin=INVALID,bool inverted=true, uint16_t switchBackTime = 0):
      // msg(pin, V_STATUS) // MyMessage (const uint8_t sensorId, const mysensors_data_t dataType)
      _pin(pin)
    {
	    config.setInverted(inverted);
            config.setSwitchBackTime(switchBackTime);
    }

    
    const uint8_t pin() 
    // Returns input's pin number
    {
	// return msg.sensor;
        return _pin;
    }
    
    const uint8_t sensorId()
    // Sensor id of output, for now same as pin
    {
        return _pin;
    }

    void configure(uint8_t pin) {
      //msg.setSensor(pin);
        _pin = pin;
    }

    void before() {
	// uint8_t pin = msg.sensor;
        pinMode(pin(), OUTPUT);
        bool is_on = false;   // TODO: Load state from EEPROM ?
        bool pin_high = is_on xor config.inverted();
        digitalWrite(pin(), pin_high);  // Off by default, level based on inverted()
    }

    void present() {
	// bool present(uint8_t childSensorId, uint8_t sensorType, const char *description, bool echo);
	// ::present(msg.sensor, S_BINARY,F("Output"));
        ::present(pin(), S_BINARY,F("Output"));
    }
    
    bool isOn(){
	    //uint8_t pin = msg.sensor;
	    auto pin_state = digitalRead(pin());
	    return bool(pin_state) xor config.inverted();
    }
    
    void update() {
	    if (config.switchback() and isOn() ) {
		    //  if (millis () - startTime >= interval)
		    if ( millis() - switchedOnTime >= (unsigned long)config.switchBackTime*1000 ) {
			set(false);
		    }
	    }
    }

    void set(bool newState) {
        // Sets logical on/off state and sends MyMessage back to controller 
        // uint8_t pin = msg.sensor;
        bool pinHigh = newState xor config.inverted();
        digitalWrite(pin(), pinHigh );
        // Serial_mysensors_logln("pin: ", msg.sensor, " set to new level: ", pinHigh );
        // TODO: Save state to EEPROM ?
        switchedOnTime = millis();
        sendState();
    }

    void toggle() {
        set(not isOn() ); 
    }
    
    bool sendState() {
      //uint8_t pin = msg.sensor;
      auto pin_state = digitalRead(pin());  // https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
      msg.setSensor(pin());
      msg.set( pin_state xor config.inverted() ); 
      bool reached = send(msg); // https://www.mysensors.org/download/sensor_api_20
      // Serial_mysensors_logln("sendState() pin: ", pin(), " send(msg) ->  ", reached );
      return reached;
    }

    bool processMessage(const MyMessage & recv_msg) {
      if ( sensorId() != recv_msg.sensor) {
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
