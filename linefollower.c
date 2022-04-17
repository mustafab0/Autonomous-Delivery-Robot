/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools
#include "ham.h"
;

volatile int avg, cm_dist;
//volatile int k; 


void findObject(void *par);

//volatile int n;
unsigned int stack1[40+25];
unsigned int stack2[40+25];

void printFun(void* par1);
int main()                                    // Main function
{
    // Add startup code here.
  pause(250);
  simpleterm_close();
  int cogno  = cogstart(lineFollower,NULL,stack1,sizeof(stack1));
  int congn1 = cogstart(findObject,NULL,stack2,sizeof(stack2));
  
  pause(250);
  
  
  
  
  }  

void findObject(void *par){
  int dr[] = {'L'};
  simpleterm_open(); 
  pause(50);
  //print("direction = %d\n",k);
  //char dr = 'L';
  while(1){
    //look(&dr);
    high(26);
    pause(250);
    low(26);
    look((char *)dr);
    //for(v=0,v<50,v++){
    //  turn((char *)dr);
    //}    
    
    //pause(250); 
    cm_dist = 0;
    for (int n = 0;n<=1;n++){
       measure(NULL);
      
    }       
     //cm_dist = cm_dist/10;
     //print("cmDist = %d\n", cm_dist); // Display distance
     //simpleterm_close();
        
  }    
  
}  