/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools
#include "readLine.h"

//volatile int avg;


//volatile int n;
unsigned int stack1[40+25];
unsigned int stack2[40+25];

void printFun(void* par1);
int main()                                    // Main function
{
  simpleterm_close();
  // Add startup code here.
  pause(250);
  simpleterm_open();
  print("In cog0");
  simpleterm_close();
  
  
  //simpleterm_close();
  //int cogn1= cogstart(printFun,NULL,stack2,sizeof(stack2));
  int cogno= cogstart(readPosition,NULL,stack1,sizeof(stack1));
  
  
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
void printFun(void* par){
  while(1){
    pause(250);
  simpleterm_open();
  print("In cog0");
  simpleterm_close();
}  
}  