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
#include <time.h>
#include <string.h>
#include <errno.h>

#define MAX_QUOTE_LENGTH 1024

struct print_job {
    int user_id;
    char filename[256];
};

struct shared_data {
    struct print_job *buffer;
    int buffer_size;
    int in;
    int out;
};

void P(int semid, int sem_num);
void V(int semid, int sem_num);
void print_error(const char *msg);
int get_id_from_file(const char *filename);
void create_quote_file(const char *filename, int user_id);

void P(int semid, int sem_num)
{
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = -1;
    op.sem_flg = 0;
    if (semop(semid, &op, 1) == -1) {
        fprintf(stderr, "P failed (semid %d, num %d): %s\n", 
                semid, sem_num, strerror(errno));
        exit(1);
    }
}

void V(int semid, int sem_num)
{
    struct sembuf op;
    op.sem_num = sem_num;
    op.sem_op = 1;
    op.sem_flg = 0;
    if (semop(semid, &op, 1) == -1) {
        fprintf(stderr, "V failed (semid %d, num %d): %s\n",
                semid, sem_num, strerror(errno));
        exit(1);
    }
}

void print_error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int get_id_from_file(const char *filename)
{
    FILE *fp;
    int id;
    
    if ((fp = fopen(filename, "r")) == NULL) {
        print_error("Failed to open ID file - is daemon running?");
    }
    
    if (fscanf(fp, "%d", &id) != 1) {
        fclose(fp);
        print_error("Failed to read ID from file");
    }
    
    fclose(fp);
    return id;
}

void create_quote_file(const char *filename, int user_id)
{
    char cmd[MAX_QUOTE_LENGTH + 256];
    
    /* Fetch quote and extract content using cut */
    snprintf(cmd, sizeof(cmd),
             "curl -s --connect-timeout 3 --max-time 5 "
             "http://api.quotable.io/random | "
             "grep -o '\"content\":\"[^\"]*' | "
             "cut -d'\"' -f4 > %s",
             filename);

    if (system(cmd) != 0) {
        /* If curl fails, create a simple message */
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            print_error("Failed to create quote file");
        }
        fprintf(fp, "User %d: [Could not fetch quote]", user_id);
        fclose(fp);
    }
}

int main()
{
    int user_id;
    int shmid;
    int semid;
    int buffer_shmid;
    struct shared_data *shared;
    char filename[256];
    int i;
    int work_time;
    struct print_job job;
    
    srand(getpid());
    user_id = getpid();
    
    /* Verify daemon is running */
    if (system("test -f print_daemon.pid") != 0) {
        print_error("Print daemon is not running");
    }
    
    /* Get IPC IDs */
    shmid = get_id_from_file("print_shmid");
    semid = get_id_from_file("print_semid");
    buffer_shmid = get_id_from_file("print_buffer_shmid");
    
    /* Attach shared memory */
    shared = (struct shared_data *)shmat(shmid, NULL, 0);
    if (shared == (struct shared_data *)-1) {
        print_error("Failed to attach shared memory");
    }
    
    /* Create unique quote file in current directory */
    snprintf(filename, sizeof(filename), "user_%d_quote.txt", user_id);
    create_quote_file(filename, user_id);
    printf("User %d created quote file: %s\n", user_id, filename);
    
    /* Main work loop */
    for (i = 0; i < 5; i++) {
        work_time = 2 + rand() % 4;
        printf("User %d is working for %d seconds...\n", user_id, work_time);
        sleep(work_time);
        
        job.user_id = user_id;
        strncpy(job.filename, filename, sizeof(job.filename));
        job.filename[sizeof(job.filename)-1] = '\0';
        
        printf("User %d is submitting print job %d\n", user_id, i+1);
        
        P(semid, 2);  /* Wait for empty slot */
        P(semid, 0);  /* Lock mutex */
        
        shared->buffer[shared->in] = job;
        shared->in = (shared->in + 1) % shared->buffer_size;
        
        V(semid, 0);  /* Release mutex */
        V(semid, 1);  /* Signal full slot */
    }
    
    printf("User %d completed all print jobs. Logging off.\n", user_id);
    remove(filename);
    shmdt(shared);
    return 0;
}
