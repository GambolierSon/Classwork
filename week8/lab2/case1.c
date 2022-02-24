#include <stdio.h>

int main(){ // Case1 fork
	printf("Case1 Processes\n");
	fork();
	printf("This is process %u\n", getpid());
}
