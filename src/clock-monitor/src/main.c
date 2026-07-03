 #include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>

 #include "clock_monitor.h"
 
 #define NUM_WORKERS 10
 #define MAX_SLEEP 10

  /* Checks the return value of pthread operations and terminates the program on failure. */
 static void checkPthreadError(int result, const char *operation){

    if (result != 0) {

        fprintf(stderr, "%s failed\n", operation);
        exit(EXIT_FAILURE);

    }

 }

 /* Function executed by each worker thread */
 void *worker(void *arg){

    int id = *(int *)arg;   // Retrieve thread ID

    registerThread(id);   // Register the thread in the monitor

    int sleepTime = (rand() % MAX_SLEEP) + 1;   // Random sleep duration in ticks

    printf("Worker %d: needs to sleep %d ticks \n", id, sleepTime);

    while(1){

        /* Sleep for the generated number of ticks */
        sleepTicks(sleepTime);

        /* Simulate some work before going to sleep again */
        printf("Worker %d: doing some work before next sleep \n", id);

    }

    return (NULL);

 }
 
 int main(void) {
    
    pthread_t workers[NUM_WORKERS];   // Array of worker threads
    pthread_t clockThread;   // Thread for the ticking clock

    int ids[NUM_WORKERS];   // IDs for each worker thread

    initClockMonitor();   // Initialize the monitor

    srand(time(NULL));   // Seed the random number generator

    /* Create worker threads */
    for(int i = 0; i < NUM_WORKERS; i++){
        
        ids[i] = i;

        checkPthreadError(pthread_create(&workers[i], NULL, worker, &ids[i]), "pthread_create");

    }

    /* Create the clock thread */
    checkPthreadError(pthread_create(&clockThread, NULL, tick, NULL), "pthread_create");

    /* Wait for all worker threads to finish (this won't happen in infinite loop) */
    for(int i = 0; i < NUM_WORKERS; i++){

        checkPthreadError(pthread_join(workers[i], NULL), "pthread_join");

    }

    printf("All worker threads have finished.\n");

    destroyClockMonitor();   // Clean up resources

    return 0;

 }