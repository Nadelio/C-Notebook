#include <stdio.h>

int (*beep)();

int meep() {
	return 2;
}

int main() {
  beep = *meep;
	printf("%d\n", beep());
	printf("%d\n", meep());
}
