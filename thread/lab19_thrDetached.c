/* LAB19 : Thread Detached */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>


void * myThread(void * args)
{

  char * str = (char *) args;
  sleep(1); // Sleep for 1 second to simulate work
  printf("%s", str);

  return NULL;
}

int main(int argc, char * argv[]){

  char hello[] = "Hello World!\n";

  pthread_t thread;  //thread identifier

  
  return 0;
}