#include "akbd.h"


akbd::akbd(int pin_nbr)
{
  _pin_nbr = pin_nbr;
  pinMode(_pin_nbr, INPUT);  
  nbr_keys = NBR_KEYS;
}

void akbd::begin(void)
{
  kbdState=0;
  add_on_off_bit = false;
}

void akbd::set_nbr_keys(uint8_t n){
	nbr_keys = n;
}

void akbd::enable_on_off(bool en_on_off){
	add_on_off_bit = en_on_off;
}


void akbd::set_aval(byte key_indx, uint16_t key_value){
    key_val[key_indx] = key_value;
}    

//int kbdPin = 15; 
int akbd::rd_analog(void){
  return( analogRead(_pin_nbr));
}

void akbd::scan(void) {
	int kbdVal = 0; 
	int d;
	int i=0;
	char k=0;
	kbdVal = analogRead(_pin_nbr);

	if (kbdVal > KEY_TOL ){
		while (i< nbr_keys){
			d = kbdVal-key_val[i];
			d = abs(d);
			if (d <= KEY_TOL) {
				k = i+'0';
				i =99;
			}
			else i++;
		}  
		switch(k){    // fix asterisk and hash ASCII codes
			  case '0'+10: k='*'; break;
			  case '0'+11: k='#'; break;
			  case '0'+12: k='@'; break;
			  case '0'+13: k='='; break;
			  case '0'+14: k='>'; break;
			  case '0'+15: k='<'; break;
		}
	} 	
	switch( kbdState ){	
	case 0:  // no key pressed
		if (k != 0) {
		    lastKey = k;
		    kbdDebCntr=KBD_DEB;
			kbdPushCntr = 0;
			kbdState= 1;
		}
		break;
	case 1:  // key pressed but debounce still active
		if (k == lastKey) {
			if (kbdDebCntr) 
			{
				kbdDebCntr--;
			}	
			else 
			{ 
				kbdState= 2;
				kbdPushCntr = 0;
			}	   
		} else kbdState = 0;
		break;
		
	case 2:  // key is still pressed	
		if (k != lastKey) 
		{ 
			kbdState = 3;
		}
		else 
		{ 
			kbdPushCntr++;    // with 10ms scan period the risk of overflow can be neglected
		}			  

	case 3:  // key pressed and released, accepted, not read
		  
		break;
	case 4:  // key read
		kbdState = 0;
		break;
	}

}

char akbd::read(void){
  char k = 0;	
  if (kbdState == 3)
  { 
     kbdState = 4;
	 k = lastKey;
	 if ((kbdPushCntr > 100) && add_on_off_bit)
	 {
	     k = lastKey | 0b10000000;
     }		 
  } 
  return(k);

}
