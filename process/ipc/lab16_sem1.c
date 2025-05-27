// mutex_writer.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define SEM_NAME "/my_mutex"

int main() 
{


      // Lock
    
    printf("[Writer] Got lock. Writing...\n");

    FILE *f = fopen("/tmp/shared.txt", "a");
    if (f) {
        fprintf(f, "Writer: wrote something.\n");
        fclose(f);
    } else {
        perror("fopen");
    }

    sleep(2);  // Simulate long operation
    printf("[Writer] Done. Releasing lock.\n");

    
    return 0;
}
