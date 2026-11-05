#include <stdio.h>

// forward declaration
int check_even(int* arr, size_t arr_len);
int sum_of_array(int* arr, size_t arr_len);

int main(void) {
	int array[5] = { 2, 7, 8, 9, 10 };
	// use size_t to make sure you can handle any length of array
	size_t arr_len = 5;

	int num_even = check_even(array, arr_len);
	int sum = sum_of_array(array, arr_len);
	printf("Count of even numbers: %d\n", num_even);
	printf("Sum: %d\n", sum);
}

int check_even(int* arr, size_t arr_len) {
	int count = 0;
	for(int i = 0; i < arr_len; i++) {
		// *() = dereference
		// arr is a pointer to the beginning of the array (first element)
		// i can be treated as an offset from the beginning of the array (hence starting at 0)
		// *(arr + i) is equivalent to arr[i], and is only used because we are using a pointer here instead of an array
		if(*(arr + i) % 2 == 0) count++;
	}
	return count;
}

int sum_of_array(int* arr, size_t arr_len) {
	int sum = 0;
	for(int i = 0; i < arr_len; i++) {
		sum += *(arr+i);
	}
	return sum;
}
