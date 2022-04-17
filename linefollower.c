/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools
#include "ping.h"
#include "servo.h"
//#include "ham.h"
;

void lineFollower(void *par);
int measure(void *par);
void look(char *dir);
void scan(void *par);
int constrain(int amt, int low, int high);
void intersectionCounter(void *par);


static volatile int leftFlag,rightFlag, centreFlag, avg, cm_dist,position, intersection;
static volatile int GOAL = 2250;
volatile const double KP = 0.025; //0.04                
volatile const double KD = 0.003;
volatile double lastError = 0;

unsigned int stack1[40+25];
unsigned int stack2[40+25];
unsigned int stack3[40+25];


int main()                                    // Main function
{
    // Add startup code here.
  pause(250);
  
  print("cog 0\n");
  //simpleterm_close();
  int linefollower_cog  = cogstart(lineFollower,NULL,stack1,sizeof(stack1));
  //int cogn1 = cogstart(scan,NULL,stack2,sizeof(stack2));
  int intersectionCounter_cog  = cogstart(intersectionCounter,NULL,stack3,sizeof(stack3));
  
  pause(3000);
  //print("time = %d\n",time[0]);
  print("intersection = %d\n",intersection);
  
    
 }  
  
  
void lineFollower (void *par){
  
  
  //simpleterm_open();
  for (int i =0; i<=5; i++){  
    high(26);
    pause(100);
    low(26);
    pause(100);
  }  
   
  int time[8];
    while(1){
          
     for(int i = 7;i<=14;i++){
        high(i);
        pause(10);
        time[i-7] = rc_time(i,1);
        
        if(time[i-7] >1000) {time[i-7] = 2500;}
        
      } 
      int avg = 0;
      //print("time = %d\n",time[0]);
      if ( time[0] == 2500 && time[1] == 2500 && time[2] == 2500 && time[3] == 2500 && time[4] == 2500 && time[5] == 2500 && time[6] == 2500 && time[7] == 2500){
        
        intersection =1;
        
      }        
            
      for(int i = 0; i<=7;i++){
        avg = avg + i*time[i];
      }
      //print("average sum = %d\n",avg);
      avg = avg/8;
      
      //print("average = %d\n",avg);
      int error_t = GOAL - avg;
      
      int adjustment = KP*error_t + KD*(error_t - lastError);
      //print("Adjustment = %d\n",adjustment);
      //print("constrain left = %d\n",constrain(1520 + adjustment, 1490, 1520));
      //print("constrain right = %d\n",constrain(1460 + adjustment, 1460, 1490));
      lastError = error_t;
 
      servo_set(17,constrain(1520 + adjustment, 1490, 1520));  //Left Motor 
      servo_set(16,constrain(1460 + adjustment, 1460, 1490)); // Right Motor
              
      pause(10);
        
    }      
    
} 

int measure (void *par) // Main function
{
    int cmDist = ping_cm(15); // Get cm distance from Ping)))
    int cm_dist = cmDist;
    print("cmDist = %d\n", cmDist);
    pause(200); // Wait 1/5 second
    //cm_dist = cm_dist+cmDist;
    return cmDist;
}

void look (char *dir)
{  
    int waitTime = 400;

    char k = (char)dir[0];
    print("direction = %c\n", k);
    pause(200);
    switch (k)
    {
    case 'L':
      servo_angle(6, 1600);
      pause(waitTime);
      break;
   
    case 'R':
      servo_angle(6, 100);
      pause(waitTime);
      break;
   
    case 'C':
      servo_angle(6, 800);
      pause(waitTime);
      break;
      default:
      break;
    }
}

void scan(void *par){
  
  char dr;
  //int dr[] = {'L','C','R'};
  
  pause(50);
  //print("direction = %d\n",k);
  //char dr 'L';
  dr = 'L';
  look(&dr);
  //pause(250); 
  //cm_dist;
  for (int n = 0;n<=1;n++){
     cm_dist = measure(NULL);
    }   
  if (cm_dist <60){
      leftFlag = 1;
    }
  dr = 'C';
  look(&dr);
  //pause(250); 
  //cm_dist;
  for (int n = 0;n<=1;n++){
     cm_dist = measure(NULL);
  }   
  if (cm_dist <60){
      centreFlag = 1;
    } 
  dr = 'R';
  look(&dr);
  //pause(250); 
  //cm_dist;
  for (int n = 0;n<=1;n++){
     cm_dist = measure(NULL);
  }   
  if (cm_dist <60){
      rightFlag = 1;
    } 
  print("Left Object = %d, Centre Object = %d, Right Object = %d,\n",leftFlag, centreFlag, rightFlag);
  pause(1000);
  
}  

int constrain(int amt, int low, int high) {
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}  

void intersectionCounter(void *par){
  while(1){
    if(intersection){ 
      //4 green 
      high(4);
      pause(100);
      low(4);
      pause(100);
      //5 red
      high(5);
      pause(100);
      low(5);
      pause(100);
    }  
  }    
}  
