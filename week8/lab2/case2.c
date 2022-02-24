#include <stdio.h>

int main(){
	printf("Case 2 Processes:\n");
	fork(); fork();
	printf("This is process %u\n", getpid());
}
