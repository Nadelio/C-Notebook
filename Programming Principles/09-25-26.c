#include <stdio.h>

int main(void) {
	int x;
	int a = (x = 2, x + 4, x + 8);
	printf("%d\n", a);

	return 0;
}
