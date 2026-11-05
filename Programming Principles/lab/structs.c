#include <stdio.h>
#include <stdbool.h>

typedef enum {
	ERR,
	OK
} RESULT_TYPE;

typedef struct {
	union { // anon union
		char* err_msg;
		int result;
	} value;
	RESULT_TYPE type;
} fn_foo_result;

fn_foo_result division(int a, int b) {
	if(b == 0) {
		return (fn_foo_result){ { .err_msg = "Division by zero" }, ERR };
	}
	return (fn_foo_result){ { .result = (a / b) }, OK};
}

void print_foo_result(fn_foo_result result) {
	if(result.type == ERR) {
		printf("%s\n", result.value);
	} else if(result.type == OK) {
		printf("%d\n", result.value);
	} else {
		printf("Unknown value.");
	}
}

int main(void) {
	fn_foo_result r = division(1, 2);
	print_foo_result(r);

	r = division(1, 0);
	print_foo_result(r);

	return 0;
}
