#include <semaphore/sem.h>

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


// Configuration, can be overridden by compile time definitions
#ifndef N_CLIENTS
#define N_CLIENTS 100
#endif

#ifndef N_MACHINES
#define N_MACHINES 4
#endif

#ifndef N_DRIERS
#define N_DRIERS 2
#endif

#ifndef N_FOLDERS
#define N_FOLDERS 2
#endif



// Semaphores to manage access to resources
sem_t *washers;
sem_t *driers;
sem_t *folders;

// Used to maximize initial chaos 
//  by trying to release many thread at once
sem_t *chaos;

/** The following functions are used to simulate the behavior of the laundry
 *  machines.  They use semaphores to guarantee that clients don't use more 
 * machines than are available.
 */
void wash(int client_id) {
    sem_lock(washers);
    printf("%d:Washing\n", client_id);
    usleep(rand()%45);
    printf("%d:Washing:Done\n", client_id);
    sem_unlock(washers);
}
void dry(int client_id) {
    sem_lock(driers);
    printf("%d:Drying\n", client_id);
    usleep(rand()%60);
    printf("%d:Drying:Done\n", client_id);
    sem_unlock(driers);
}
void fold(int client_id) {
    sem_lock(folders);
    printf("%d:Folding\n", client_id);
    usleep(rand()%10);
    printf("%d:Folding:Done\n", client_id);
    sem_unlock(folders);
}

/** Function that is run by each client thread.  It simulates the client
 *  doing laundry.  It uses the wash, dry, and fold functions to simulate
 *  the behavior of the machines.
 */
void *clean(void *input) {

    int client_id = (size_t)input;

    // Wait for release
    sem_lock(chaos);
    
    // Laundry!!!
    wash(client_id);
    dry(client_id);
    fold(client_id);

    return input;
}

int main(void) {

    // Initialize configuration variables
    size_t n_clients = N_CLIENTS;
    size_t n_washing_machines = N_MACHINES;
    size_t n_driers = N_DRIERS;
    size_t n_folding_stations = N_FOLDERS;

    // Create the semaphores to manage the different resources
    washers = sem_new(n_washing_machines);
    driers = sem_new(n_driers);
    folders = sem_new(n_folding_stations);
    chaos = sem_new(0);

    // Create the threads to simulate the clients
    pthread_t clients[n_clients];
    for (size_t i=0; i<n_clients; i++) {
        pthread_create(clients+i, NULL, clean, (void*)i);
    }

    // Try to cause chaos by releasing all the threads at once
    for (int i=0; i<n_clients; i++) {
        sem_unlock(chaos);
    }

    // Join all clients before the end of the program
    for (int i=0; i<n_clients; i++) {
        pthread_join(clients[i], NULL);
    }

    // Cleanup before the end of the program
    sem_delete(washers);
    sem_delete(driers);
    sem_delete(folders);
    sem_delete(chaos);

    return 0;
}