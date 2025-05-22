// Will King
// CSC 460
// 2/25
// Faster Sync


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>


typedef struct {
    int turn;
} shared_mem_t;

int main(int argc, char *argv[]) {
    int MAX_PROCS = 26;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        exit(1);
    }
    
    int N = atoi(argv[1]);
    if (N < 1 || N > MAX_PROCS) {
        fprintf(stderr, "N must be between 1 and 26\n");
        exit(1);
    }
    
    int shmid = shmget(IPC_PRIVATE, sizeof(shared_mem_t), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    
    shared_mem_t *shared = (shared_mem_t *)shmat(shmid, NULL, 0);
    if (shared == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    shared->turn = 0;
    
    int i, j;
    for (i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            char letter = 'A' + i;
            for (j = 0; j < N; j++) {
                while (shared->turn != i);
                printf("%c:%d\n", letter, getpid());
                fflush(stdout);
                shared->turn = (i + 1) % N;
            }
            exit(0);
        }
    }
    
    for (i = 0; i < N; i++) {
        wait(NULL);
    }
    
    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}
