#include <stdio.h>

int main(void) {
	int i, j, k, l;
	i = 1;
	j = 2;
	k = i > k ? i : j;
	l = (i >= 0 ? i : 0) + j;
	printf("l = %d\nk = %d", l, k);
}
