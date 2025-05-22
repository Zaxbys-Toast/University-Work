// Will King
// CSC 460
// Print Daemon
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

/* Structure for print jobs */
struct print_job {
    int user_id;
    char filename[256];
};

/* Structure for shared data */
struct shared_data {
    struct print_job *buffer;
    int buffer_size;
    int in;
    int out;
};

void P(int semid, int sem_num) {
    struct sembuf op = {sem_num, -1, 0};
    semop(semid, &op, 1);
}

void V(int semid, int sem_num) {
    struct sembuf op = {sem_num, 1, 0};
    semop(semid, &op, 1);
}

void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

void cleanup(int shmid, int semid, int buffer_shmid) {
    char cmd[100];
    
    if (shmid != -1) {
        sprintf(cmd, "ipcrm -m %d", shmid);
        system(cmd);
    }
    
    if (buffer_shmid != -1) {
        sprintf(cmd, "ipcrm -m %d", buffer_shmid);
        system(cmd);
    }
    
    if (semid != -1) {
        sprintf(cmd, "ipcrm -s %d", semid);
        system(cmd);
    }
    
    system("rm -f print_daemon.pid");
    system("rm -f print_shmid print_semid print_buffer_shmid");
}

int main(int argc, char *argv[]) {
    int buffer_size;
    int shmid = -1;
    int semid = -1;
    int buffer_shmid = -1;
    struct shared_data *shared = NULL;
    pid_t pid = getpid();
    char pid_str[20];
    FILE *fp;
    
    if (argc != 2) {
        print_error("Usage: daemon <buffer_size (1-10)>");
        exit(1);
    }
    
    buffer_size = atoi(argv[1]);
    if (buffer_size < 1 || buffer_size > 10) {
        print_error("Buffer size must be between 1 and 10");
        exit(1);
    }
    
    if (system("test -f print_daemon.pid") == 0) {
        print_error("Daemon is already running");
        exit(1);
    }
    
    /* Create PID file */
    sprintf(pid_str, "%d", pid);
    fp = fopen("print_daemon.pid", "w");
    if (!fp) {
        print_error("Failed to create PID file");
        exit(1);
    }
    fprintf(fp, "%d", pid);
    fclose(fp);
    
    /* Create and attach shared memory */
    shmid = shmget(IPC_PRIVATE, sizeof(struct shared_data), IPC_CREAT | 0666);
    if (shmid == -1) {
        print_error("Failed to create shared memory");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    
    fp = fopen("print_shmid", "w");
    if (!fp) {
        print_error("Failed to create shmid file");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    fprintf(fp, "%d", shmid);
    fclose(fp);
    
    shared = (struct shared_data *)shmat(shmid, NULL, 0);
    if (shared == (struct shared_data *)-1) {
        print_error("Failed to attach shared memory");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    
    /* Create and attach buffer */
    buffer_shmid = shmget(IPC_PRIVATE, buffer_size * sizeof(struct print_job), IPC_CREAT | 0666);
    if (buffer_shmid == -1) {
        print_error("Failed to create buffer shared memory");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    
    fp = fopen("print_buffer_shmid", "w");
    if (!fp) {
        print_error("Failed to create buffer shmid file");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    fprintf(fp, "%d", buffer_shmid);
    fclose(fp);
    
    shared->buffer = (struct print_job *)shmat(buffer_shmid, NULL, 0);
    if (shared->buffer == (struct print_job *)-1) {
        print_error("Failed to attach buffer");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    
    /* Initialize shared data */
    shared->buffer_size = buffer_size;
    shared->in = 0;
    shared->out = 0;
    
    /* Create semaphores */
    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);
    if (semid == -1) {
        print_error("Failed to create semaphores");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    
    fp = fopen("print_semid", "w");
    if (!fp) {
        print_error("Failed to create semid file");
        cleanup(shmid, semid, buffer_shmid);
        exit(1);
    }
    fprintf(fp, "%d", semid);
    fclose(fp);
    
    /* Initialize semaphores */
    semctl(semid, 0, SETVAL, 1);  /* MUTEX = 1 */
    semctl(semid, 1, SETVAL, 0);  /* FULL = 0 */
    semctl(semid, 2, SETVAL, buffer_size);  /* EMPTY = buffer_size */
    
    printf("Print daemon started");
    
    /* Main processing loop */
    while (1) {
        P(semid, 1);  /* Wait for FULL */
        P(semid, 0);  /* Wait for MUTEX */
        
        struct print_job job = shared->buffer[shared->out];
        shared->out = (shared->out + 1) % shared->buffer_size;
        
        V(semid, 0);  /* Signal MUTEX */
        V(semid, 2);  /* Signal EMPTY */
        
        printf("\nPrinting job for user %d: %s\n", job.user_id, job.filename);
        
        char cmd[300];
        sprintf(cmd, "cat %s 2>/dev/null", job.filename);
        printf("File contents:\n");
        system(cmd);
        printf("--- End of print job ---\n");
    }
    
    /* Cleanup (unreachable in normal operation) */
    cleanup(shmid, semid, buffer_shmid);
    return 0;
}
