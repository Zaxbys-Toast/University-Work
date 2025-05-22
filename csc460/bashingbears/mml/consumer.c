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

void init_semaphores(int semid) {
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;
    
    arg.val = 1;
    semctl(semid, MUTEX, SETVAL, arg);
    
    arg.val = 0;
    semctl(semid, FULL, SETVAL, arg);
    
    arg.val = MAX_BUFFER;
    semctl(semid, EMPTY, SETVAL, arg);
    
    arg.val = 0;
    semctl(semid, SHUTDOWN, SETVAL, arg);
}

void display_ram(char ram[MAX_ROWS][MAX_COLS], int rows, int cols, Job jobs[], int job_count, Request waiting[], int wait_count) {
    int i, j;
    system("clear");
    printf("Will's Memory Manager\n");
    printf("--------------------\n");
    
    printf("ID\tPID\tSize\tSec\n");
    for (i = 0; i < job_count; i++) {
        printf("%c.\t%d\t%d\t%d\n", 'A' + jobs[i].id, jobs[i].pid, jobs[i].size, jobs[i].remaining_time);
    }
    for (i = 0; i < wait_count; i++) {
        printf("%c.\t%d\t%d\t%d (waiting)\n", 'A' + waiting[i].assigned_id, waiting[i].pid, waiting[i].size, waiting[i].time);
    }
    
    printf("\n");
    for (i = 0; i < cols + 2; i++) printf("*");
    printf("\n");
    
    for (i = 0; i < rows; i++) {
        printf("*");
        for (j = 0; j < cols; j++) {
            printf("%c", ram[i][j]);
        }
        printf("*\n");
    }
    
    for (i = 0; i < cols + 2; i++) printf("*");
    printf("\n");
}

int first_fit(char ram[MAX_ROWS][MAX_COLS], int rows, int cols, int size) {
    int i, j;
    int consecutive = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (ram[i][j] == '.') {
                consecutive++;
                if (consecutive == size) {
                    return i * cols + j - size + 1;
                }
            } else {
                consecutive = 0;
            }
        }
    }
    return -1;
}

void place_job(char ram[MAX_ROWS][MAX_COLS], int rows, int cols, int start, int size, char id) {
    int i;
    int start_row = start / cols;
    int start_col = start % cols;
    
    for (i = 0; i < size; i++) {
        int row = (start_row + (start_col + i) / cols);
        int col = (start_col + i) % cols;
        ram[row][col] = id;
    }
}

void remove_job(char ram[MAX_ROWS][MAX_COLS], int rows, int cols, Job job) {
    int i;
    int start_row = job.start_block / cols;
    int start_col = job.start_block % cols;
    
    for (i = 0; i < job.size; i++) {
        int row = (start_row + (start_col + i) / cols);
        int col = (start_col + i) % cols;
        ram[row][col] = '.';
    }
}

