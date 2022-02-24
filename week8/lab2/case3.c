#include <stdio.h>

int main(){
	printf("Case 3 Processes:\n");
	fork(); fork(); fork();
	printf("This is process %u\n", getpid());
}
