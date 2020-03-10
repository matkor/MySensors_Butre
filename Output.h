#ifndef __MYSENSORS_BUTRE_SIMPLE_RELAY_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_SIMPLE_RELAY_H_INCLUDED__   

#include <core/MySensorsCore.h>
#include "Utils.h"

//#include "MySensors_Butre.h"

class Output
{
  
  private:
    // uint8_t sensorId;
    uint8_t pin;
    MyMessage msg;

  public:
    const static uint8_t INVALID= -1;  // Default invalid pin/sensor id value
    
    Output(uint8_t sensorId=INVALID, uint8_t pin=INVALID):
      msg(sensorId, V_STATUS) // MyMessage (const uint8_t sensorId, const mysensors_data_t dataType)
      , pin(pin)
    {}

    void configure(uint8_t sensorId, uint8_t pin) {
      this->pin = pin;
      msg.setSensor(sensorId);
    }

    void before() {
      pinMode(pin, OUTPUT);
      // TODO: Load state from EEPROM ?
      // TODO: Not always inverted
      digitalWrite(pin, 1);  // Off, as inverted by default - active on 0 (drain)
    }

    void present() {
      ::present(msg.sensor, S_BINARY);
    }

    void set(bool new_state) {
        digitalWrite(pin, !new_state ); // TODO: not always inverted
        // TODO: Save state to EEPROM ?
        // void saveState(uint8_t pos, uint8_t value);   // https://www.mysensors.org/download/sensor_api_20
        // pos = sensorId ?
        
        // Serial_mysensors_logln("Output.set(): pin: ",pin);
        // Serial_mysensors_logln("                 state: ",!new_state);
        
        update();
    }
    void toggle() {
      auto pin_state = digitalRead(pin);
      set(pin_state); // TODO: not always inverted
    }
    
    void update() {
      auto pin_state = digitalRead(pin);  // https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
      msg.set( ! pin_state); // TODO: not always inverted
      send(msg);
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







#endif // __MYSENSORS_BUTRE_SIMPLE_RELAY_H_INCLUDED__   
