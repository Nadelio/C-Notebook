#include <stdio.h>
#include <stdint.h>

int main(void) {
	int arr[5] = {0, 1, 2, 3, 4};
	int* p = &arr[0]; 

	printf("%d\n", *p);
	p++; // increment address by 4 bytes because pointer to an int (4 bytes)
	printf("%d\n", *p);

	printf("%p\n", p);
	p--;
	printf("%p\n", p);

	char str[5] = {'a', 'b', 'c', 'd', 'e'};
	char* cp = &str[0];

	printf("%c\n", *cp);
	cp++; // increment address by 1 byte because pointer to a char (1 byte)
	printf("%c\n", *cp);

	printf("%p\n", cp);
	cp--;
	printf("%p\n", cp);
}
