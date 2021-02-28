#ifndef __MYSENSORS_BUTRE_UTILS_H_INCLUDED__ 
#define __MYSENSORS_BUTRE_UTILS_H_INCLUDED__   

#include <Bounce2.h>


static void
Serial_mysensors_log_intro()
{
	Serial.print("0;255;3;0;9;");
}

static void 
Serial_mysensors_logln(const char * txt)
{
	Serial_mysensors_log_intro();
	Serial.println(txt);
};

static void
Serial_mysensors_logln(const char * txt, int val)
{
	Serial_mysensors_log_intro();
	Serial.print(txt);
	Serial.print(val);
	Serial.println();
};

static void
Serial_mysensors_logln(const char * txt, float val)
{
	Serial_mysensors_log_intro();
	Serial.print(txt);
	Serial.print(val);
	Serial.println();
};


static void
Serial_mysensors_logln(const char * txt, int val,const char * txt2, int val2)
{
	Serial_mysensors_log_intro();
	Serial.print(txt);
	Serial.print(val);
	Serial.print(txt2);
	Serial.print(val2);
	Serial.println();
};



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
