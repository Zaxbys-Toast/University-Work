#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_children(int gen, int max_gen) {
   	if (gen > max_gen) return;

    	printf("%d\t%d\t%d\n", gen, getpid(), getppid());

    	int i;  
    	for (i = 0; i < gen + 1; i++) {  
        	pid_t pid = fork();

        	if (pid < 0) {
            		printf("Fork failed!\n");
            		exit(1);
        	}
        	if (pid == 0) {  
        		create_children(gen + 1, max_gen);
            		exit(0);  
        	}
   	}

    	sleep(1); 
}

int main(int argc, char *argv[]) {
    	if (argc != 2) {
        	printf("Usage: %s <N>\n", argv[0]);
        	exit(1);
    	}

    	int N = atoi(argv[1]);
    	if (N < 0 || N > 5) {
    	   	printf("Absolutely not you fool\n");
        	exit(1);
    	}

    	printf("Gen\tPID\tPPID\n");
    	create_children(0, N);

    	return 0;
}
