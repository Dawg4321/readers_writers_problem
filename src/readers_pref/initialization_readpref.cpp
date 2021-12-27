#include "readpref.h"

int main(){
    
    cout << "Intializing Semaphores...\n";

    int semid = semget(SEMKEY,NUM_SEMS,0666|IPC_CREAT); // allocating two semaphores for usage 

    for(int i = 0; i < NUM_SEMS; i++) // intializing the value of each semaphore to 1
        semctl(semid,i,SETVAL,1);

    cout << "Intializing Reader Shared Memory...\n";

    int *reader_counter; // creating pointer to read_counter integer
                         // this will be used as variable to reference shared memory of readers

    int shmid = shmget(SHMKEY,sizeof(*reader_counter),0666|IPC_CREAT); // creating 4 bytes (size of reader_counter integer) of shared memory 

    reader_counter = (int*)shmat(shmid, 0, 0); // assigning the address of shared memory to reader_counter
    
    *reader_counter = 0; // ensuring reader_counter is initialised to 0

    cout << "** Intialization Complete! **\nPlease feel free to run any readers and writers now!\n";
    
}