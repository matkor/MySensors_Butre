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
    ActionConfig pushed_config;
    ActionConfig released_config;
  
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
      this->debouncer.attach(pin);
      this->debouncer.interval(debounce_interval_millis);
    }

    /*
    void configure_action_pushed(action_t action, uint8_t relay_idx)
    {
      if ( valid_relay_idx(relay_idx) ) {
        this->pushed_config.action = action;
        this->pushed_config.relay_idx = relay_idx;
      } else {
          this->pushed_config.disable();
      }
    }
    */
    

    //void setup() {
    //  pinMode(debouncer.get_pin(), INPUT_PULLUP);
    //}

    void present()
    {
      // msg.getSensor  (   void      )
      // ::present(msg.getSensor(), S_BINARY);
      ::present(msg.sensor, S_BINARY);

      //Serial_mysensors_logln("Button presented as sensorId: ",msg.sensor); // Id of sensor that this message concerns. 

    }
    //    void
    //    attach(uint8_t pin, uint16_t interval_millis){
    //      debounce.attach(pin)
    //      debounce.
    //    }

    enum button_change_t { NO_CHANGE=0, RELEASED=1, PUSHED=2 } ;

    bool send_state() {
      bool pin_state = debouncer.read();
      send(this->msg.set(!pin_state));  // Not pressed is HIGH
      return pin_state;
    }

    button_change_t update()
    // Calculate current button state, send update msg if change detected
    {
      if (debouncer.update()) {
        // Get the update value.
        
        // Send in the new value.
        bool pin_state = send_state();
        if (pin_state == HIGH) {
          // Serial_mysensors_logln("Button released");
          //action_released();
          released_config.perform_action();
          return RELEASED;
        } else {
          // Serial_mysensors_logln("Button pushed");
          //action_pushed();
          pushed_config.perform_action();
          return PUSHED;
        }
      }
      return NO_CHANGE;
    };

    // void action_pushed();

    // void action_released();


    bool processMessage(const MyMessage & recv_msg) {
      // Returns if message was targeted to current sensor.
      // 
      if (msg.sensor != recv_msg.sensor) {
        return false;
      }
      if (recv_msg.type == V_STATUS && recv_msg.getCommand() == C_REQ ) {
        send_state();
        return true;
      }
      // TODO: If set state, consider performing actions like new state?
      return false;
    }
    
};



#endif // __MYSENSORS_BUTRE_INPUT_H_INCLUDED__   
