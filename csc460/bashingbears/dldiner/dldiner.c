// Will King
// CSC 460
// 3/24/25
// Deadlock Diner

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PHILOSOPHERS 5

int chopsticks;  // Semaphore set for the 5 chopsticks

void p(int semid, int semnum) {
    struct sembuf op;
    op.sem_num = semnum;
    op.sem_op = -1;   
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

void v(int semid, int semnum) {
    struct sembuf op;
    op.sem_num = semnum;
    op.sem_op = 1;  
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

void random_wait() {
    int i, wait_time;
    wait_time = rand() % 50000 + 10000;  // Random CPU-intensive wait
    for (i = 0; i < wait_time; i++);
}

void think(int id) {
    int i;
    for (i = 0; i < id; i++) printf("\t");
    printf("%d THINKING\n", id);
    random_wait();
}

void eat(int id) {
    int i;
    for (i = 0; i < id; i++) printf("\t");
    printf("%d EATING\n", id);
    random_wait();
}

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % PHILOSOPHERS;

    // Seed random with process ID
    srand(getpid());

    while (1) {
        think(id);

        for (id = 0; id < left; id++) printf("\t");
        printf("%d HUNGRY\n", left);

        // Pick up left chopstick
        p(chopsticks, left);

        random_wait();  

        // Pick up right chopstick 
        p(chopsticks, right);

        eat(left);

        // Put down left chopstick
        v(chopsticks, left);

        random_wait(); 

        // Put down right chopstick
        v(chopsticks, right);
    }
}

int main() {
    pid_t pids[PHILOSOPHERS];
    int i;

    chopsticks = semget(IPC_PRIVATE, PHILOSOPHERS, IPC_CREAT | 0666);
    if (chopsticks == -1) {
        perror("semget failed");
        exit(1);
    }
    
    for (i = 0; i < PHILOSOPHERS; i++) {
        if (semctl(chopsticks, i, SETVAL, 1) == -1) {
            perror("semctl failed");
            exit(1);
        }
    }

    // Fork philosophers
    for (i = 0; i < PHILOSOPHERS; i++) {
        pids[i] = fork();
        // Child process
        if (pids[i] == 0) {
            philosopher(i);
            exit(0);
        }
    }

    for (i = 0; i < PHILOSOPHERS; i++) {
        wait(NULL);
    }


    return 0;
}

