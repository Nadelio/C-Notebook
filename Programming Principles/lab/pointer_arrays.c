#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Please enter the length of the array: ");
	int arr_len;
	do {
		scanf("%d", &arr_len);
		if(arr_len <= 0) printf("Array length must be greater than zero.\n");
	} while(arr_len <= 0);
	int* arr = (int*)malloc(arr_len * sizeof(int));

	for(int i = 0; i < arr_len; i++) {
		printf("Element #%d: ", i + 1);
		scanf("%d", (arr + i));
	}

	int max = INT_MIN;
	for(int i = 0; i < arr_len; i++) {
		if(arr[i] > max) max = arr[i];
	}

	printf("The largest integer is: %d\n", max);
}
