#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Hello, World\n");
	int* arr = (int*)malloc(100 * sizeof(int));
	for(size_t i = 0; i < 100; i++) {
		arr[i] = i;
	}
	
	for(size_t i = 0; i < 100; i++) {
		printf("arr[%zu] = %d\n", i, arr[i]);
	}

	return 0;
}
