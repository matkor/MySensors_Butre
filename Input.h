#ifndef __MYSENSORS_BUTRE_INPUT_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_INPUT_H_INCLUDED__   

// https://forum.mysensors.org/topic/11005/how-can-one-use-mymessage-class-in-library/2
// #define MY_CORE_ONLY
//#include <MySensors.h>
#include <core/MySensorsCore.h>

// #include "MySensors_Butre.h"
#include "ConfigDefaults.h"
#include "Utils.h"
#include "ActionConfig.h"


class Butre;

class Input
{
  private:
    static MyMessage msg; // Common to all Inputs sending message
  
  private:
    BounceExt debouncer; // https://github.com/thomasfredericks/Bounce2/wiki
    // uint8_t pin;  // Needed as: error: 'uint8_t Bounce::pin' is protected
    uint8_t sensorId;
    // MyMessage msg;   // 


  public:
    // ActionConfig onConfig;
    // ActionConfig offConfig;
  
    const static uint8_t INVALID= -1;  // Default invalid pin/sensor id value
    
    // Input(uint8_t sensorId = INVALID, uint8_t pin=INVALID, unsigned long debounce_interval_millis=10):
    Input(uint8_t pin=INVALID, unsigned long debounce_interval_millis=10):
      debouncer(pin, debounce_interval_millis)
      // , msg(pin, V_STATUS) // MyMessage (const uint8_t sensorId, const mysensors_data_t dataType)
      // S_BINARY sends V_STATUS
      ,sensorId(sensorId)
      // ,pin(pin)
    {}

    const uint8_t pin() 
    // Returns input's pin number
    {
	return sensorId;
    }
    
    void before() 
	// initialisations that needs to take place before MySensors transport has been setup (eg: SPI devices).
    {	
      // const uint8_t pin = msg.sensor;
      // pinMode(pin, INPUT_PULLUP);
      pinMode(pin(), INPUT_PULLUP); 
      // Serial_mysensors_logln("Input configured pin: ", pin);
    }

    void present()
    {
      // ::present(msg.sensor, S_BINARY, F("Input"));
      ::present(pin(), S_BINARY, F("Input"));
      //Serial_mysensors_logln("Button presented as sensorId: ",msg.sensor); // Id of sensor that this message concerns. 
    }

    // enum button_change_t { NO_CHANGE=0, RELEASED=1, PUSHED=2 } ;
    bool sendState() {
      bool state; 
      return sendState(state);
    }

    bool sendState(bool & logLevel) {  // TODO: Rename state to logLevel and pin_state to pinHigh
        bool pin_state = debouncer.read();
        logLevel = !pin_state; // TODO: Not always inverted (not pressed is HIGH)
                            // use INVERTED flag 
                            // and  setInverted(bool inverted) / bool inverted() like in Output.h/cpp
        msg.setSensor(pin());
        msg.set(logLevel);
        return send(msg);
    }
    
    bool update(Butre & butre);
    // Calculate current button state, send update msg if change detected
    // Execute butre actions if defined
    
    

    bool processMessage(const MyMessage & recvMsg) {
      // Returns if message was targeted to current sensor.
      // 	
      //if (msg.sensor != recvMsg.sensor) {
      if (pin() != recvMsg.sensor) {
        return false;
      }
      if (recvMsg.type == V_STATUS && recvMsg.getCommand() == C_REQ ) {
        sendState();
        return true;
      }
      // TODO: If set state, consider performing actions like new state?
      return true;
    }    
};


#endif // __MYSENSORS_BUTRE_INPUT_H_INCLUDED__   
