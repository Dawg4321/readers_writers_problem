#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <iostream>

#include "readwrite.h"

#define SEMKEY 54321
#define SHMKEY 12345

#define NUM_SEMS 2

#define READER_SEM 0
#define FILE_SEM 1

using namespace std;

int main(){

    int semid = semget(SEMKEY,NUM_SEMS,0777|IPC_CREAT); // allocating two semaphores for usage 

    for(int i = 0; i < NUM_SEMS; i++) // intializing the value of each semaphore to 1
        semctl(semid,i,SETVAL,1);

    struct sembuf sem_signal, sem_wait; // creating two sembuff structures
                                        // these are used for signal and wait operations on each semaphore
    
    sem_wait.sem_flg = SEM_UNDO; // intialising operation of sem_wait sembuf
    sem_wait.sem_op = -1;        // setting sem_op value to -1
                                 // this is so the semaphore value will be decremented when a wait operation occurs
    
    sem_signal.sem_flg = SEM_UNDO; // intialising operation of sem_signal sembuf
    sem_signal.sem_op = 1;         // setting sem_op value to 1
                                   // this is so the semaphore value will be incremented when a wait operation occurs
    

    int *reader_counter; // creating pointer to read_counter integer
                         // this will be used as variable to reference shared memory of readers

    int shmid = shmget(SHMKEY,sizeof(*reader_counter),0777|IPC_CREAT); // creating 4 bytes (size of reader_counter integer) of shared memory 

    reader_counter = (int*)shmat(shmid, 0, 0); // assigning the address of shared memory to reader_counter
    
    *reader_counter = 0; // ensuring reader_counter is initialised to 0
    
    int counter = 1; // counter to help determine how many read operations have occured in each program instance

    while(1){ // infinite loop to allow file reads to continue until the program closes
        cout << string(43,'-') << "\n"; // line printout to help seperate each read operation
        cout << counter++ << ". Please press enter to read from the file "; // requesting the using to press enter to start a file read operation
        cin.ignore(); // ignoring input value

        sem_wait.sem_num = READER_SEM; // selecting reader control semaphore
        semop(semid,&sem_wait,1); // performing wait operation on reader control semaphore
                                  // this ensures only one reader can access the shared memory at a time
        
        *reader_counter = *reader_counter + 1; // incrementing reader counter in shared memory

        if(*reader_counter == 1){ // if the current reader is the first
            sem_wait.sem_num = FILE_SEM; // selecting file control semaphore
            semop(semid,&sem_wait,1); // performing a wait operation on the file semaphore
        }                             // this ensures only readers have access to the file 

        sem_signal.sem_num = READER_SEM; // selecting reader control semaphore
        semop(semid,&sem_signal,1); // performing signal operation on reader control semaphore
                                    // this allows the next reading in the queue to access the shared memory
        
        // ** ENTERING CRITICAL SECTION **
        readFile(); // performing file read
        // ** LEAVING CRITICAL SECTION **
        
        sem_wait.sem_num = READER_SEM; // selecting reader control semaphore
        semop(semid,&sem_wait,1); // performing wait operation on reader control semaphore
                                  // this ensures only one reader can access the shared memory at a time

        *reader_counter = *reader_counter - 1; // incrementing reader counter in shared memory

        if(*reader_counter == 0){ // if the current reader is the last
            sem_signal.sem_num = FILE_SEM; // selecting file control semaphore
            semop(semid,&sem_signal,1); // performing signal operation on file sempahore
        }                               // this allows writers to gain access to the file as their are no more readers waiting to read 
            
        sem_signal.sem_num = READER_SEM; // selecting reader control semaphore
        semop(semid,&sem_signal,1); // performing signal operation on reader control semaphore
                                    // this allows the next reading in the queue to access the shared memory
    }
}