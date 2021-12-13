#include "writerpref.h"

int main(){

    int semid = semget(SEMKEY,NUM_SEMS,0777|IPC_CREAT); // allocating two semaphores for usage 

    for(int i = 0; i < NUM_SEMS; i++) // intializing the value of each semaphore to 1
        semctl(semid,i,SETVAL,1);

    int *reader_counter; // creating pointer to read_counter integer
                         // this will be used as variable to reference shared memory of readers

    int shmid = shmget(READSHMKEY,sizeof(*reader_counter),0777|IPC_CREAT); // creating 4 bytes (size of reader_counter integer) of shared memory 

    reader_counter = (int*)shmat(shmid, 0, 0); // assigning the address of shared memory to reader_counter
    
    *reader_counter = 0; // ensuring reader_counter is initialised to 0 before read operations

    int *writer_counter; // creating pointer to writer_counter integer
                         // this will be used as variable to reference shared memory of writers
    
    int shmid2 = shmget(WRITESHMKEY,sizeof(*writer_counter),0777|IPC_CREAT); // creating 4 bytes (size of writer_counter integer) of shared memory 

    writer_counter = (int*)shmat(shmid2, 0, 0); // assigning the address of shared memory to writer_counter
    
    *writer_counter = 0; // ensuring writer_counter is initialised to 0 before write operations
}