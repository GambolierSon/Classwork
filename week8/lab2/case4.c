#include <stdio.h>

int main(){
	int pid;
	int pid2;
	printf("Case 3 Processes:\n");
	if((pid=fork()) && (pid2 = fork())){fork();}
	if((pid=fork()) && (pid2 = fork())){fork();}
	if((pid=fork()) && (pid2 = fork())){fork();}
	printf("This is process %u\n", getpid());
}
