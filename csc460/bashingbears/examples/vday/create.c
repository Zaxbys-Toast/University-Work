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

shmid  =  shmget(IPC_PRIVATE, 100*sizeof(char), 0777);
if (shmid == -1)
    {
    printf("Could not get shared memory.\n");
    return(0);
    }

printf("SHMID: %d\n\n",shmid);
sleep(5);

/****   Attach to the shared memory  ******/

message = (char *) shmat(shmid, NULL, SHM_RND);

strcpy(message,"I love CSC 460!");

while (1)
{
	printf("%s\n",message);
	sleep(1);
}

}

