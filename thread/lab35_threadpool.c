#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct {
     void (*function)(void *);
} TaskTypeDef;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

TaskTypeDef taskQueue[256];
int taskCount = 0;


void userFunction(void *arg) 
{
     int a =rand() % 100;
     int b =rand() % 100;
    int result = a + b;
   int prod =   a * b;
    printf("Task Somme : %d + %d = %d Prod = %d\n", a, b, result,prod);
    usleep(50000); // Simulate some work

}


void executeTask(TaskTypeDef *task) 
{
     if (task->function != NULL) 
     {
      task->function(NULL); // Call the user function
      usleep(50000); // Simulate some work
     }
}



void submitTask(TaskTypeDef *task) 
{

}



/* 
*/
void *startThread(void *arg) 
{
    while (1) 
    {

        
    }
    return NULL;
}

#define THREAD_POOL_SIZE 2
int main() 
{
    pthread_t threads[THREAD_POOL_SIZE];
    int i;

    //create thread pool    
    for (i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&threads[i], NULL, (void *)startThread, NULL);
    }

     printf ("Thread pool created with %d threads.\n", THREAD_POOL_SIZE);

    // Submit tasks to the queue
    for (i = 0; i < 100; i++) 
    {
        TaskTypeDef task = {.function=&userFunction};
        submitTask(&task);
    }


    // Wait for threads to finish (they won't in this infinite loop example)
    for (i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }


    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}