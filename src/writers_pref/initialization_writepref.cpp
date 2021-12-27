// initialization_writepref.cpp
// written by Ryan Wiebe
// file to initialze shared memory and semaphores in writers-preference solution

#include "writepref.h"

/* --------------------initialization_writepref--------------------
    
    This file is used to initialize the semaphores and shared memory for the writers-preference solution.
    It must be run before any readers or writers can be run to ensure defined behaviour

   ---------------------------------------------------------------- */

int main(){

    cout << "Intializing Semaphores...\n";

    int semid = semget(SEMKEY,NUM_SEMS,0666|IPC_CREAT); // allocating two semaphores for usage using Sys V system call

    for(int i = 0; i < NUM_SEMS; i++) // intializing the value of each semaphore to 1
        semctl(semid,i,SETVAL,1);     // this is critical as the semaphores must only be initialized once

    cout << "Intializing Reader Shared Memory...\n";

    int *reader_counter; // creating pointer to read_counter integer
                         // this will be used as variable to reference shared memory of readers

    int shmid = shmget(READSHMKEY,sizeof(*reader_counter),0666|IPC_CREAT); // creating 4 bytes of shared memory (size of reader_counter integer)

    reader_counter = (int*)shmat(shmid, 0, 0); // assigning the address of shared memory to reader_counter
    
    *reader_counter = 0; // ensuring reader_counter is initialised to 0 before read operations
                         // this is critical as reader_counter must only be initialised once

    cout << "Intializing Writer Shared Memory...\n";

    int *writer_counter; // creating pointer to writer_counter integer
                         // this will be used as variable to reference shared memory of writers
    
    int shmid2 = shmget(WRITESHMKEY,sizeof(*writer_counter),0666|IPC_CREAT); // creating 4 bytes of shared memory (size of writer_counter integer) 

    writer_counter = (int*)shmat(shmid2, 0, 0); // assigning the address of shared memory to writer_counter
    
    *writer_counter = 0; // ensuring writer_counter is initialised to 0 before write operations
                         // this is critical as writer_counter must only be initialised once

    cout << "** Intialization Complete! **\nPlease feel free to run any readers and writers now!\n";

    return 0;
}
