#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>





int main() 
{


    int *ptr = (int*)0x400; //invalid address
    *ptr = 123;  // Will cause SIGSEGV

    return 0;
}
