#include <stdio.h>

int main(){ // Case1 fork
	printf("Case5 Processes\n");
	int i;
	for(i = 1; i <= 5; i++){
		fork();
	}
	printf("This is process %u\n", getpid());
}
