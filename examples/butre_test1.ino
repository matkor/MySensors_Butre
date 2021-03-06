// Enable debug prints to serial monitor
// #define MY_DEBUG

// Enable serial gateway
#define MY_GATEWAY_SERIAL

// Define a lower baud rate for Arduino's running on 8 MHz (Arduino Pro Mini 3.3V & SenseBender)
#if F_CPU == 8000000L
#define MY_BAUD_RATE 38400
#endif

// NOTE: MySensors.h must be include in sketch (.ino) file so MySensors_Butre has include paths set to MySensors directory
//        and is able to #include <core/MySensorsCore.h>
#include <MySensors.h>
#include <MySensors_Butre.h>


// Optional method - for initialisations that needs to take place before MySensors transport has been setup (eg: SPI devices).
void before() {
  // Serial_mysensors_logln("CALLED: before()");
  // button_set.before();
  // relay_set.before();
  butre.before();
  // Serial_mysensors_logln("DONE: before()");

  butre.configureInputOn(0,ACTION_TOGGLE,0);
  butre.configureInputOn(1,ACTION_TOGGLE,1);

  butre.outputs.outputs[0].config.setSwitchBackTime(3);
  butre.outputs.outputs[0].config.setInverted(0);
  
  butre.outputs.outputs[1].config.setSwitchBackTime(10);

  butre.outputs.outputs[2].config.setInverted(0);
  
  
}

void setup() {
  // put your setup code here, to run once:

}

void presentation()
{
  // Serial_mysensors_logln("CALLED: presentation()");
  // Send the sketch version information to the gateway and Controller
  
  // NOTE: Home Assistant used name of sketch as part of entity name
  // sendSketchInfo("Butre Test", "0.1");
  // button_set.present();
  // relay_set.present();
  butre.present("Butre Test", "0.1");
  // Serial_mysensors_logln("DONE: presentation()");
}


void loop() {
  butre.loop();
  
}


void receive(const MyMessage &message) {
  // Serial_mysensors_logln("Message received");
  if (butre.processMessage(message)) {
    // message was targeted to Butre
  }
  /*
  if (message.type == V_STATUS) {
    //Serial_mysensors_log_intro();
    //Serial.print("message V_STATUS for sensor: ");
    //Serial.print(message.sensor);
    //Serial.print(", requested status: ");
    //Serial.println(message.getBool());
    if ( .process_message(message) ) {
      // Serial_mysensors_logln("Message accepted by relay_set");
    } else if ( button_set.process_message(message) ) {
      
    }
  } */
}
