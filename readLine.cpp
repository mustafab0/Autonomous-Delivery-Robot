#include "simpletools.h"
#include "readLine.h"



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
    }      
    //return avg;
}  
