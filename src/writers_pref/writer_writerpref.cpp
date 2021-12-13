#include "writerpref.h"

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
    

    sem_signal.sem_flg = SEM_UNDO; // intialising operation of sem_signal sembuf
    sem_signal.sem_op = 1;         // setting sem_op value to 1
                                   // this is so the semaphore value will be incremented when a wait operation occurs

    int *writer_counter;

    int shmid = shmget(WRITESHMKEY,sizeof(*writer_counter),0777|IPC_CREAT); // creating 4 bytes (size of reader_counter integer) of shared memory 

    writer_counter = (int*)shmat(shmid, 0, 0); // assigning the address of shared memory to reader_counter
    
    *writer_counter = 0; // ensuring reader_counter is initialised to 0

    int counter = 1; // counter to help determine how many write operations have occured in each program instance

    while(1){

        cout << string(43,'-') << "\n"; // line printout to help seperate each read operation
        cout << counter++ << ". Please press enter to write to file "; // requesting the using to press enter to start a file read operation
        cin.ignore(); // ignoring input value

        sem_wait.sem_num = WRITER_SEM; // selecting the writer control sempahore
        semop(semid,&sem_wait,1); // performing wait operation on writer control sempahore
                                  // this ensures only one writer can access the shared memory at a time
        
        *writer_counter = *writer_counter + 1; // incrementing writer counter in shared memory 
        
        if(*writer_counter == 1){ // if at least one writer is trying to write
            sem_wait.sem_num = TRYREAD_SEM; // selecting try to read semaphore
            semop(semid,&sem_wait,1); // performing a wait operation on the try to read semaphore
                                      // this locks out readers from reading until all writers are done writing
        }   

        sem_signal.sem_num = WRITER_SEM; // selecting the writer control sempahore
        semop(semid,&sem_signal,1); // performing signal operation on writer control sempahore
                                    // this allows the next writer in the queue to increment the writer counter

        sem_wait.sem_num = FILE_SEM; // selecting file control semaphore
        semop(semid,&sem_wait,1); // performing wait operation on file sempahore
                                  // this prevents readers and writers gaining access to the file until the writing is complete

        // ** ENTERING CRITICAL SECTION **
        writeFile(); // writing to file
        // ** LEAVING CRITICAL SECTION **
        
        sem_wait.sem_num = FILE_SEM; // selecting file control semaphore
        semop(semid,&sem_signal,1); // performing signal operation on file sempahore
                                    // this allows readers and writers to gain access to the file as the writing is complete 

        sem_wait.sem_num = WRITER_SEM; // selecting the writer control sempahore
        semop(semid,&sem_wait,1); // performing wait operation on writer control sempahore
                                  // this ensures only one writer can access the shared memory at a time
        
        *writer_counter = *writer_counter - 1; // incrementing writer counter in shared memory 
        
        if(*writer_counter == 0){ // if this writer is the last writer
            sem_signal.sem_num = TRYREAD_SEM; // selecting try to read semaphore
            semop(semid,&sem_signal,1); // performing a signal operation on the try to read semaphore
                                        // this allows readers begin reading as all writers have finished
        }   

        sem_signal.sem_num = WRITER_SEM; // selecting the writer control sempahore
        semop(semid,&sem_signal,1); // performing signal operation on writer control sempahore
                                    // this allows the next writer in the queue to access shared memory
    }
}