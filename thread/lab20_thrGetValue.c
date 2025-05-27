#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* thread_function(void* arg) 
{
    // Allocate memory on the heap to store the integer value.
    // This memory will persist after the thread finishes, allowing
    // the main thread to retrieve the value.
    int* num = malloc(sizeof(int));
    if (num == NULL) {
        perror("malloc failed in thread_function");
        return NULL;; // Return NULL to indicate an error
    }
    *num = 42; // Example value to return

    // Return the pointer to the allocated memory.
    // The pthread_join function will receive this pointer.
    return (void*)num;
}

int main() 
{
    pthread_t thread;         // Declare a thread identifier.
    void* return_value;       // Declare a pointer to hold the thread's return value.

    // Create the thread.
    // pthread_create(thread_id, attributes, start_routine, arg)
    // - &thread:           Pointer to the thread identifier.
    // - NULL:              Default thread attributes.
    // - thread_function:   The function that the new thread will execute.
    // - NULL:              Argument to pass to the thread_function (none in this case).
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("pthread_create failed");
        return 1; // Indicate an error
    }

    // Wait for the thread to finish and retrieve its return value.
    // pthread_join(thread_id, return_value_ptr)
    // - thread:            The identifier of the thread to wait for.
    // - &return_value:     Pointer to a void* where the thread's return value will be stored.



    return 0; // Indicate successful execution
}