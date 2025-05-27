#include <stdio.h>
#include <unistd.h>
#include <signal.h>



int main()
{
 

  while(1) 
  {
      printf("Waiting for interruption...\n");
      sleep(1);
  }
}