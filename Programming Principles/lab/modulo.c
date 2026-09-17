#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

int main(void) {
	int a, b;
	printf("Enter two integers\n");
	scanf_s("%d %d", &a, &b);
	printf("The value of A is: %d\n""The value of B is: %d\n""The remainder when A is divided by B is: %d\n", a, b, (a % b));
	printf("The value of A/B is: %.3f\n", (float)a/b);
	printf("Enter a value: ");
	int n;
	scanf_s("%d", &n);
	printf("%s\n", n == 2 ? "The given value is 2." : "The given value is not 2.");
	if(n % 2 == 0) printf("%d is divisible by 2.\n", n);
	else printf("%d is not divisible by 2.\n", n);

	if(n % 3 == 0) printf("%d is divisible by 3.\n", n);
	else printf("%d is not divisible by 3.\n", n);

	return 1;
}
