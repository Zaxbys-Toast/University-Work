#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>


main(int argc, char *argv[])
{
int shmid;
char *message;

/*****  Get Shared Memory and ID *****/

shmid  = atoi(argv[1]);

/****   Attach to the shared memory  ******/

message = (char *) shmat(shmid, NULL, SHM_RND);

strcpy(message,argv[2]);


}

