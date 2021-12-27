// readpref.h
// written by Ryan Wiebe
// header file used by readers-preference solution

#ifndef READPREF_H
#define READPREF_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <iostream>

// defining keys and number of semaphores
// these are used when gathering shared memory and semaphores
#define SEMKEY 54321 // semaphore generatoin key
#define SHMKEY 12345 // shared memory generation key

#define NUM_SEMS 2 // number of Sys V semaphores needed

// defining use of each semaphore
// the following numbers correspond to the POSIX semaphores
#define READER_SEM 0 // READER_SEM controls shared memory between readers
#define FILE_SEM 1 // FILE_SEM controls file.txt and ensures readers and writers aren't interacting with the file simultaneously 

using namespace std;

#endif