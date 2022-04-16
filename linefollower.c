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
//volatile int leftFlag;

//volatile int k; 
static volatile int leftFlag,rightFlag, centreFlag, avg, cm_dist;

//volatile int n;
unsigned int stack1[40+25];
unsigned int stack2[40+25];


int main()                                    // Main function
{
    // Add startup code here.
  pause(250);
  simpleterm_close();
  int cogno  = cogstart(lineFollower,NULL,stack1,sizeof(stack1));
  int cogn1 = cogstart(scan,NULL,stack2,sizeof(stack2));
  
  pause(8000);
  
  //cog_end((int*)cogn1);
  //pause(250);
  simpleterm_open();
  pause(250);
  print("Hi in cog 0 \n");
  print("Left Object = %d, Centre Object = %d, Right Object = %d,\n", leftFlag, centreFlag, rightFlag);
    
 }  
  
  
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

void look (char *dir){  
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
  simpleterm_open(); 
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
  simpleterm_close();
}  


