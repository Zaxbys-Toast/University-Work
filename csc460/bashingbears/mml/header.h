#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEM_KEY 1234
#define SHM_KEY 5678
#define MAX_ROWS 20
#define MAX_COLS 50
#define MAX_BUFFER 26

/* Semaphore indices */
#define MUTEX 0
#define FULL 1
#define EMPTY 2
#define SHUTDOWN 3

typedef struct {
    int rows;
    int cols;
    int buffer_size;
    int shutdown_flag;
    int next_id;
    int in;
    int out;
} SharedInfo;

typedef struct {
    pid_t pid;
    int size;
    int time;
    int assigned_id;
    int placed;
} Request;

typedef struct {
    int id;
    int remaining_time;
    int start_block;
    int size;
    pid_t pid;
} Job;

#endif
