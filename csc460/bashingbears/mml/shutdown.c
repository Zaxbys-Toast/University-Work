#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include "header.h"

void V(int semid, int sem_num) {
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

int main() {
    int semid, shmid;
    FILE *fp;
    
    /* Read shared info */
    fp = fopen("memory_manager.info", "r");
    if (!fp) {
        printf("Memory manager not running\n");
        exit(1);
    }
    
    fscanf(fp, "%d %d", &semid, &shmid);
    fclose(fp);
    
    /* Signal shutdown */
    V(semid, SHUTDOWN);
    
    printf("Shutdown signal sent\n");
    return 0;
}
