#include <stdio.h>

// using a macro
#define SQUARE(x) (x) * (x)

// using an inline function
inline long square(long x) {
	return x * x;
}

int main(void) {
	long x = 10;

	// using a macro gives you a lot of flexibility, with some drawbacks
	printf("%ld\n", SQUARE(x));
	
	// using an inline function can give you stricter typing to avoid common macro issues with expressions
	printf("%ld\n", square(x));
	return 0;
}
