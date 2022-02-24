/*
 *  shell2.c 
 *  simplest shell with an exit command and a signal handler for ^C 
 *     running in loop to read input string (command) to be processed
 *     To exit, type EOF (ctlr+D) or ctlr+C 
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

char *getinput(char *buffer, size_t buflen) 
{
	printf("$$ ");
	return fgets(buffer, buflen, stdin);
}

void sig_handler(int signum)
{
	//Signal received and handler activates
	printf("\nSignal Caught!\n");
}

int main(int argc, char **argv) 
{
	char buf[1024];
	pid_t pid;
	int status;

	signal(SIGINT, sig_handler); //Set up handler to catch SIGINT


	while (getinput(buf, sizeof(buf))) {
		buf[strlen(buf) - 1] = '\0';

		if(strcmp(buf, "exit") == 0){
			printf("shell1 exits\n");
			exit(0);
		}

		if((pid=fork()) == -1) {
			fprintf(stderr, "shell: can't fork: %s\n",
					strerror(errno));
			continue;
		} else if (pid == 0) {
			/* child */
			execlp(buf, buf, (char *)0);
			fprintf(stderr, "shell: couldn't exec %s: %s\n", buf,
					strerror(errno));
			exit(EX_DATAERR);
		}

		if ((pid=waitpid(pid, &status, 0)) < 0)
			fprintf(stderr, "shell: waitpid error: %s\n",
					strerror(errno));
	}
	exit(EX_OK);
}
