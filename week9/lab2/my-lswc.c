/*
 * my-lswc.c
 * Extremely low-power ls clone. 
 * Prints out some environment data at the beginning.
 * ./my-lswc .
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int
main(int argc, char **argv) {

	DIR *dp;
	struct dirent *dirp;
	char *str;
	int strCheck;
	int len;
	pid_t pid;

	system("date; hostname; whoami; ls *"); //print out system data

	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL ){
		printf("%s\n", dirp->d_name);
		
		//wc check start
		str = dirp->d_name; //set str to filename

		len = strlen(str); //find the length of the str
		
		strCheck = strcmp(str + len - 2, ".c"); //compare the last two chars of str to ".c"
		
		if((strCheck == 0)){ //if the last two chars of str are ".c"
			pid = fork();
			if(pid < 0){ //if fork produced an error
				printf("fork error\n");
			} else if(pid == 0){ //if process is child run wc
				if(execlp("wc", "wc", str, (char *)0) < 0){
					printf("exec error\n");
				}
			}		
			if(waitpid(pid, NULL, 0) < 0){ //wait for wc to end
				printf("wait error\n");
			}
		}
		//wc check end
	}
	closedir(dp);
	return(0);
}
