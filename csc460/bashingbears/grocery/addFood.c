// Will King
// 2/28/25
// CSC 460
// Shared Grocery List

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

struct glistStruct {
    int id;
    char name[20];
    int favNum;
    char favFood[30];
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
	printf("Wrong number of arguments!\n");
	return 1;
    }
   
    char *food= argv[1];
    // Path to the file containing the shared memory ID
    const char *glist_id_file = "/pub/csc460/glist/GLISTID.txt";
    
    // Open the file to read the shared memory ID
    FILE *file = fopen(glist_id_file, "r");
    if (file == NULL) {
        perror("Failed to open GLISTID.txt");
        exit(EXIT_FAILURE);
    }

    // Read the shared memory ID from the file
    int shmid;
    if (fscanf(file, "%d", &shmid) != 1) {
        perror("Failed to read shared memory ID");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
    struct glistStruct *list = (struct glistStruct *)shmat(shmid, NULL, 0);

    int myID = 16;
    int i;
    for(i = 0; i < 24; i++) {
	if(list[i].id == myID) {
		strncpy(list[i].favFood, food, sizeof(list[i].favFood) - 1);
		break;
	}
    }
    shmdt(list);
    return 0;
}
