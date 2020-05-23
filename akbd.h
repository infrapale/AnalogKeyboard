#ifndef akbd_h
#define akbd_h
#include "Arduino.h"

#define NBR_KEYS 16
#define KBD_PIN 15
#define KEY_TOL 16
#define KBD_DEB 2

class akbd
{
  public:
    akbd(int pin_nbr);
    void begin(void);
	void set_nbr_keys(uint8_t n);
	void enable_on_off(bool en_on_off);
    void set_aval(byte key_indx, uint16_t key_value);
    void scan(void);
    char read(void);
    int rd_analog(void);
  private:
    int _pin_nbr;
	uint8_t  nbr_keys;
	volatile bool add_on_off_bit; 
    volatile char lastKey;
    volatile int       kbdDebCntr;
	volatile uint16_t  kbdPushCntr;
    volatile int  kbdState;
    volatile uint16_t  key_val[NBR_KEYS] = {
      925,    //0   
      48,     //1  
      86,     //2  
      129,    //3  
      195,    //4  
      308,    //5  
      410,    //6  
      545,    //7  
      692,    //8  
      783,    //9  
      863,    //asterisk  
      959     //hash     
  
};

};

#endif

