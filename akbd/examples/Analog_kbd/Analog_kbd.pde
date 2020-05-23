// T056  Analog Keyboard Test Sketch 
// 2011-05-27 
// This example code is in the public domain.

#include <akbd.h>

akbd kbd(1);
char key;
int aval;


void setup()
{
  Serial.begin(9600);  // start serial for output
  kbd.begin();
  //kbd.set_aval(1,99);  //if preset values not OK
}

void loop()
{
  while(1){
    kbd.scan();
    delay(10);
    
    key = kbd.read();
    if (key) {
      Serial.println(key);
    }
  }
  //delay(1000);
  //aval = kbd.rd_analog();
  //Serial.println(aval);
  
  
}
