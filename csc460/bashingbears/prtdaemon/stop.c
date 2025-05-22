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

void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

int main() {
    FILE *fp;
    int shmid = -1;
    int buffer_shmid = -1;
    int semid = -1;
    pid_t daemon_pid = -1;

    /* 1. Check if daemon is running */
    if (system("test -f ./print_daemon.pid") != 0) {
        print_error("Print daemon is not running");
        return 1;
    }

    /* 2. Get daemon PID */
    fp = fopen("./print_daemon.pid", "r");
    if (!fp || fscanf(fp, "%d", &daemon_pid) != 1) {
        print_error("Failed to read daemon PID");
        if (fp) fclose(fp);
        return 1;
    }
    fclose(fp);

    /* 3. Get shared memory IDs */
    fp = fopen("./print_shmid", "r");
    if (!fp || fscanf(fp, "%d", &shmid) != 1) {
        print_error("Failed to read shared memory ID");
        if (fp) fclose(fp);
        return 1;
    }
    fclose(fp);

    fp = fopen("./print_buffer_shmid", "r");
    if (!fp || fscanf(fp, "%d", &buffer_shmid) != 1) {
        print_error("Failed to read buffer memory ID");
        if (fp) fclose(fp);
        return 1;
    }
    fclose(fp);

    /* 4. Get semaphore ID */
    fp = fopen("./print_semid", "r");
    if (!fp || fscanf(fp, "%d", &semid) != 1) {
        print_error("Failed to read semaphore ID");
        if (fp) fclose(fp);
        return 1;
    }
    fclose(fp);

    /* 5. Kill the daemon process */
    char kill_cmd[50];
    sprintf(kill_cmd, "kill %d", daemon_pid);
    if (system(kill_cmd) != 0) {
        print_error("Failed to kill daemon process");
        return 1;
    }

    /* 6. Clean up IPC resources */
    if (shmid != -1) {
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            print_error("Failed to remove shared memory");
        }
    }

    if (buffer_shmid != -1) {
        if (shmctl(buffer_shmid, IPC_RMID, NULL) == -1) {
            print_error("Failed to remove buffer memory");
        }
    }

    if (semid != -1) {
        if (semctl(semid, 0, IPC_RMID) == -1) {
            print_error("Failed to remove semaphores");
        }
    }

    /* 7. Remove temporary files */
    system("rm -f ./print_daemon.pid");
    system("rm -f ./print_shmid");
    system("rm -f ./print_buffer_shmid");
    system("rm -f ./print_semid");

    printf("Successfully stopped print daemon (PID: %d)\n", daemon_pid);
    printf("Cleaned up all shared resources\n");
    
    return 0;
}
