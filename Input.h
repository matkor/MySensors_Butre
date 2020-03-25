#ifndef __MYSENSORS_BUTRE_INPUT_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_INPUT_H_INCLUDED__   

// https://forum.mysensors.org/topic/11005/how-can-one-use-mymessage-class-in-library/2
// #define MY_CORE_ONLY
//#include <MySensors.h>
#include <core/MySensorsCore.h>

// #include "MySensors_Butre.h"
#include "Utils.h"
#include "ActionConfig.h"

class Input
{
  private:
    BounceExt debouncer; // https://github.com/thomasfredericks/Bounce2/wiki
    // uint8_t pin;  // Needed as: error: 'uint8_t Bounce::pin' is protected
    uint8_t sensorId;
    MyMessage msg;


  public:
    ActionConfig onConfig;
    ActionConfig offConfig;
  
    const static uint8_t INVALID= -1;  // Default invalid pin/sensor id value
    Input(uint8_t sensorId = INVALID, uint8_t pin=INVALID, unsigned long debounce_interval_millis=10):
      debouncer(pin, debounce_interval_millis)
      , msg(sensorId, V_STATUS) // MyMessage (const uint8_t sensorId, const mysensors_data_t dataType)
      // S_BINARY sends V_STATUS
      // ,sensorId(sensorId)
      // ,pin(pin)
    {}

    void configure(uint8_t sensorId, uint8_t pin,unsigned long debounce_interval_millis=10) {
      msg.setSensor(sensorId);
      pinMode(pin, INPUT_PULLUP); 
      debouncer.attach(pin);
      debouncer.interval(debounce_interval_millis);
    }

    void present()
    {
	// bool present(uint8_t childSensorId, uint8_t sensorType, const char *description, bool echo);
      // msg.getSensor  (   void      )
      // ::present(msg.getSensor(), S_BINARY);
      ::present(msg.sensor, S_BINARY, F("Input"));
      //Serial_mysensors_logln("Button presented as sensorId: ",msg.sensor); // Id of sensor that this message concerns. 
    }
    //    void
    //    attach(uint8_t pin, uint16_t interval_millis){
    //      debounce.attach(pin)
    //      debounce.
    //    }

    // enum button_change_t { NO_CHANGE=0, RELEASED=1, PUSHED=2 } ;

    bool sendState() {
      bool pin_state = debouncer.read();
      bool state = !pin_state; // TODO: not always inverted
      return send(this->msg.set(state));  // Not pressed is HIGH
    }

    // button_change_t update()
    bool update()
    // Calculate current button state, send update msg if change detected
    {
      if (debouncer.update()) {
        // Get the update value.        
        // Send in the new value.
        bool pin_state = sendState();
        if (pin_state) {
          onConfig.performAction();
          //return PUSHED;
        } else {
          offConfig.performAction();
          //return RELEASED;
        }
        return true;
      }
      // return NO_CHANGE;
      return false;
    };


    bool processMessage(const MyMessage & recvMsg) {
      // Returns if message was targeted to current sensor.
      // 	
      if (msg.sensor != recvMsg.sensor) {
        return false;
      }
      if (recvMsg.type == V_STATUS && recvMsg.getCommand() == C_REQ ) {
        sendState();
        return true;
      }
      // TODO: If set state, consider performing actions like new state?
      return false;
    }    
};


#endif // __MYSENSORS_BUTRE_INPUT_H_INCLUDED__   
