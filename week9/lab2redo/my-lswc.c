/*
 * simple-ls.c
 * Extremely low-power ls clone.
 * ./simple-ls .
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int
main(int argc, char **argv) {

	DIR *dp;
	struct dirent *dirp;
	char *str;
	int len;
	pid_t pid;
	int strChk;

	system("date; hostname; whoami; ls *");

	if (argc != 2) {
		fprintf(stderr, "usage: %s dir_name\n", argv[0]);
		exit(1);
	}

	if ((dp = opendir(argv[1])) == NULL ) {
		fprintf(stderr, "can't open '%s'\n", argv[1]);
		exit(1);
	}

	while ((dirp = readdir(dp)) != NULL )
	{
		printf("%s\n", dirp->d_name);

		//wc check start

		//Check each name against "*.c". check will equal 0 if there's a match
		str = dirp->d_name;
		len = strlen(str);
		strChk = strcmp(str + len - 2, ".c"); // checks if the last two chars of d_name are '.c'. 0 if same

		//if they match fork and then have child exec "wc d_name"
		if(strChk == 0)
		{
			pid = fork();
			if(pid < 0){
				printf("fork error\n");
			} else if(pid == 0)
			{
				if(execlp("wc", "wc", str, (char *)0) < 0)
				{
					printf("exec error\n");
				}
			}
			if(waitpid(pid, NULL, 0) < 0)
			{
				printf("wait error\n");
			}
		}
		//wc check end
	}

	closedir(dp);
	return(0);
}
