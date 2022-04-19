/**
* This is the main Blank Simple C++ Project program file.
*/

#include <stdio.h>            // Recommended over iostream for saving space
#include <propeller.h>        // Propeller-specific functions

#include "simpletools.h"                      // Include simple tools
#include "ping.h"
#include "servo.h"
//#include "ham.h"
;

void lineFollower(void *par);
int measure();
void turn(char *dir);
void look(char *dir);
void scan(void *par);
int constrain(int amt, int low, int high);
void streetCounter(void *par);
void stop();


static volatile int leftFlag,rightFlag, centerFlag, avg, cm_dist,position, intersection, streetNo, UpOrDown, A, B;


static volatile int GOAL = 2250;
volatile const double KP = 0.025; //0.04                
volatile const double KD = 0.003;
volatile double lastError = 0;

unsigned int stack1[40+25];
unsigned int stack2[40+25];
unsigned int stack3[40+25];

int main(){
  // Add your code here
  
  int linefollower_cog  = cogstart(lineFollower,NULL,stack1,sizeof(stack1));
  pause(10000);
  int intersectionCounter_cog  = cogstart(streetCounter,NULL,stack3,sizeof(stack3));
  //int scan_cog = cogstart(scan,NULL,stack2,sizeof(stack2));
  if(streetNo==1){
    int scan_cog = cogstart(scan,NULL,stack2,sizeof(stack2));
  }  
  return 0;
}

void lineFollower (void *par){
  for (int i=0; i<=5; i++){  
    high(26);
    pause(100);
    low(26);
    pause(100);
  }  
  UpOrDown=1;
  int objectDetectedNo = 0;
  while(objectDetectedNo){
    
    ///----------------------line detection and get position--------------------------
    for(int i = 7;i<=14;i++){
      high(i);
      pause(10);
      time[i-7] = rc_time(i,1);
      
      if(time[i-7] >1000) {time[i-7] = 2500;}
      
    } 
    int avg = 0;         
    
  
      
    /// compute adjustment and set servo speed
    for(int i = 0; i<=7;i++){
      avg = avg + i*time[i];
    }
    //print("average sum = %d\n",avg);
    avg = avg/8;
    //-------------------------------------------------------------------------
    
    
    //-------------------------------PID Control------------------------------
    //print("average = %d\n",avg);
    int error_t = GOAL - avg;
    
    int adjustment = KP*error_t + KD*(error_t - lastError);
    //print("Adjustment = %d\n",adjustment);
    //print("constrain left = %d\n",constrain(1520 + adjustment, 1490, 1520));
    //print("constrain right = %d\n",constrain(1460 + adjustment, 1460, 1490));
    lastError = error_t;
    //-------------------------------------------------------------------------
    
    
    //------------------------------Follow the line-------------------------------
    servo_set(17,constrain(1520 + adjustment, 1490, 1520));  //Left Motor 
    servo_set(16,constrain(1460 + adjustment, 1460, 1490)); // Right Motor
            
    pause(10);
    //-----------------------------------------------------------------------------
    
    //------------------------------Detect intersection----------------------------------
    if ( time[0] == 2500 && time[1] == 2500 && time[2] == 2500 && time[3] == 2500 && time[4] == 2500 && time[5] == 2500 && time[6] == 2500 && time[7] == 2500){
      
      intersection=1;
    }
    else{
      intersection=0;
    } 
    //-----------------------------------------------------------------------------------
    pause(100)
    if(centerFlag==1 && objectDetected){
      if(streetNo%2==0){
        turn('R')
        UpOrDown=!UpOrDown;
        A=1;
      }
      else(){
        turn('L');
        UpOrDown=!UpOrDown;
        B=1;
      }                 
    }
    else if((A==1||B==1) &&  objectDetected){
      objectDetected=objectDetected+1;
    } 
    else(A==1||B==1){
      if(streetNo == 1){ //might be wrong
          A=0
          B=1
          turn('R');
          UpOrDown=!UpOrDown
        }        
      }
      else(){
        B=0
        A=1
        turn('R');
        UpOrDown=!UpOrDown;
        
      }      
            
    }           
  
}

void scan(void *par){
  while(1){
    if(centerFlag){
      servo_angle(6,800)
    }
    else if(A==1||B==1){
      servo_angle(6,100)
    } 
    else{
      servo_angle(6,800)
    }   
    int cm_dist = measure();    
    if(centerFlag==1){
      if(cm_dist<35){
         //4 green 
          high(2);
          pause(100);
          low(3);
          pause(100);
          //5 red
          high(2);
          pause(100);
          low(3);
          pause(100); 
     }      
    }
    else{
       if(cm_dist<11){
          //4 green 
          high(2);
          pause(100);
          low(3);
          pause(100);
          //5 red
          high(2);
          pause(100);
          low(3);
          pause(100); 
      }           
    }          
  }  
}

void streetCounter(void *par){
  while(1){
    if(intersection==1){
      if(UpOrDown){
        if(A==1){
          streetNo=streetNo-1;
        }
        else(){
          streetNo=street+1;
        }
        intersection=0;                
      }      
    }    
  }  
}

int measure () // Main function
{
    int cmDist = ping_cm(15); // Get cm distance from Ping)))
    int cm_dist = cmDist;
    print("cmDist = %d\n", cmDist);
    pause(200); // Wait 1/5 second
    //cm_dist = cm_dist+cmDist;
    return cmDist;
}