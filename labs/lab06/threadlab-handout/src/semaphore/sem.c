#include <stdlib.h>
#include <semaphore/sem.h>
#include <stdio.h>

/* Create and allocate a new semaphore.  The initial value of the semaphore
 * is given by init.  If init is less than zero, return NULL. 
 * Initialize the mux and cond variables. You'll need them to protect accesses to the counter.
 */
sem_t *sem_new(int init) {

    // Don't allow negative initial values
    if (init<0) return NULL;

    // Allocate memory for the semaphore
    sem_t *sem = (sem_t*)malloc(sizeof(sem_t));
    if (!sem) return NULL;

    // Set the semaphore's initial value
    sem->counter = init;

    // Initialize the mux that protects the counter
    if (pthread_mutex_init(&sem->mux, NULL) != 0) {
        free(sem);
        return NULL;
    }

    // Initialize the condition variable that is used to wait on the semaphore
    if (pthread_cond_init(&sem->cond, NULL) != 0) {
        pthread_mutex_destroy(&sem->mux);
        free(sem);
        return NULL;
    }

    return sem;
}

/** Free the semaphore. */
void sem_delete(sem_t *sem) {
    // Destroy the mutex and condition variable
    // Free the memory for the semaphore
    if (sem) {
        pthread_mutex_destroy(&sem->mux);
        pthread_cond_destroy(&sem->cond);
        free(sem);
    }
}

/** Decrement the counter on the semaphore.  
 * If the value is greater than zero, allow the function to return after derementing.
 * Otherwise, wait for it to become positive. 
 *
 * You'll need to use the mux and cond variables to protect accesses to the counter.
 * Don't loop while locked!
 */
int sem_lock(sem_t *sem) {
	pthread_mutex_lock(&sem->mux);
    while (sem->counter<=0) {
    	//waits for signal to prevent deadlock
    	pthread_cond_wait(&sem->cond, &sem->mux);
    }
    
    sem->counter--;
    pthread_mutex_unlock(&sem->mux);
    return 0;
}

/** Increment the counter on the semaphore.  
 *
 * You'll need to use the mux and cond variables to protect accesses to the counter.
 */
int sem_unlock(sem_t *sem) {
	pthread_mutex_lock(&sem->mux);
    sem->counter++;
    if(sem->counter > 0) {
    	//signals sem_lock that the counter is above 0
    	pthread_cond_signal(&sem->cond);
    }
    pthread_mutex_unlock(&sem->mux);
    return 0;
}




