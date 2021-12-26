#include "readpref.h"
#include "../readwrite/readwrite.h"

int main(){

    /* -------------------- Intialization --------------------
        
        ** Operation **

        two semaphores gathered using semget function
        reader needs to use the file and reader semaphores
        the semaphore number corresponding to these are defined readpref.h
        these help improve readability when doing semaphore operations

        two sembuf structs are created for wait and signal operations on each sempahore
        the semaphore number must be set before each semaphore operation

            e.g. sem_wait.sem_num = FILE_SEM; // setting semaphore to perform wait operation on
                 semop(semid,&sem_wait,1);    // performing wait operation specified semaphore       
        
        shared memory is then initialized to size of an integer
        int *reader_counter is then set to point at reader shared memory

        NOTE: intialization_readpref.cpp must be run before any writers or readers
              this ensures the intial values of the semaphores and shared memory are only initialized once 

       ------------------------------------------------------- */

    // semaphore initialization

    int semid = semget(SEMKEY,NUM_SEMS,0666); // gathering allocated semaphores for usage 

    struct sembuf sem_signal, sem_wait; // creating two sembuff structures
                                        // these are used for signal and wait operations on each semaphore
    
    sem_wait.sem_flg = SEM_UNDO; // intialising operation of sem_wait sembuf
    sem_wait.sem_op = -1;        // setting sem_op value to -1
                                 // this is so the semaphore value will be decremented when a wait operation occurs
    
    sem_signal.sem_flg = SEM_UNDO; // intialising operation of sem_signal sembuf
    sem_signal.sem_op = 1;         // setting sem_op value to 1
                                   // this is so the semaphore value will be incremented when a wait operation occurs
    
    // shared memory initialization

    int *reader_counter; // creating pointer to read_counter integer
                         // this will be used as variable to reference shared memory of readers

    int shmid = shmget(SHMKEY,sizeof(*reader_counter),0666); // creating 4 bytes (size of reader_counter integer) of shared memory 

    reader_counter = (int*)shmat(shmid, 0, 0); // assigning the address of shared memory to reader_counter
    
    int counter = 1; // counter to help determine how many read operations have occured in each program instance

    // -------------------- Reader Loop --------------------

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
                    // see readwrite/readwrite.cpp
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