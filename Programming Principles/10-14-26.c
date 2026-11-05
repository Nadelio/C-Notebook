#include <stdio.h>

int gcd(int m, int n) {
	printf("\tm = %d\n\tn = %d\n---\n", m, n);
	return (m%n == 0)? n : gcd(n, m%n);
}

int main(void) {
	printf("%d\n", gcd(10, 2));
	printf("%d\n", gcd(7, 2));
	printf("%d\n", gcd(2, 10));
	printf("%d\n", gcd(48, 18));
	return 0;
}
