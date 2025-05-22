// Will King
// CSC 460
// 2/14/2025
// Alphabet Squared

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void create_processes(int index, int n) {
	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork Failed");
		exit(1);
	} else if (pid == 0) {
		char letter = 'A' + index;
		int i;
		for (i = 0; i < n; i++) {
			printf("%c:%d\n", letter, getpid());
		}
		exit(0);
	}

}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		printf("Usage: a.out <N>\n");
		return 1;
	}

	int n = atoi(argv[1]);
	if (n < 1 || n > 26) {
		printf("N must be between 1 and 26\n");
		return 1;
	}

	int i;
	for (i = 0; i < n; i++) {
		create_processes(i, n);
	}

	for (i = 0; i < n; i++) {
		wait(NULL);
	}

	return 0;
}
