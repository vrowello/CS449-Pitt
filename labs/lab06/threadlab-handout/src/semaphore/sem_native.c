/** This file contains implementats the functions using native semaphore
 *  functions.  You should not modify this file. It's used to compare your 
 *  with native semaphores.
 */

#include <stdlib.h>
#define NATIVE_SEMAPHORES 1
#include <semaphore/sem.h>
#include <stdio.h>



int sem_lock(sem_t *sem) {
    return sem_wait(sem);
}

int sem_unlock(sem_t *sem) {
    return sem_post(sem);
}

sem_t *sem_new(int init) {
  sem_t *sem = malloc(sizeof(sem_t));
  sem_init(sem, 0, init);
  return sem;
}

void sem_delete(sem_t *sem) {
    if (sem) {
        sem_destroy(sem);
        free(sem);
    }
}

