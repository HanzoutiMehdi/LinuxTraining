#include <stdio.h>
#include <fcntl.h>


void delay() {
    for (volatile long i = 0; i < 10000000; ++i);  // Keeps CPU busy
}

//add process function to take time 
// to simulate a long-running operation
void process() {
    for (volatile long i = 0; i < 100000000; ++i)
    {
        // Simulate some processing work
        if (i % 10000000 == 0) {
            // Optionally print progress or do something
             printf("Processing: %ld\n", i);
             delay();  // Introduce a delay to simulate a long-running operation
        }

    }
    
    // Keeps CPU busy
}


int main() 

{
    int fd = open("nonexistent.txt", O_RDONLY);
 
    delay();  // Introduce a delay to simulate a long-running operation
    
    if (fd == -1)
     {
        perror("open failed");
        //fprintf(stderr, "Open failed\n"); // stderr (fd 2)
         //write(2, "open failed"\n", 13);  // FD 2 = stderr


    }
    
    process();  // Call the process function to simulate a long-running operation
    
    printf("This message will not be printed \n");// stdout (fd 1)
    //write(1, "Hello stdout\n", 13);  // FD 1 = stdout

    return 0;
}


