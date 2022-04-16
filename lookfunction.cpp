

#include "simpletools.h"                      // Include simple tools
#include "ping.h"

int measure() // Main function
{
    while(1) // Continuous loop
     {
      int cmDist = ping_cm(6); // Get cm distance from Ping)))
      printf("cmDist = %d\n", cmDist); // Display distance
      pause(200); // Wait 1/5 second
     } 
}

void look(char k){
 
   
   
    switch (k)
    {
    case 'L':
      serv_angle(11, 160);
      break;
   
    case 'R':
      serv_angle(11, 0);
      break;
   
    case 'C':
      serv_angle(11, 80);
      break;
      default:
      break;
    }
}
