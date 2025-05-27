#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct {
    int a;
    int b;
} TaskTypeDef;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

TaskTypeDef taskQueue[256];
int taskCount = 0;


void executeTask(TaskTypeDef *task) 
{
    int result = task->a + task->b;
    printf("Task executed: %d + %d = %d\n", task->a, task->b, result);
    sleep(1); // Simulate some work
}
#define THREAD_POOL_SIZE 20



void submitTask(TaskTypeDef *task) 
{
    pthread_mutex_lock(&mutex);
    if (taskCount < 256) 
    {
        taskQueue[taskCount++] = *task;
    }
     else 
     {
        printf("Task queue is full!\n");
    }
    pthread_mutex_unlock(&mutex);
}



/* 
*/
void *startThread(void *arg) 
{
    while (1) {
        TaskTypeDef task;
        int taskAvailable = 0;

        pthread_mutex_lock(&mutex);

        if (taskCount > 0)
         {
            TaskTypeDef task = taskQueue[0];
            int i;
            for (i = 0; i < taskCount - 1; i++) {
                taskQueue[i] = taskQueue[i + 1]; // Shift tasks
            }
            taskCount--;   
            taskAvailable = 1;
        } 
        pthread_mutex_unlock(&mutex);
        if (taskCount == 0) 
        {
            //sleep 100ms

            usleep(100000); // Sleep for 100 milliseconds if no tasks are available

        }

        if (taskAvailable) 
        {
            executeTask(&task);
        }



    }
    return NULL;
}

int main() 
{
    pthread_t threads[THREAD_POOL_SIZE];
    int i;

    // Initialize the task queue
    TaskTypeDef t1 = {1, 2};


    //create thread pool    
    for (i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&threads[i], NULL, (void *)startThread, NULL);
    }


    // Submit tasks to the queue
    for (i = 0; i < 100; i++) 
    {
        TaskTypeDef task = {i, i + 1};
        submitTask(&task);
    }


    // Wait for threads to finish (they won't in this infinite loop example)
    for (i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

// Test
   //executeTask(&t1);

    // Clean up
    pthread_mutex_destroy(&mutex);
    return 0;
}