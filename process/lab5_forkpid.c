#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
 {
    int id = fork();
      
     printf("Hello world from process id =%d my pid =%d \n",id, getpid());
    
    return 0;
}