#ifndef WRITEPREF_H
#define WRITEPREF_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <iostream>

#include "../readwrite/readwrite.h"

#define SEMKEY 86421 // semaphore generation key
#define READSHMKEY 24680 // reader shared memory generation key
#define WRITESHMKEY 12468 // writer shared memory generation key

#define NUM_SEMS 4 // number of POSIX semaphores needed

#define READER_SEM 0 // READER_SEM controls shared memory between readers
#define FILE_SEM 1 // FILE_SEM controls file.txt and ensures readers and writers aren't interacting with the file simultaneously 
#define TRYREAD_SEM 2 // TRYREAD_SEM ensures writers have a higher priority than readers when accessing file.txt
#define WRITER_SEM 3 // WRITER_SEM controls shared memory between writers

using namespace std;

#endif