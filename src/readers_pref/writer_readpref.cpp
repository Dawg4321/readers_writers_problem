#include "readpref.h"
#include "../readwrite/readwrite.h"

int main(){
    /* -------------------- Intialization --------------------
        
        ** Operation **

        two semaphores gathered using semget function
        writer needs to use only the file semaphore 
        the semaphore number corresponding to this is defined readpref.h
        this helps improve readability when doing semaphore operations

        two sembuf structs are created for wait and signal operations on each sempahore
        the semaphore number is initally set to the file semaphore
        this is because only one semaphore is used in this code     

        NOTE: intialization_readpref.cpp must be run before any writers or readers
              this ensures the intial values of the semaphores and shared memory are only initialized once 

       ------------------------------------------------------- */

    // semaphore initialization

    int semid = semget(SEMKEY,NUM_SEMS,0666); // allocating two semaphores for usage 

    struct sembuf sem_signal, sem_wait; // creating two sembuff structures
                                        // these are used for signal and wait operations on file control semaphore

    sem_wait.sem_flg = SEM_UNDO; // intialising operation of sem_wait sembuf
    sem_wait.sem_op = -1;        // setting sem_op value to -1
                                 // this is so the semaphore value will be decremented when a wait operation occurs
    

    sem_signal.sem_flg = SEM_UNDO; // intialising operation of sem_signal sembuf
    sem_signal.sem_op = 1;         // setting sem_op value to 1
                                   // this is so the semaphore value will be incremented when a wait operation occurs
    
    sem_signal.sem_num = FILE_SEM; // selecting the file control semaphore on sem_signal and sem_wait as only this sem is used
    sem_wait.sem_num = FILE_SEM;   

    int counter = 1; // counter to help determine how many write operations have occured in each program instance

    // -------------------- Writer Loop --------------------

    while(1){ // infinite loop to allow file writes to continue until the program is closed

        cout << string(43,'-') << "\n"; // line printout to help seperate each read operation
        cout << counter++ << ". Please press enter to write to file "; // requesting the using to press enter to start a file read operation
        cin.ignore(); // ignoring input value

        semop(semid,&sem_wait,1); // performing wait operation on file sempahore
                                  // this prevents readers and writers gaining access to the file until the writing is complete  
        
        // ** ENTERING CRITICAL SECTION **
        writeFile(); // write to file
                     // see readwrite/readwrite.cpp
        // ** LEAVING CRITICAL SECTION **

        semop(semid,&sem_signal,1); // performing signal operation on file sempahore
                                    // this allows readers and writers to gain access to the file as the writing is complete  
    }
}