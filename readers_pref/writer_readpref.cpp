#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

#include "readwrite.h"

#define SEMKEY 54321

#define NUM_SEMS 2

#define FILE_SEM 1

using namespace std;

int main(){

    int semid = semget(SEMKEY,NUM_SEMS,0777); // allocating two semaphores for usage 

    for(int i = 0; i < NUM_SEMS; i++) // intializing the value of each semaphore to 1
        semctl(semid,i,SETVAL,1);

    struct sembuf sem_signal, sem_wait; // creating two sembuff structures
                                        // these are used for signal and wait operations on file control semaphore
    
    sem_wait.sem_num = FILE_SEM;
    sem_wait.sem_flg = SEM_UNDO; // intialising operation of sem_wait sembuf
    sem_wait.sem_op = -1;        // setting sem_op value to -1
                                 // this is so the semaphore value will be decremented when a wait operation occurs
    
    sem_signal.sem_num = FILE_SEM;
    sem_signal.sem_flg = SEM_UNDO; // intialising operation of sem_signal sembuf
    sem_signal.sem_op = 1;         // setting sem_op value to 1
                                   // this is so the semaphore value will be incremented when a wait operation occurs
    int reader_counter = 0;

    while(1){
        semop(semid,&sem_wait,1);
        
        writeFile();

        semop(semid,&sem_signal,1);
        
    }

}