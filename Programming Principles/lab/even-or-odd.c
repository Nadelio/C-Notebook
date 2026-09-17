#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("[ERROR] No number passed into program");
		return 1;
	} else if (argc != 2) {
		printf("[ERROR] Too many numbers passed into program");
		return 1;
	}

	int number = atoi(argv[1]);
	printf("%d is %s\n", number, number % 2 == 0? "even." : "odd");

	return 0;
}
