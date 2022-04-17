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
void turn(char *dir);
void look(char *dir);
void scan(void *par);
int constrain(int amt, int low, int high);
void intersectionCounter(void *par);
void stop();


static volatile int leftFlag,rightFlag, centreFlag, avg, cm_dist,position, intersection, intersectionCount, direction;



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
  //char dir="L";
  
  print("cog 0\n");
  //simpleterm_close();
  int linefollower_cog  = cogstart(lineFollower,NULL,stack1,sizeof(stack1));
  int intersectionCounter_cog  = cogstart(intersectionCounter,NULL,stack3,sizeof(stack3));
  int scan_cog = cogstart(scan,NULL,stack2,sizeof(stack2));
  
  
  pause(3000);
  //print("time = %d\n",time[0]);
  while(1){
  print("intersection = %d\n",intersection);
  //dir="L";
//  print("direction = %c\n", k);
  pause(2000);
  
  }  
    
 }  
  
  
void lineFollower (void *par){
  
  
  //simpleterm_open();
  
   
  int time[8];
    while(1){
      
      for (int i =0; i<=5; i++){  
        high(26);
        pause(100);
        low(26);
        pause(100);
      }   
          
     for(int i = 7;i<=14;i++){
        high(i);
        pause(10);
        time[i-7] = rc_time(i,1);
        
        if(time[i-7] >1000) {time[i-7] = 2500;}
        
      } 
      int avg = 0;
      //print("time = %d\n",time[0]);
      if ( time[0] == 2500 && time[1] == 2500 && time[2] == 2500 && time[3] == 2500 && time[4] == 2500 && time[5] == 2500 && time[6] == 2500 && time[7] == 2500){
        
        intersection=1;
      }
      else{
        intersection=0;
      }          
      
      //int intCounter=intersectionCounter;
      if(intersectionCount==1){
        
        
        /// compute adjustment and set servo speed
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
        ///////
        
        } 
       else if(intersectionCount==2){
         int obs_dist=measure();
         
             if(obs_dist<35){
                high(0);
                pause(100);
                low(0);
                pause(100);
             }   
             else if(obs_dist<65) {
                high(1);
                pause(100);
                low(1);
                pause(100);
             }    
             else{
                high(1);
                pause(100);
                low(1);
                pause(100);
             }       
             
              
              
              
              turn("L");
              
              /// compute adjustment and set servo speed
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
              ///////   
                           
       }
       else if(intersectionCount==3||6||8||11){ 
        turn("R");
        
        
              /// compute adjustment and set servo speed
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
              ///////   
       }  
       else if(intersectionCount==13){
         turn("R");
         
         /// compute adjustment and set servo speed
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
          /////// 
       }
      else{
        while(1){
          high(26);
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

void scan(void *par)
{  
  while(1){
    int waitTime = 400;

    //char k = (char)dir[0];
    char k ='L';
    print("direction = %c\n", k);
    //pause(200);
    
    switch (k)
    {
    case 'L':
      servo_angle(6, 1600);
      pause(400);
      break;
   
    case 'R':
      servo_angle(6, 100);
      pause(400);
      break;
   
    case 'C':
      servo_angle(6, 800);
      pause(400);
      break;
      default:
      break;
    }
    
    int cm_dist = measure();
    if(cm_dist<11){
      high(2);
      pause(100);
      low(2);
      pause(100);
      //5 red
      high(3);
      pause(100);
      low(3);
      pause(100);
    }    
  }    
}
/*
void measure(char *dir){
  
  
  
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
*/

int constrain(int amt, int low, int high) {
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}  

void intersectionCounter(void *par){
  while(1){
    if(intersection==1){ 
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

void turn(char *dirn){
  
   char f = (char)dirn[0];

   
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