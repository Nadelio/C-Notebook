#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* cstring;

void center_str(const char* str, int field_width);

int main(void) {
	const cstring tmp = "abc";
	cstring str = (char*)malloc(strlen(tmp) + 1);
	memcpy(str, tmp, strlen(tmp) + 1);
	center_str(str, 4);
	*(str + 1) = 'd';
	center_str(str, 4);
	return 0;
}

void center_str(const char* str, int field_width) {
	int padlen = (field_width - strlen(str)) / 2;
	printf("%*s%s%*s\n", padlen, " ", str, padlen, " ");
}
