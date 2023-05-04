#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

int pos_x = 64;
int pos_y = 16;
int direction_x = 1;
int direction_y = 0;
int left_paddle = 1;
int right_paddle = 127;
int goal_player1 = 0;
int goal_player2 = 0;

void ball_movement(int paddle1, int paddle2){

 
  pos_x += direction_x;
  pos_y += direction_y;

 
  
  if( pos_x == right_paddle){
    if((pos_y >= paddle2 && pos_y < paddle2 + 8)){
    direction_x = -1;
    direction_y = 1;
    }
  }
  else if ( pos_x > 127){
    pos_x = 64;
    pos_y = 16;
    delay(1500);
    
    goal_player1++;
    
    direction_x = 1;
    direction_y = 0;
  }
  
 if( pos_x == left_paddle){
    if((pos_y >= paddle1 && pos_y < paddle1 + 8)){
    direction_x = 2;
    direction_y = 1;
    }
  }
  else if ( pos_x < 1){
    pos_x = 64;
    pos_y = 16;
    delay(1500);

    goal_player2++;
    direction_x = -1;
    direction_y = 0;
  }
  
  if( pos_y == 32){
    direction_y = -1;
   
  }
  if (pos_y == 0){
  direction_y = 1;
  
}

 Ball(pos_x,pos_y);


}

void win(){

 if(goal_player1 == 3){
   
   goal_player1 = 0;
   goal_player2 = 0;

   display_string(2, "PLAYER 1 WINS!");
   display_update();
   delay(2000);
   display_string(2, "* PLAY AGAIN! *");
   display_update();
   delay(2000);
  
 }

 if(goal_player2 == 3){
   
   goal_player1 = 0;
   goal_player2 = 0;

  
   display_string(2, "PLAYER 2 WINS!");
   display_update();
   delay(2000);
   display_string(2,"* PLAY AGAIN! *");
   display_update();
   delay(2000);
   
 }



}
