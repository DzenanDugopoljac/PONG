#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


int getsw(void){

  int switches;
  switches = (PORTD >> 8) & 0xf;
  
 return switches; 
}


int getbtns(void){

  int buttons;
  
  buttons = ((((PORTD >> 5) & 0x7) << 1) | ((PORTF >> 1) & 0x1));
 
  
  return buttons;
 
 return PORTD;
}



  

