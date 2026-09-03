#include <stdio.h>
#include <stdarg.h>

void println(const char* fmt, ...) { 
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args); // vprintf and its sibling functions are used for creating our own printf-like functions
	printf("\n");
	va_end(args);
	return;
}

int main(void) {
	int a = 23;
	float f = 23.45;
	println("%.2f\n%d", f, a);
	return 0;
}
