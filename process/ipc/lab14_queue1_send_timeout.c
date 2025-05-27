#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

#define QUEUE_NAME  "/myqueue"
#define MAX_SIZE    1024

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char message[MAX_SIZE] = "Hello with timeout!";

    // Set queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Open the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    // Create a 500ms timeout
    struct timespec timeout;
    if (clock_gettime(CLOCK_REALTIME, &timeout) == -1) {
        perror("clock_gettime");
        exit(1);
    }

    // Add 500 milliseconds
    timeout.tv_nsec += 500 * 1000000; // 500ms in nanoseconds

    // Normalize if needed
    if (timeout.tv_nsec >= 1000000000) {
        timeout.tv_sec += timeout.tv_nsec / 1000000000;
        timeout.tv_nsec %= 1000000000;
    }

    // Send with timeout
    if (mq_timedsend(mq, message, strlen(message) + 1, 0, &timeout) == -1) {
        if (errno == ETIMEDOUT) {
            fprintf(stderr, "mq_timedsend: timed out\n");
        } else {
            perror("mq_timedsend");
        }
        exit(1);
    }

    printf("Message sent with 500ms timeout: %s\n", message);

    mq_close(mq);
    return 0;
}
