// Will King
// 3/7/25
// CSC 460 - Operating Systems
// Fastest Sync
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void p(int sem_id, int sem_num) {
  struct sembuf sops;
  sops.sem_num = sem_num;
  sops.sem_op = -1;
  sops.sem_flg = 0;
  semop(sem_id, &sops, 1);
}

void v(int sem_id, int sem_num) {
  struct sembuf sops;
  sops.sem_num = sem_num;
  sops.sem_op = 1;
  sops.sem_flg = 0;
  semop(sem_id, &sops, 1);
}

int main(int argc, char * argv[]) {
  if (argc != 2) { 
    printf("Usage: %s <N>", argv[0]);
    return 1;
  }
  // Declare a bunch of variables
  int num_processes, i, j, sem_id;
  pid_t pid;

  num_processes = atoi(argv[1]);
  
  if(num_processes <= 0 || num_processes > 26) {
    printf("<N> must be a positive integer less than 27");
    return 1;
  }
  
  // Set up the semaphores
  sem_id = semget(IPC_PRIVATE, num_processes, 0770);
  if (sem_id == -1) {
    printf("Semaphore error");
    return 1;
  } 
  
  for (i = 0; i < num_processes; i++) {
    semctl(sem_id, i, SETVAL, 0);
  }

  for (i = 0; i < num_processes; i++) {
    pid = fork();
    if (pid == 0) {
      for (j = 0; j < num_processes; j++) {	
	p(sem_id, i);
	printf("%c: %d\n", 'A' + i, getpid());
	v(sem_id, (i + 1) % num_processes);
      }
      return 0;
    } else if (pid < 1) {
      printf("fork error");
      return 1;
    }
  }
  // Signal the first semaphore to start the process
  v(sem_id, 0);
  for (i = 0; i < num_processes; i++) {
    wait(NULL);
  }
  semctl(sem_id, 0, IPC_RMID, 0);

  return 0;
}
