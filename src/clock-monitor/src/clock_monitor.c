 #include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>

 #include "clock_monitor.h"

 #define MAX_THREADS 100

 /* Global variable to track the number of clock ticks */
 static int clockTick = 0;

 /* Mutex for synchronizing access to shared resources */
 static pthread_mutex_t mutex;
 /* One condition variable per thread */
 static pthread_cond_t cond[MAX_THREADS];

 /* Array holding the target tick each thread is waiting for */
 static int waitingTicks[MAX_THREADS];

 /* Mapping from internal thread IDs to pthread_t */
 static pthread_t threadIds[MAX_THREADS];

 /* Checks the return value of pthread operations and terminates the program on failure. */
 static void checkPthreadError(int result, const char *operation){

    if (result != 0) {

        fprintf(stderr, "%s failed\n", operation);
        exit(EXIT_FAILURE);

    }

 }

 /* Initializes the monitor (mutex, condition variables, waiting array) */
 void initClockMonitor(void){

    checkPthreadError(pthread_mutex_init(&mutex, NULL), "pthread_mutex_init");

    for(int i = 0; i < MAX_THREADS; i++){

        checkPthreadError(pthread_cond_init(&cond[i], NULL), "pthread_cond_init");

        waitingTicks[i] = -1;   // -1 means the thread is not waiting
       
    }

 }

 /* Destroys the monitor's synchronization primitives */
 void destroyClockMonitor(void){

    checkPthreadError(pthread_mutex_destroy(&mutex), "pthread_mutex_destroy");

    for(int i = 0; i < MAX_THREADS; i++){

        checkPthreadError(pthread_cond_destroy(&cond[i]), "pthread_cond_destroy");

    }

 }

 /* Returns the internal thread ID corresponding to the calling pthread_t */
 int getThreadId(void){

    pthread_t self = pthread_self();

    for(int i = 0; i < MAX_THREADS; i++){

        if(pthread_equal(threadIds[i], self)){

            return i;

        }

    }

    return (-1);   // Not found

 }

 /* Registers the calling thread by associating its pthread_t with an internal ID */
 void registerThread(int id){

    checkPthreadError(pthread_mutex_lock(&mutex), "pthread_mutex_lock");

    threadIds[id] = pthread_self();

    checkPthreadError(pthread_mutex_unlock(&mutex), "pthread_mutex_unlock");

 }

 /* Function that simulates a ticking clock, running in its own thread */
 void *tick(void *arg){

    (void)arg;

    while(1){
        
        checkPthreadError(pthread_mutex_lock(&mutex), "pthread_mutex_lock");
        
        clockTick++;   // Increment global clock tick

        printf("Clock tick: %d \n", clockTick);

        /* Check which threads need to be woken up */
        for(int i = 0; i < MAX_THREADS; i++){

            if((waitingTicks[i] != -1) && (clockTick >= waitingTicks[i])){

                checkPthreadError(pthread_cond_signal(&cond[i]), "pthread_cond_signal");  // Wake up thread

                waitingTicks[i] = -1;   // Mark as not waiting

            }

        }

        checkPthreadError(pthread_mutex_unlock(&mutex), "pthread_mutex_unlock");

        sleep(2);   // Wait 2 seconds before the next tick

    }

    return (NULL);

 }

 /* Makes a thread wait for a specific number of clock ticks */
 void sleepTicks(int ticks){

    checkPthreadError(pthread_mutex_lock(&mutex), "pthread_mutex_lock");

    int id = getThreadId();   // Resolve the thread's internal ID

    if(id == -1){

        fprintf(stderr, "Error: thread ID not found! \n");

        checkPthreadError(pthread_mutex_unlock(&mutex), "pthread_mutex_unlock");

        return;

    }

    /* Set the tick at which the thread should wake up */
    waitingTicks[id] = clockTick + ticks;

    /* Wait until the global clock reaches the wake-up tick */
    while(clockTick < waitingTicks[id]){

        checkPthreadError(pthread_cond_wait(&cond[id], &mutex), "pthread_cond_wait");

    }

    printf("Worker %d: wake up after %d ticks \n", id, ticks);

    checkPthreadError(pthread_mutex_unlock(&mutex), "pthread_mutex_unlock");

 }