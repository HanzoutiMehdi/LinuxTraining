#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    
   // create pipe       
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }
    
    int id = fork();
    int n;
     
   // Check if fork() failed
    if (id < 0) {
        perror("Fork failed");
        exit(1);
    }
   
    if (id == 0)
     { 
        // Child process
        close(fd[0]); // Close unused read end
        
        for (int i = 0; i < 5; i++) {
            n = i + 1;
            write(fd[1], &n, sizeof(n)); // Write to pipe
            printf("** Child process %d wrote %d to pipe\n", getpid(), n);
        }
        close(fd[1]); // Close write end
        exit(0);
    }
    else
     { // Parent process
        close(fd[1]); // Close unused write end
        wait(NULL); // Wait for child process to finish
    #if 0 
        for (int i = 0; i < 7; i++) {
            read(fd[0], &n, sizeof(n)); // Read from pipe
            printf(" ---- > Parent process %d read %d from pipe\n", getpid(), n);
        }
     #endif  
#if 1
        // Read remaining data from the pipe    
        while (read(fd[0], &n, sizeof(n)) > 0)
         {
            printf(" ---- > Parent process %d read %d from pipe\n", getpid(), n);
        }

#endif 

        close(fd[0]); // Close read end
    }

    return 0;
}