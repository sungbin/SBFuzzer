#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int runner(int argc, char* argv[]) {
	
	if(argc < 2) {
                printf("ERROR: THE NUMBER OF AGURMENTS MUST BE BIGGER THAN TWO!\n");
                return 1;
        }

	int fd[2];
	pipe(fd);
	int val = 0;
	int pid = 1;
	fork(&pid);

	if(pid) { // Parent

		int start, end;
		start = (int)clock() / CLOCKS_PER_SEC;
		end = (((int)clock()) / CLOCKS_PER_SEC);

		while ( (end - start) < 100) {
			sleep(3); /* sleep 3 seconds */
			rc = waitpid(pid, &status, WNOHANG);
			if (rc < 0) {
				perror("waitpid");
				return 1;
			}
			if (WIFEXITED(status) || WIFSIGNALED(status)) {
        			/* it's done */
        			break;
    			}
			end = (((int)clock()) / CLOCKS_PER_SEC);
		}

		close(fd[1]);
		read(fd[0], &val, sizeof(val));
		printf("Parent received value: %d\n", val);
		close(fd[0]);

		
	} else { // Child
		close(fd[0]);
	
		dup2(fd[1], STDOUT_FILENO)

		execl(argv[1], (argv+1) ); //STD_OUT 으로 값이 출력이 안됨?
		
	}
	
	return 0;
}

