#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 256

int main(void) {
	int num;
	printf("Enter a number: ");
	int result = scanf_s("%d", &num);
	if(result == 0) {
		_set_errno(5);
		perror("Failed to parse a number from stdin");
		return 1;
	} else if(result == EOF) {
		_set_errno(5);
		perror("Error with stdin, could not assign values");
		return 1;
	}
	printf("Your number is: %d\n", num);
	return 0;
}