int main(int argc, char *argv[]) {
    int rows, cols, buffer_size;
    int semid, shmid, fd;
    SharedInfo *shared;
    char ram[MAX_ROWS][MAX_COLS];
    Job jobs[MAX_BUFFER];
    Request waiting[MAX_BUFFER];
    int job_count = 0;
    int wait_count = 0;
    time_t last_display, current;
    Request *buffer;
    Request req;
    Job new_job;
    int pos, i, j;
    
    if (argc != 4) {
        printf("Usage: %s rows cols buffer_size\n", argv[0]);
        exit(1);
    }
    
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    buffer_size = atoi(argv[3]);
    
    if (rows < 1 || rows > MAX_ROWS || cols < 1 || cols > MAX_COLS || 
        buffer_size < 1 || buffer_size > MAX_BUFFER) {
        printf("Invalid parameters\n");
        exit(1);
    }
    
    /* Check if another consumer is running */
    fd = open("memory_manager.lock", O_CREAT | O_EXCL | O_RDWR, 0644);
    if (fd < 0) {
        printf("Memory manager is already running\n");
        exit(1);
    }
    
    /* Initialize semaphores */
    semid = semget(SEM_KEY, 4, IPC_CREAT | 0666);
    init_semaphores(semid);
    
    /* Initialize shared memory */
    shmid = shmget(SHM_KEY, sizeof(SharedInfo) + buffer_size * sizeof(Request), IPC_CREAT | 0666);
    shared = (SharedInfo *)shmat(shmid, NULL, 0);
    
    shared->rows = rows;
    shared->cols = cols;
    shared->buffer_size = buffer_size;
    shared->shutdown_flag = 0;
    shared->next_id = 0;
    shared->in = 0;
    shared->out = 0;
    
    /* Write IDs to file */
    FILE *fp = fopen("memory_manager.info", "w");
    fprintf(fp, "%d %d", semid, shmid);
    fclose(fp);
    
    /* Initialize RAM */
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            ram[i][j] = '.';
        }
    }
    
    last_display = time(NULL);
    
    while (1) {
        /* Check for shutdown */
        if (semctl(semid, SHUTDOWN, GETVAL) > 0) {
            break;
        }
        
        /* Check for new requests */
        P(semid, FULL);
        P(semid, MUTEX);
        
        buffer = (Request *)(shared + 1);
        if (shared->in != shared->out) {
            req = buffer[shared->out];
            shared->out = (shared->out + 1) % buffer_size;
            
            req.assigned_id = shared->next_id++;
            if (shared->next_id >= 26) shared->next_id = 0;
            
            /* Try to place in RAM */
            pos = first_fit(ram, rows, cols, req.size);
            if (pos != -1) {
                new_job.id = req.assigned_id;
                new_job.pid = req.pid;
                new_job.size = req.size;
                new_job.remaining_time = req.time;
                new_job.start_block = pos;
                jobs[job_count++] = new_job;
                place_job(ram, rows, cols, pos, req.size, 'A' + req.assigned_id);
                req.placed = 1;
            } else {
                waiting[wait_count++] = req;
            }
        }
        
        V(semid, MUTEX);
        V(semid, EMPTY);
        
        /* Update time and check for completed jobs */
        current = time(NULL);
        if (current != last_display) {
            last_display = current;
            
            for (i = 0; i < job_count; i++) {
                jobs[i].remaining_time--;
                if (jobs[i].remaining_time <= 0) {
                    remove_job(ram, rows, cols, jobs[i]);
                    /* Notify producer */
                    kill(jobs[i].pid, SIGUSR1);
                    
                    /* Remove from jobs array */
                    for (j = i; j < job_count - 1; j++) {
                        jobs[j] = jobs[j + 1];
                    }
                    job_count--;
                    i--;
                }
            }
            
            /* Check waiting queue */
            for (i = 0; i < wait_count; i++) {
                pos = first_fit(ram, rows, cols, waiting[i].size);
                if (pos != -1) {
                    new_job.id = waiting[i].assigned_id;
                    new_job.pid = waiting[i].pid;
                    new_job.size = waiting[i].size;
                    new_job.remaining_time = waiting[i].time;
                    new_job.start_block = pos;
                    jobs[job_count++] = new_job;
                    place_job(ram, rows, cols, pos, waiting[i].size, 'A' + waiting[i].assigned_id);
                    
                    /* Remove from waiting array */
                    for (j = i; j < wait_count - 1; j++) {
                        waiting[j] = waiting[j + 1];
                    }
                    wait_count--;
                    i--;
                }
            }
            
            display_ram(ram, rows, cols, jobs, job_count, waiting, wait_count);
        }
        
        usleep(100000); /* Sleep for 100ms */
    }
    
    /* Cleanup */
    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    remove("memory_manager.info");
    close(fd);
    unlink("memory_manager.lock");
    
    printf("Memory manager shutdown complete\n");
    return 0;
}
