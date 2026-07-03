 #include <pthread.h>
 #include <semaphore.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <time.h>
 
 /* Semaphore representing whether the table is available (1 = free, 0 = busy) */
 sem_t table;
 /* Semaphores for each food combination placed by the waiter */
 sem_t pies_meat, meat_veg, veg_pies;

 /* Checks the return value of semaphore operations and terminates on failure. */
 static void checkSemaphoreError(int result, const char* operation){

    if (result != 0) {

        perror(operation);

        exit(EXIT_FAILURE);

    }

 }

 /* Checks the return value of pthread operations and terminates on failure. */
 static void checkPthreadError(int result, const char* operation){

    if (result != 0) {

        fprintf(stderr, "%s failed: %s\n", operation, strerror(result));

        exit(EXIT_FAILURE);

    }

 }

 /* Function representing the waiter */
 void* waiter(void* arg){

    (void)arg;

    while(1){

        /* Wait until the table is available */
        sem_wait(&table);

        /* Randomly choose a combination of two food items */
        int r = rand() % 3;

        /* Provide the selected combination and signal the respective client */
        switch (r) {

            case 0:
                printf("Waiter gives pies & meat\n");
                checkSemaphoreError(sem_post(&pies_meat), "sem_post(pies_meat)");
                break;

            case 1:
                printf("Waiter gives meat & veg\n");
                checkSemaphoreError(sem_post(&meat_veg), "sem_post(meat_veg)");
                break;

            case 2:
                printf("Waiter gives veg & pies\n");
                checkSemaphoreError(sem_post(&veg_pies), "sem_post(veg_pies)");
                break;
        }

    }

    return (NULL);

 }

 /* Client 1 has vegetables; waits for pies & meat */
 void* client1(void* arg){

    (void)arg;

    while(1){

        /* Wait until waiter gives pies & meat */
        checkSemaphoreError(sem_wait(&pies_meat), "sem_wait(pies_meat)");

        printf("Client1 has veg, starts eating \n");

        sleep(1);   // Simulate eating time

        /* Signal that the table is now free */
        checkSemaphoreError(sem_post(&table), "sem_post(table)");

    }

    return (NULL);

 }

 /* Client 2 has pies; waits for meat & veg */
 void* client2(void* arg){

    (void)arg;

    while(1){

        /* Wait until waiter gives meat & veg */
        checkSemaphoreError(sem_wait(&meat_veg), "sem_wait(meat_veg)");

        printf("Client2 has pies, starts eating \n");

        sleep(1);   // Simulate eating time

        /* Signal that the table is now free */
        checkSemaphoreError(sem_post(&table), "sem_post(table)");

    }

    return (NULL);

 }

 /* Client 3 has meat; waits for veg & pies */
 void* client3(void* arg){

    (void)arg;

    while(1){

        /* Wait until waiter gives veg & pies */
        checkSemaphoreError(sem_wait(&veg_pies), "sem_wait(veg_pies)");

        printf("Client3 has meat, starts eating \n");

        sleep(1);   // Simulate eating time

        /* Signal that the table is now free */
        checkSemaphoreError(sem_post(&table), "sem_post(table)");

    }

    return (NULL);

 }

 int main(void) {

    srand((unsigned int)time(NULL));

    pthread_t w;
    pthread_t c1, c2, c3;

    /* Initialize the semaphores */
    checkSemaphoreError(sem_init(&table, 0, 1), "sem_init(table)");   // Table starts as free

    /* No food initially */
    checkSemaphoreError(sem_init(&pies_meat, 0, 0), "sem_init(pies_meat)");
    checkSemaphoreError(sem_init(&meat_veg, 0, 0), "sem_init(meat_veg)");
    checkSemaphoreError(sem_init(&veg_pies, 0, 0), "sem_init(veg_pies)");

    /* Create waiter thread */
    checkPthreadError(pthread_create(&w, NULL, waiter, NULL), "pthread_create(waiter)");

    /* Create client threads */
    checkPthreadError(pthread_create(&c1, NULL, client1, NULL), "pthread_create(client1)");
    checkPthreadError(pthread_create(&c2, NULL, client2, NULL), "pthread_create(client2)");
    checkPthreadError(pthread_create(&c3, NULL, client3, NULL), "pthread_create(client3)");

    /* Wait for all threads to finish (they won't in this infinite loop) */
    checkPthreadError(pthread_join(w, NULL), "pthread_join(waiter)");
    
    checkPthreadError(pthread_join(c1, NULL), "pthread_join(client1)");
    checkPthreadError(pthread_join(c2, NULL), "pthread_join(client2)");
    checkPthreadError(pthread_join(c3, NULL), "pthread_join(client3)");

    checkSemaphoreError(sem_destroy(&table), "sem_destroy(table)");
    checkSemaphoreError(sem_destroy(&pies_meat), "sem_destroy(pies_meat)");
    checkSemaphoreError(sem_destroy(&meat_veg), "sem_destroy(meat_veg)");
    checkSemaphoreError(sem_destroy(&veg_pies), "sem_destroy(veg_pies)");

    return 0;

 }