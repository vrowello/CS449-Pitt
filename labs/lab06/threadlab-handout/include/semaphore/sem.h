#pragma once
#include <pthread.h>

#ifndef NATIVE_SEMAPHORES
typedef struct {
    pthread_mutex_t mux;
    pthread_cond_t cond;
    int counter;
} sem_t;
#else
// This will use native semaphores
#include <semaphore.h>
#endif

/** Creates a semaphore, and initializes the variables */
sem_t *sem_new(int init);
/** Deletes the semaphore given, making sure all dynamic memory is freed */
void sem_delete(sem_t *sem);

/** Locks the semaphore, blocking if necessary */
int sem_lock(sem_t *sem);
/** Unlocks the semaphore, releasing any threads waiting */
int sem_unlock(sem_t *sem);
