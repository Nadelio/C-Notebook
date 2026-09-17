#include <stdio.h>

int main(void) {
	int b = 1;
	printf("b = %d\n", b);
	int a = b += 2;
	printf("a = %d, b = %d\n", a, b);
	return 0;
}
