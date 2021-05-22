#ifndef __MYSENSORS_BUTRE_BUTRE_DHD_INCLUDED__ 
#define __MYSENSORS_BUTRE_BUTRE_DHD_INCLUDED__   

#include <math.h>

#include "DHT.h"
#include <core/MySensorsCore.h>


class ButreDHT {
private:
    uint8_t _pin;  // NOTE: Could be accessible from DHT object.
    uint8_t _humSensorId;
    MyMessage msg; // FUTURE: Use one MyMesssage struct for all sending data in Butre ?
    bool inital_msgs_sent = false; // Flag if initial state messages ware sent , or was requested again    , FUTURE: Use one global flag in Butre instance ?
    float lastTemp;
    float lastHum;
    float tempHysteresis = 0.1;
public:
    DHT dht;
    
    ButreDHT(uint8_t pin, uint8_t humSensorId, uint8_t type):
        dht(pin,type) 
    {
        // We need to store copy of pin as uint8_t _pin, _type; are private in DHT class :(
        _pin = pin;
        _humSensorId = humSensorId;
        lastTemp = NAN;  // Last sent temp value
        lastHum = NAN;   // Last sent hum value
        
        
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
    
    
    /*
    bool sendState(float temp, float hum) {
        // Serial_mysensors_logln("Reading dht values");
        // Read temperature as Celsius (the default)
        //float t = dht.readTemperature();
        Serial_mysensors_logln("Sending temp ",temp);
        msg.setSensor(_pin);
        msg.setType(V_TEMP);  
        bool sendResult = send(msg.set(temp,1));
        if (sendResult) {
            lastTemp = temp;
        }
        
        // float h = dht.readHumidity();
        Serial_mysensors_logln("Sending hum ",hum);
        msg.setSensor(_humSensorId);
        msg.setType(V_HUM);
        // sendResult &= send(msg.set(h,1));
        bool sendResultHum = send(msg.set(hum,1));
        if (sendResultHum) {
            lastHum = hum;
        }
        return sendResult and sendResultHum;
    } */
    
    
    
    bool sendTemp(float temp) {
        // Serial_mysensors_logln("Sending temp ",temp);
        msg.setSensor(_pin);
        msg.setType(V_TEMP);  
        msg.set(temp,1);
        bool sendResult = send(msg);  // Returns true if message reached the first stop on its way to destination. https://www.mysensors.org/download/sensor_api_20#sending-data
        // Serial_mysensors_logln("sendTemp(): sendResult: ", sendResult);
        
        if (sendResult) {
            if (isnan(lastTemp)) {
                lastTemp = temp;
                // Serial_mysensors_logln("sendTemp(): first temp reading, tempHysteresis/2.0: ", float(tempHysteresis/2.0));
            } else if ( temp > lastTemp) {
                lastTemp = temp - (tempHysteresis/2.0);
                // Serial_mysensors_logln("sendTemp(): temp raising, tempHysteresis/2.0: ", float(tempHysteresis/2.0));
            } else { // We never sendTemp when is no change bigger than tempHysteresis, so there must have been decrese in temp
                lastTemp = temp + (tempHysteresis/2.0);
                // Serial_mysensors_logln("sendTemp(): temp falling, tempHysteresis/2.0: ", float(tempHysteresis/2.0));
            }
        } 
        return sendResult;
    }
    
    bool sendHum(float hum) {
        // Serial_mysensors_logln("Sending hum ",hum);
        msg.setSensor(_humSensorId);
        msg.setType(V_HUM);
        msg.set(hum,1);
        bool sendResult = send(msg);
        if (sendResult) {
            lastHum = hum;
        }
        return sendResult;
    }
    
    bool sendState(float temp, float hum) {
        if ( not sendTemp(temp) ) {
            return false;
        }
        return sendHum(hum);
    }
        
    
    // update(Butre & butre)   // For now we will respond only to pulls 
    
    bool processMessage(const MyMessage &recvMsg) {
        if (pin() == recvMsg.sensor or recvMsg.sensor == _humSensorId ) {
            if (recvMsg.type == V_STATUS && recvMsg.getCommand() == C_REQ ) {
                update();
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
    
    bool update() 
    {
        bool sendResult = true;
        unsigned long t = micros();
        float temp = dht.readTemperature();
        float hum = dht.readHumidity();
        
        t = micros() - t;
        if (t > 100) { // Seems take 56 us ?!?
            // Serial_mysensors_logln("DHT reading time: ",t);  // 22 ms 
            // Serial_mysensors_logln("Temp: ", temp, " prev temp: ", lastTemp);
            if ( not isnan(temp)) {
                if (isnan(lastTemp)) {
                    // Serial_mysensors_logln("Sending initial temp: ", temp);
                    sendResult = sendResult and sendTemp(temp);
                } else {
                    if ( abs(lastTemp - temp) > tempHysteresis ) {
                        // Serial_mysensors_logln("Sending updated temp: ", temp);
                        sendResult = sendResult and sendTemp(temp);
                    } else {
                        // Serial_mysensors_logln("Not sending same temp: ", temp);
                    }
                }
            }
        }
        return sendResult;
    }
    
    void loop() {
        // FUTURE: Merge with butre loop ?
        /*
        if ( ! inital_msgs_sent ) {
            bool sendResult = sendState();
            if (sendResult) {
                inital_msgs_sent = true;
            } else {
            }
        }*/
        /*
        if ( isnan(lastHum) or isnan(lastTemp) ) {
            sendState();
        } else {
            update()
        }*/
        update();
    }
};



#endif # MYSENSORS_BUTRE_BUTRE_DHD_INCLUDED
