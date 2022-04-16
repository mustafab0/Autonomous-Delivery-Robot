/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools
#include "ham.h"
;

volatile int avg;
volatile int cm_dist;


//volatile int n;
unsigned int stack1[40+25];
unsigned int stack2[40+25];

void printFun(void* par1);
int main()                                    // Main function
{
    // Add startup code here.
  pause(250);
 
  simpleterm_close();
  //int cogn1= cogstart(printFun,NULL,stack2,sizeof(stack2));
  int cogno= cogstart(lineFollower,NULL,stack1,sizeof(stack1));
  
  
  while(1){
  pause(5000);
  simpleterm_open();
  pause(250);
  print("In cog0\n");
  simpleterm_close();
  
  }  
/*
   while(1){
   simpleterm_open();
   pause(250);
   print("In cog0\n");
   pause(250);
   print("cogno running %d\n",cogno);
   simpleterm_close();
 }   
    */
}

/*
1=350
2=650
3=1200
4=3000
5=3000
6=3000
7=3600
8=4000
*/