#include <stdio.h>


int main() {
	char line[256];
	char* s;

	if(fgets(line, sizeof(line), stdin)) {
		printf("%s", line);
	}

	return 0;
}
