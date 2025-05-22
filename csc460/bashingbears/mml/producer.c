#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <fcntl.h>
#include "header.h"
void P(int semid, int sem_num) {
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = -1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

void V(int semid, int sem_num) {
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

void sig_handler(int signo) {
    if (signo == SIGUSR1) {
        /* Do nothing, just wake up from pause */
    }
}

int main(int argc, char *argv[]) {
    int size, time;
    int semid, shmid;
    FILE *fp;
    void *shared;
    SharedInfo *info;
    Request req;
    
    if (argc != 3) {
        printf("Usage: %s size time\n", argv[0]);
        exit(1);
    }
    
    size = atoi(argv[1]);
    time = atoi(argv[2]);
    
    /* Read shared info */
    fp = fopen("memory_manager.info", "r");
    if (!fp) {
        printf("Memory manager not running\n");
        exit(1);
    }
    
    fscanf(fp, "%d %d", &semid, &shmid);
    fclose(fp);
    
    /* Attach shared memory */
    shared = shmat(shmid, NULL, 0);
    if (shared == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    
    info = (SharedInfo *)shared;
    
    /* Validate request */
    if (size < 1 || size > info->rows * info->cols || time < 1 || time > 30) {
        printf("Invalid request parameters\n");
        shmdt(shared);
        exit(1);
    }
    
    printf("%d is requesting %d blocks of RAM for %d seconds\n", getpid(), size, time);
    
    /* Setup signal handler */
    signal(SIGUSR1, sig_handler);
    
    /* Prepare request */
    req.pid = getpid();
    req.size = size;
    req.time = time;
    req.placed = 0;
    
    /* Add to buffer */
    P(semid, EMPTY);
    P(semid, MUTEX);
    
    Request *buffer = (Request *)(info + 1);
    buffer[info->in] = req;
    info->in = (info->in + 1) % info->buffer_size;
    
    V(semid, MUTEX);
    V(semid, FULL);
    
    /* Wait for completion */
    pause();
    
    printf("%d finished my request of %d blocks for %d seconds\n", getpid(), size, time);
    
    shmdt(shared);
    return 0;
}
