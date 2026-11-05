#include <stdio.h>

typedef char* cstring;

int main(void) {
	cstring hello_world = "Hello, World!"; // is null-terminated (ends in a null byte '\0')
	printf("%s\n", hello_world);
	return 0;
}
