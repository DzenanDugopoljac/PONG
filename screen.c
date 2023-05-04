#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


void SetPixel(int x, int y) {
  int shift = 0;
    if (y > 0) {
      
      shift = y / 8;
    }
    
    display[shift * 128 + x] |= 1 << (y - shift * 8);     
}

void Paddle(int x, int y){

  int i;
  for(i = 0; i < 8; i ++)
    {
      SetPixel(x,y+i);
    }
}

void Ball(int x, int y){

  SetPixel(x , y);
}


void cleardisplay() {
  int i;
  for (i = 0; i < sizeof(display); i++)
      {
	display[i] = 0;
      }
}


