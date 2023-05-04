/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
//#define TRISE PIC32_R(0x86100) = *(volatile unsigned*)(0xbf800000 + (0x86100))
//#define PORTE PIC32_R(0x86110) = *(volatile unsigned*)(0xbf800000 + (0x86110))
PRTE = 0;
int paddle1 = 13;
int paddle2 = 13;
int timeoutcount = 0;



uint8_t display[128*32] = {0};    



/* Interrupt Service Routine */
void user_isr( void ){


  if(IFS(0) & 0x8000){
    IFSCLR(0) = 0x8000;
     PORTE++;
 }

  if(IFS(0) & 0x0100){
     IFSCLR(0) = 0x0100;         // reset Timer 2, by doing this we acknowledge
     timeoutcount++;             // interrupts from Timer 2 

 
   
    
  }
}
 


/* Lab-specific initialization goes here */
void labinit( void )
{
    int switches;
   
    TRISE &= ~0xff;   // bits 7 through = 0    (output)
    TRISD = 0xFE0;    // bits 11 through 5 = 1 (input)
  

    T2CON  = 0x0;
    // T2CONSET = 0x50;  // prescale 1:38
    T2CONSET = 0x70;     // prescale 1:256 so that we are able to get an update after every 10 timeouts events.
    TMR2 = 0x0;          // clear timer register
    //PR2 = 25000;       // 25 000 period
    PR2 = 31250;         // 31 250 period
   
    T2CONSET = 0x8000; // start timer

    IECSET(0) = 0x0100;      // enable the interrupt for timer 2
    IPCSET(2) = 0x0012;      // set highest prioritys for T2IP and T2IS (subpriority)
   
    
    IECSET(0) = 0x8000;      // enable the interrupt for timer 2 switch 3
    IPCSET(3) = 0x1200;        // set highest priority for switch
   
    
    enable_interrupt();

  return;
}



/* This function is called repetitively from the main program */
void labwork( void ){
 
  if((getbtns() == 0x8) && (paddle1 > 0)){
   
    Paddle(0, paddle1 -= 1);
  }
  if((getbtns() == 0x4) && (paddle1 < 24)){
   
      Paddle(0, paddle1 += 1);
    }
  if((getbtns() == 0x2) && (paddle2 > 0)){
 
    Paddle(127, paddle2 -= 1);
  }

  if ((getbtns() == 0x1) && (paddle2 < 24)){
   
      Paddle(127, paddle2 += 1);
    }
  

  win();
  cleardisplay();
  
  Paddle(1, paddle1); // left paddle
  Paddle(127,paddle2); // Right paddle
  
  ball_movement(paddle1, paddle2);
  delay(15);
  
  DisplayImage(display);



 
  

  
} 



