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

