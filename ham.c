#include "simpletools.h"
#include "servo.h"
#include "ping.h"
#include "ham.h"

;


void lineFollower (void *par){

  int time[8];
    while(1){
      
      /*simpleterm_open();
      pause(250);
      print("In cog1 = \n");
      simpleterm_close();
      pause(2000);
      */
      for(int i = 7;i<=14;i++){
        high(i);
        pause(10);
        time[i-8] = rc_time(i,1);
        
        if(time[i-8] >1000) {time[i-8] = 2500;}
        
        //print("value for pin %d: %d\n",i,time[i-8]);
        //time = 0;
      } 
      int avg = 0;
      for(int i = 0; i<=7;i++){
        avg = avg + i*time[i];
      }
      //print("average sum = %d\n",avg);
      avg = avg/8;
      
      //printf(OUTA1=%n\n",position);
      int error = GOAL - avg;		
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
    
} 

void measure (void *par) // Main function
{
    int cmDist = ping_cm(6); // Get cm distance from Ping)))
    int cm_dist = cmDist;
    print("cmDist = %d\n", cmDist);
    pause(200); // Wait 1/5 second
    //cm_dist = cm_dist+cmDist;
    
}

void look (char *dir){  


    char k = (char)dir[0];
    print("direction = %c\n", k);
    pause(200);
    switch (k)
    {
    case 'L':
      servo_angle(15, 1600);
      pause(1000);
      break;
   
    case 'R':
      servo_angle(15, 100);
      pause(1000);
      break;
   
    case 'C':
      servo_angle(15, 800);
      pause(1000);
      break;
      default:
      break;
    }
}

void turn(char *dirn){
  
   char f = (char)dirn[0];
   
   switch(f){
    case 'L':
    for(int i = 0; i<40;i++){
       //servoLeft.writeMicroseconds(1300);
       servo_speed(17, 100);         
   // 1.3 ms full speed anti clockwise
       //servoRight.writeMicroseconds(1300);    
       servo_speed(16, -100);     
   // 1.3 ms full speed anti clockwise
       delay(20);
    }
    stop();
    break;
    case 'R':
    for(int i = 0; i<40;i++){  
       //servoLeft.writeMicroseconds(1700);
       servo_speed(17, 100);           
  // 1.3 ms full speed anti clockwise
       //servoRight.writeMicroseconds(1700);
       servo_speed(16, -100);          
  // 1.3 ms full speed anti clockwise
       delay(20);
      }
      stop();
      break;
     default:
     for(int i=0;i<75;i++){
      //servoLeft.writeMicroseconds(1700);  
      servo_speed(17, 100);       
  // 1.3 ms full speed anti clockwise
      //servoRight.writeMicroseconds(1700);
      servo_speed(16, 100);       
   // 1.3 ms full speed anti clockwise
      delay(20);
      }
      stop();
   }
   
}


int constrain(int amt, int low, int high) {
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}  