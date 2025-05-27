#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME  "/myqueue1"
#define MAX_SIZE    1024
int main()
 {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];

    // Set queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Open the queue for writing
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);

    if (mq == -1) 
    {
        perror("mq_open");
        exit(1);
    }

    // Prepare the message
    snprintf(buffer, sizeof(buffer), "Hello, this is a message from process %d", getpid());


    //mq_timedsend(mq, buffer, strlen(buffer) + 1, 0, NULL);

    // Send message
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) 
    {
        perror("mq_send");
        exit(1);
    }

    printf("Message sent: %s\n", buffer);
    mq_close(mq);

    return 0;
}
