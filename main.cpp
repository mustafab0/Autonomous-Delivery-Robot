

#include "simpletools.h"                      // Include simple tools
#include "servo.h"                            // Include servo library

void lineFollower();
int constrain(int amt, int low, int high);
void look(char k);

int GOAL = 3000;
const double KP = 0.035; //0.04                
const double KD = 0.03;
volatile int position;
volatile double lastError = 0;

// Global vars for cogs to share
unsigned int stack1[40 + 25]; // Stack vars for cog1


int main()                                    // Main function
{
  position=3000;
  pause(1000); // 1 s delay
/*  
  for(int n = 0; n <= 50; n+=1){

  lineFollower();
 
}  
*/
cogstart(lineFollower, NULL, stack1, sizeof(stack1));
}


void lineFollower(){

  //printf(OUTA1=%n\n",position);
  int error = GOAL - position;		
  //We check difference between goal and current position
  //printf("error= ");
  //printf(error);
 
  // Compute motor adjustment
  int adjustment = KP*error + KD*(error - lastError); //PID tuning
 
  // Store error for next increment
  lastError = error;
  //printf("adjustment= ");
  //printf(adjustment);
  //printf('\t');
  //delay(250);
  
  
  // servoLeft.writeMicroseconds(constrain(1550 + adjustment, 1490, 1550)); 
  servo_speed(17,constrain(100 + adjustment, 75, 100));        
  // servoRight.writeMicroseconds(constrain(1420 + adjustment, 1420, 1490));        // We make slight adjustments based on the KP and KD we calculated
  servo_speed(16,constrain(100 + adjustment, 75, 100));        
  pause(1);
}

int constrain(int amt, int low, int high) {
  ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}  


void look(char k){
 
   
   
    switch (k)
    {
    case 'L':
      serv_angle(11, 160);
      break;
   
    case 'R':
      serv_angle(11, 0);
      break;
   
    case 'C':
      serv_angle(11, 80);
      break;
      default:
      break;
    }
 }


/*
1=350
2=650
3=1200
4=3000
5=3000
6=3000
7=3600
8=4000
*/