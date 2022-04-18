   
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
int measure();
void turn(char dirn);
void look(char *dir);
void scan(void *par);
int constrain(int amt, int low, int high);
void intersectionCounter(void *par);
void stop();
void streetCounter(void *par);


static volatile int objectDetected,rightFlag, avg, cm_dist,position, intersection, intersectionCount, direction, UpOrDown, A, B;
static volatile int centerFlag = 1;
static volatile int streetNo = -1;



static volatile int GOAL = 2250;
volatile const double KP = 0.025; //0.04               
volatile const double KD = 0.003;
volatile double lastError = 0;

unsigned int stack1[40+25];
unsigned int stack2[40+25];
unsigned int stack3[40+25];


int main()                                    // Main function
{
  simpleterm_close();
  int linefollower_cog  = cogstart(lineFollower,NULL,stack1,sizeof(stack1));
  pause(15000);
  int intersectionCounter_cog  = cogstart(streetCounter,NULL,stack3,sizeof(stack3));
  //int scan_cog = cogstart(scan,NULL,stack2,sizeof(stack2));
  pause(2000);
  int scan_cog = cogstart(scan,NULL,stack2,sizeof(stack2)); 
    
 }  
  
  
void lineFollower (void *par){
  
  
  simpleterm_open();
  
  print("hello\n");
  for (int i =0; i<=5; i++){  
        high(26);
        pause(100);
        low(26);
        pause(100);
      } 
  
  UpOrDown=1;
  int objectDetectedNo = 0; 
  int turnedRight, turnedLeft;
  int time[8];
    while(objectDetectedNo<2){
     //print("streetno = %d\n",intersection);        
     for(int i = 7;i<=14;i++){
        high(i);
        pause(10);
        time[i-7] = rc_time(i,1);
        
        if(time[i-7] >1000) {time[i-7] = 2500;}
        
      } 
      int avg = 0;
      
      for(int i = 0; i<=7;i++){
          avg = avg + i*time[i];
        }
        //print("average sum = %d",avg);
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
      
      //print("time = %d\n",time[0]);
      if ( time[0] == 2500 && time[1] == 2500 && time[2] == 2500 && time[3] == 2500 && time[4] == 2500 && time[5] == 2500 && time[6] == 2500 && time[7] == 2500){
        
        intersection=1;
        servo_set(17,1520);
        servo_set(16,1460);
      }
      else{
        intersection = 0;
      }        
      
      if(centerFlag==1 && objectDetected){
        if(streetNo%2==0){
          //print("does this print\n");
          turn('R');
          UpOrDown=!UpOrDown;
          centerFlag = 0;
          A = 1;
        }
        else if(streetNo%2 == 1 && centerFlag == 1){
        turn('L');
        UpOrDown=!UpOrDown;
        centerFlag = 0;
        B =1;
        }                 
      }
      else if((A==1||B==1) &&  objectDetected){
        objectDetectedNo=objectDetectedNo+1;
      } 
      else if(A==1 && streetNo ==1){
            turn('R');
            UpOrDown=!UpOrDown;
            A == 0;
      }        
        
      else if (streetNo == 4 && B == 1 ) {
          turn('R');
          UpOrDown=!UpOrDown;
          B==0;
      } 
      else if ((A == 1 || B== 1) && intersection == 1 && UpOrDown == 0){
         turn('R');
         UpOrDown=!UpOrDown;
      }                        
    }      
} 

int measure () // Main function
{
    int cmDist = ping_cm(15); // Get cm distance from Ping)))
    int cm_dist = cmDist;
    //print("cmDist = %d\n", cmDist);
    pause(200); // Wait 1/5 second
    //cm_dist = cm_dist+cmDist;
    return cmDist;
}


void scan(void *par){
  //simpleterm_open();
  //print("hello in scan\n");
  while(1){
    if(centerFlag){
      servo_angle(6,700);
    }
    else if(A==1||B==1){
      servo_angle(6,1700);
    } 
    else{
      servo_angle(6,700);
    }   
    int cm_dist = measure();    
    if(centerFlag==1){
      if(cm_dist<30){
         //4 green 
          objectDetected =1;
          high(3);
          pause(100);
          low(3);
          pause(100);
          //5 red
          high(2);
          pause(100);
          low(2);
          pause(100); 
     }   
     else { objectDetected = 0;}  
    }
    else{
       if(cm_dist<11){
          //4 green 
          objectDetected =1;
          high(3);
          pause(100);
          low(3);
          pause(100);
          //5 red
          high(2);
          pause(100);
          low(2);
          pause(100); 
      }   
      else { objectDetected = 0;}         
    }          
  }  
}


int constrain(int amt, int low, int high) {
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}  

void intersectionCounter(void *par){
  while(1){
    if(intersection==1){ 
      intersection=0;
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
      intersectionCount=intersectionCount+1;
      pause(1);
      intersection=0;
    }  
  }    
}  

void stop(){
  servo_speed(17, 0);         // stop
  pause(20);
  servo_speed(16, 0);         // stop
  pause(20);
}

void streetCounter(void *par){
  for (int i =0; i<=5; i++){  
        high(27);
        pause(100);
        low(27);
        pause(100);
      } 
  while(1){
    if(intersection==1){
      if(UpOrDown){
        if(A==1){
          streetNo=streetNo-1;
          
        }
        else{
          streetNo=streetNo+1;
         
        }
           
        } 
        intersection=0; 
        for(int blink = 0; blink<5;blink++)  {
          high(5); high(4);
          pause(200);
          low(5);low(4);                     
      }      
    }    
  }  
}

void turn(char dirn){
  
   char f = dirn;

   
   switch(f){
    case 'L':
    for(int i = 0; i<30;i++){
       //servoLeft.writeMicroseconds(1300);
       servo_speed(17, -100);         
   // 1.3 ms full speed anti clockwise
       //servoRight.writeMicroseconds(1300);    
       servo_speed(16, -100);     
   // 1.3 ms full speed anti clockwise
       pause(20);
    }
    stop();
    break;
    case 'R': 
    for(int i = 0; i<30;i++){  
       //servoLeft.writeMicroseconds(1700);
       servo_speed(17, 100);           
  // 1.3 ms full speed anti clockwise
       //servoRight.writeMicroseconds(1700);
       servo_speed(16, 100);          
  // 1.3 ms full speed anti clockwise
       pause(20);
      }
      stop();
      break;
     default:
     for(int i=0;i<75;i++){
      //servoLeft.writeMicroseconds(1700);  
      servo_speed(17, 100);       
  // 1.3 ms full speed anti clockwise
      //servoRight.writeMicroseconds(1700);
      servo_speed(16, -100);       
   // 1.3 ms full speed anti clockwise
      pause(20);
      }
      stop();
   }
   
}
