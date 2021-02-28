#ifndef __MYSENSORS_BUTRE_BUTRE_DHD_INCLUDED__ 
#define __MYSENSORS_BUTRE_BUTRE_DHD_INCLUDED__   

#include "DHT.h"
#include <core/MySensorsCore.h>


class ButreDHT {
private:
    uint8_t _pin;
    uint8_t _humSensorId;
    MyMessage msg; // FUTURE: Use one MyMesssage struct for all sending data in Butre ?
    bool inital_msgs_sent = false; // Flag if initial state messages ware sent , or was requested again    , FUTURE: Use one global flag in Butre instance ?
public:
    DHT dht;
    
    ButreDHT(uint8_t pin, uint8_t humSensorId, uint8_t type):
        dht(pin,type) 
    {
        // We need to store copy of pin as uint8_t _pin, _type; are private in DHT class :(
        _pin = pin;
        _humSensorId = humSensorId;
    };
    
    uint8_t pin() const {
        return _pin;
    }
    
    void begin() 
    {
        dht.begin();
    };
    
    void present()
    {
        ::present(pin(), S_TEMP, F("Temperature"));        
        ::present(_humSensorId, S_HUM, F("Humidity"));
    };
    
    
    bool sendState() {
        Serial_mysensors_logln("Reading dht values");
        // Read temperature as Celsius (the default)
        float t = dht.readTemperature();
        Serial_mysensors_logln("Sending temp ",t);
        msg.setSensor(_pin);
        msg.setType(V_TEMP);  
        bool sendResult = send(msg.set(t,1));
        
        float h = dht.readHumidity();
        Serial_mysensors_logln("Sending hum ",h);
        msg.setSensor(_humSensorId);
        msg.setType(V_HUM);
        sendResult &= send(msg.set(h,1));
        return sendResult;
        
    }
    // update(Butre & butre)   // For now we will respond only to pulls 
    
    bool processMessage(const MyMessage &recvMsg) {
        if (pin() == recvMsg.sensor or recvMsg.sensor == _humSensorId ) {
            if (recvMsg.type == V_STATUS && recvMsg.getCommand() == C_REQ ) {
                sendState();
            }
            return true;
        } /* else if (recvMsg.sensor == _humSensorId) {
            if (recvMsg.type == V_STATUS && recvMsg.getCommand() == C_REQ ) {
                // sendHumState();
                sendState();
            }
            return true;
        }*/
        return false;
    };
    
    void loop(){
        // FUTURE: Merge with butre loop ?
        if ( ! inital_msgs_sent ) {
            bool sendResult = sendState();
            if (sendResult) {
                inital_msgs_sent = true;
            } else {
            }
        }
    }
};



#endif # MYSENSORS_BUTRE_BUTRE_DHD_INCLUDED
