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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <new quantity>\n", argv[0]);
        return 1;
    }
    int newQuantity = atoi(argv[1]);
    
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

    struct glistStruct *groceryList;

    groceryList = (struct glistStruct *)shmat(shmid, NULL, 0);

    int myId = 16;  
    int i;
    for (i = 0; i < 24; i++)
    {
        if (groceryList[i].id == myId)
        {
            groceryList[i].favNum = newQuantity;
            printf("Updated %s's favNum to %d.\n", groceryList[i].name, newQuantity);
            break;
        }
    }

    shmdt(groceryList);

    return 0;
}

