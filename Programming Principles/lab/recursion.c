#include <stdio.h>

int decimal_to_binary(int n) {
	if(n == 0) { return 0; } // base case
	printf("%d", n % 2);
	return decimal_to_binary(n /= 2); // recursive case
}

int main(void) {
	int n = 25;
	while(n != 0) {
		printf("%d", n % 2); // print least significant binary digit
		n /= 2; // right shift
	}
	printf("\n");
	decimal_to_binary(25);

	return 0;
}
