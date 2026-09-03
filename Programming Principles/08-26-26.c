#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* cstring;

#define PROG_SIZE 256
#define TAPE_SIZE 256

#define ANSI_CMD "\e[0;"
#define ERROR "31m"
#define PROG_OUTPUT "36m"
#define ANSI_RESET "\e[0m"

#define CANONIZE_POS(dest, value) dest = clamp(value, 0, TAPE_SIZE - 1)

/*
ISA SPEC:
+ : increment element at data_ptr
- : decrement element at data_ptr
< : decrement data_ptr
> : increment data_ptr
. : output the element at data_ptr as char to stdout
, : get a single byte from stdin
[ : begin a loop (skip to matching exit bracket if tape[data_ptr] == 0)
] : end a loop
*/

int clamp(int value, int min, int max);
int interpret(char* prog_str);

int main(int argc, char** argv) {
	// argv[0] is filename (bf.exe)
	// argv[1] is the brainfuck program string
	
	char* prog_str = (char*)malloc(PROG_SIZE * sizeof(char));
	if(strlen(argv[1]) > PROG_SIZE) {
		printf(ANSI_CMD ERROR "[ERROR] Program is larger than %d bytes."ANSI_RESET, PROG_SIZE);
		return 1;
	}

	memcpy(prog_str, argv[1], PROG_SIZE);

	cstring test_str = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."; 

	int test = interpret(test_str);
	assert(test == 0);

	return interpret(prog_str);
}

int interpret(char* prog_str) {
	int data_ptr = 0;
	int* tape = (int*)malloc(TAPE_SIZE * sizeof(int));
	memset(tape, 0, TAPE_SIZE * sizeof(int));
	int canon_pos = 0;
	int c = 0;

	for(int i = 0; i < PROG_SIZE || prog_str[i] == '\0'; i++) {
		switch (prog_str[i]) {
			case '>': // move right
				data_ptr++;
				break;
			case '<': // move left
				data_ptr--;
				break;
			case '+': // increment
				CANONIZE_POS(canon_pos, data_ptr);
				tape[canon_pos]++;
				break;
			case '-': // decrement
				CANONIZE_POS(canon_pos, data_ptr);
				tape[canon_pos]--;
				break;
			case '.': // send to stdout
				CANONIZE_POS(canon_pos, data_ptr);
				printf(ANSI_CMD PROG_OUTPUT);
				printf("%c", tape[canon_pos]);
				printf(ANSI_RESET);
				break;
			case ',': // get from stdin
				CANONIZE_POS(canon_pos, data_ptr);
				tape[canon_pos] = getchar();
				break;
			case '[': // loop start
				CANONIZE_POS(canon_pos, data_ptr);
				if(tape[canon_pos] == 0) {
					i++;
					while(c > 0 || prog_str[i] != ']') {
						if (prog_str[i] == '[') c++;
						else if (prog_str[i] == ']') c--;
						i++;
					}
				}
				break;
			case ']': // loop end
				if(tape[canon_pos] != 0) {
					i--;
					while(c > 0 || prog_str[i] != '[') {
						if (prog_str[i] == ']') c++;
						else if(prog_str[i] == '[') c--;
						i--;
					}
				}
				break;
			default: // anything else
				break;
		}
	}

	return 0;
}

int clamp(int value, int min, int max) {
	if(value < min) return min;
	if(value > max) return max;
	return value;
}
