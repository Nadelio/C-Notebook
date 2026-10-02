#include <stdio.h>

// array designators
int main(void) {
	int arr[100] = {[0 ... 99] = 0}; //! needs the spaces in between the two indexes
	for(int i = 0; i < 100; i++) {
		printf("[%d] = %d\n", i, arr[i]);
	}
	return 0;
}
