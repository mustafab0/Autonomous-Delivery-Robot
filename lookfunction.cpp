

#include "simpletools.h"                      // Include simple tools
#include "ping.h"
int main() // Main function
{
    while(1) // Continuous loop
     {
      int cmDist = ping_cm(6); // Get cm distance from Ping)))
      printf("cmDist = %d\n", cmDist); // Display distance
      pause(200); // Wait 1/5 second
     } 
}
