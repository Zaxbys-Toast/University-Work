#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define DEAD 3

struct shared_data {
    int state[NUM_PHILOSOPHERS];
    int time_elapsed;
};

int sem_id, shm_id;
struct shared_data *shared;

void P(int sem_num) {
    struct sembuf op = {sem_num, -1, 0};
    semop(sem_id, &op, 1);
}

void V(int sem_num) {
    struct sembuf op = {sem_num, 1, 0};
    semop(sem_id, &op, 1);
}

void test(int id) {
    if (shared->state[id] == HUNGRY &&
        shared->state[(id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING &&
        shared->state[(id + 1) % NUM_PHILOSOPHERS] != EATING) {
        shared->state[id] = EATING;
        V(id);
    }
}

void philosopher(int id) {
    srand(time(NULL) ^ getpid());
    while (1) {
        sleep(rand() % 5 + 1); // Thinking
        
        P(NUM_PHILOSOPHERS); // Lock shared data
        shared->state[id] = HUNGRY;
        test(id);
        V(NUM_PHILOSOPHERS); // Unlock shared data
        
        P(id); // Wait until able to eat
        
        sleep(rand() % 3 + 1); // Eating
        
        P(NUM_PHILOSOPHERS);
        shared->state[id] = THINKING;
        test((id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
        test((id + 1) % NUM_PHILOSOPHERS);
        V(NUM_PHILOSOPHERS);
        
        if (shared->time_elapsed >= 60) break;
    }
    P(NUM_PHILOSOPHERS);
    shared->state[id] = DEAD;
    V(NUM_PHILOSOPHERS);
    exit(0);
}

int main() {
    key_t key;
    int i;
    key = ftok("safephils", 'S');
    shm_id = shmget(key, sizeof(struct shared_data), IPC_CREAT | 0666);
    shared = (struct shared_data *)shmat(shm_id, NULL, 0);
    sem_id = semget(key, NUM_PHILOSOPHERS + 1, IPC_CREAT | 0666);

    for (i = 0; i < NUM_PHILOSOPHERS + 1; i++) {
        semctl(sem_id, i, SETVAL, 1);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        shared->state[i] = THINKING;
        if (fork() == 0) {
            philosopher(i);
        }
    }

    while (1) {
        int dead_count = 0;
        sleep(1);
        shared->time_elapsed++;
        printf("%d.", shared->time_elapsed);
        for (i = 0; i < NUM_PHILOSOPHERS; i++) {
            if (shared->state[i] == THINKING) printf(" thinking");
            else if (shared->state[i] == HUNGRY) printf(" hungry");
            else if (shared->state[i] == EATING) printf(" eating");
            else if (shared->state[i] == DEAD) {
                printf(" dead");
                dead_count++;
            }
        }
        printf("\n");
        if (dead_count == NUM_PHILOSOPHERS) break;
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) wait(NULL);
    semctl(sem_id, 0, IPC_RMID);
    shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}
