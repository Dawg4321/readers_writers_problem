#ifndef READPREF_H
#define READPREF_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <iostream>

#include "../readwrite/readwrite.h"

#define SEMKEY 54321 // keys for shared memory
#define SHMKEY 12345

#define NUM_SEMS 2 // number of POSIX semaphores needed

// defining use of each semaphore
// the following numbers correspond to the POSIX semaphores
#define READER_SEM 0 // READER_SEM controls shared memory between readers
#define FILE_SEM 1 // FILE_SEM controls file.txt and ensures readers and writers aren't interacting with the file simultaneously 

using namespace std;

#endif