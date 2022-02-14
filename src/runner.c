#include <stdio.h>

#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int
runner(int argc, char* argv[]) {

	printf("argc: %d, argv[0]: %s, argv[1]: %s\n",argc,argv[0],argv[1]);

        int result;
        int pipefd[2];
        FILE *cmd_output;
        char buf[1024];
        int status;

        result = pipe(pipefd);
        if (result < 0) {
          perror("pipe");
          return -1;
        }

        result = fork();
        if(result < 0) {
          return -1;
        }

        if (result == 0) {
          dup2(pipefd[1], STDOUT_FILENO); /* Duplicate writing end to stdout */
          close(pipefd[0]);
          close(pipefd[1]);

	  execl(argv[0],argv[0],argv[1],NULL); // TODO: multiple argument
          //execl("../test/test_atoi", "test_atoi", "10",NULL);
          //execl("/Users/sungbin/Desktop/SBFuzzer/test/test_atoi", "/Users/sungbin/Desktop/SBFuzzer/test/test_atoi", "10",NULL);
          _exit(1);
        }

        /* Parent process */
        close(pipefd[1]); /* Close writing end of pipe */

        cmd_output = fdopen(pipefd[0], "r");

        if (fgets(buf, sizeof buf, cmd_output)) {
          printf("Data from who command: %s\n", buf);
        } else {
          printf("No data received.\n");
        }

        wait(&status);
        printf("Child exit status = %d\n", status);

        return 0;
}
