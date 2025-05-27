// mutex_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define SEM_NAME "/my_mutex"

int main() {
    sem_t *sem = sem_open(SEM_NAME, 0);  // Open existing semaphore
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("[Reader] Waiting for lock...\n");
    sem_wait(sem);  // Lock
    printf("[Reader] Got lock. Reading...\n");

    FILE *f = fopen("/tmp/shared.txt", "r");
    if (f) {
        char buf[128];
        while (fgets(buf, sizeof(buf), f)) {
            printf("[Reader] Read: %s", buf);
        }
        fclose(f);
    } else {
        perror("fopen");
    }

    printf("[Reader] Done. Releasing lock.\n");

    sem_post(sem);  // Unlock
    sem_close(sem);

    return 0;
}
