#include "simpletools.h"
#include "ham.h"
#include "ping.h"


void lineFollower(void *par){

  int time[8];
    while(1){
      
      simpleterm_open();
      pause(250);
      print("In cog1 = \n");
      for(int i = 8;i<=15;i++){
        high(i);
        pause(10);
        time[i-8] = rc_time(i,1);
        
        if(time[i-8] >1000) {time[i-8] = 2500;}
        
        print("value for pin %d: %d\n",i,time[i-8]);
        //time = 0;
      } 
      int avg = 0;
      for(int i = 0; i<=7;i++){
        avg = avg + i*time[i];
      }
      print("average sum = %d\n",avg);
      avg = avg/8;
      print("weighted average = %d\n",avg);
      
      
      simpleterm_close();
      pause(2000);
    }      
    //return avg;
}  

void measure(void *par) // Main function
{
    while(1) // Continuous loop
     {
      int cmDist = ping_cm(6); // Get cm distance from Ping)))
      printf("cmDist = %d\n", cmDist); // Display distance
      pause(200); // Wait 1/5 second
     } 
}

void look(void *dir){  

    pause(50); 
    char k = (char)((size_t)dir);
   
    switch (k)
    {
    case 'L':
      servo_angle(11, 160);
      break;
   
    case 'R':
      servo_angle(11, 0);
      break;
   
    case 'C':
      servo_angle(11, 80);
      break;
      default:
      break;
    }
}
