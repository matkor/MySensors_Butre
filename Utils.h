#ifndef __MYSENSORS_BUTRE_UTILS_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_UTILS_H_INCLUDED__   

#include <Bounce2.h>

/*
void
Serial_mysensors_log_intro()
{
	Serial.print("0;255;3;0;9;");
}

void
Serial_mysensors_logln(const char * txt)
{
	Serial_mysensors_log_intro();
	Serial.println(txt);
};

void
Serial_mysensors_logln(const char * txt, int val)
{
	Serial_mysensors_log_intro();
	Serial.print(txt);
	Serial.print(val);
	Serial.println();
};
*/

class BounceExt: public Bounce
{
  public:
    BounceExt(uint8_t pin, uint16_t interval_millis ) :
      Bounce(pin, interval_millis) {};
    uint8_t get_pin() {
      return pin;
    }
};


#endif // __MYSENSORS_BUTRE_UTILS_H_INCLUDED__
