#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define FILENAME_MAX_LEN 64
#define EXPRESSION_MAX_LEN 256

#define UNREACHABLE _set_errno(0); perror("Unreachable branch"); exit(1);
#define UNIMPLEMENTED _set_errno(0); perror("Unimplemented function"); exit(1);

typedef struct {
	size_t length;
	long* results;
} ResultArray;

ResultArray* parse_file(char* filename);

typedef struct {
	size_t pos;
	const char* input;
} Parser;

long parse_expr(char* expr);

long parse_comparison(Parser* parser);
long parse_addition(Parser* parser);
long parse_multiplication(Parser* parser);
long parse_unary(Parser* parser);
long parse_power(Parser* parser);
long parse_primary(Parser* parser);

void skip_whitespace(Parser* parser);
bool match(Parser* parser, char c);
void syntax_error(Parser* parser, const char* message);

void syntax_print(char* expr);
bool is_integer(char c);
bool is_operator(char c);

int main(int argc, char** argv) {

	// PARSE ARGS
	bool passed_in_file = false;
	bool passed_in_expr = false;
	if(argc == 3) { // has 2 arguments
		if(strcmp(argv[1], "-f") == 0) { // is argv[1] == "-f"?
			passed_in_file = true;
		}
	} else if(argc == 2) { // has 1 argument
		if(strcmp(argv[1], "-f") == 0) { // is argv[1] == "-f"?
			printf("Usage: [-f <filename>] | <expression>\n");
			return 1;
		}
		passed_in_expr = true;
	} else {
		printf("Usage: [-f <filename>] | <expression>\n");
		return 1;
	}

	char* filename = (char*)malloc(FILENAME_MAX_LEN); // allocate 64 bytes for filename (EXCESSIVE)
	if(passed_in_file) {
		if(strlen(argv[2]) >= FILENAME_MAX_LEN) { // fail if given filename too long
			_set_errno(36);
			perror("File name too long");
			return 1;
		} else {
			memcpy(filename, argv[2], strlen(argv[2]) + 1); // copy given filename to filename variable (including null terminator)
			printf("Successfully parsed filename: %s\n", filename);
		}
	} else {
		free(filename);
	}

	char* expr = (char*)malloc(EXPRESSION_MAX_LEN); // allocate 256 bytes for expression (excessive)
	if(passed_in_expr) {
		if(strlen(argv[1]) >= EXPRESSION_MAX_LEN) {
			_set_errno(90);
			perror("Expression too long.");
			return 1;
		} else {
			memcpy(expr, argv[1], strlen(argv[1]) + 1);
			printf("Validated expression length.\n");
		}
	} else {
		free(expr);
	}

	// PARSE FILE/EXPR

	if(passed_in_file) {
		ResultArray* result = parse_file(filename);
		if(result == NULL) {
			_set_errno(5);
			perror("ResultArray is a NULL Pointer");
			return 1;
		}

		for(size_t i = 0; i < (result->length); i++) {
			if(result->results[i] == 0 || result->results[i] == 1) {
				printf("Result[%zu] = %ld (%s)\n", i, result->results[i], result->results[i] ? "true" : "false");
			} else {
				printf("Result[%zu] = %ld\n", i, result->results[i]);
			
			}
		}

		free(result->results);
		free(result);
	} else if(passed_in_expr) {
		long result = parse_expr(expr);
		if(result == 0 || result == 1) {
			printf("Result = %ld (%s)\n", result, result ? "true" : "false");
		} else {
			printf("Result = %ld\n", result);
		}
	} else {
		UNREACHABLE
	}

	// CLEANUP
	
	if(passed_in_expr) {
		free(expr);
	} else if(passed_in_file) {
		free(filename);
	} else {
		UNREACHABLE
	}
	return 0;
}

ResultArray* parse_file(char* filename) {
	FILE* file;
	errno_t err;
	ResultArray* results = NULL;

	if((err = fopen_s(&file, filename, "r")) != 0) {
		_set_errno(err);
		perror("Cannot open file");
		exit(1);
	} else {
		char** lines = NULL;
		size_t count = 0;
		char buf[1024]; // string buffer
		
		while(fgets(buf, sizeof(buf), file)) {
			char* line = (char*)malloc(strlen(buf) + 1);

			if(line == NULL) {
				_set_errno(12);
				perror("Failed to allocate memory for line");
				exit(1);
			}

			strcpy_s(line, strlen(buf) + 1, buf);

			char** tmp = realloc(lines, (count + 1) * sizeof(char*));

			if(tmp == NULL) {
				free(line);
				_set_errno(12);
				perror("Failed to reallocate lines");
				exit(1);
			}

			lines = tmp;
			lines[count] = line;
			count++;
		}

		fclose(file);

		// to prevent any issues with allocating 0 bytes
		//   for the long array, allocate at least one long
		if(count == 0) { count = 1; }

		results = (ResultArray*)malloc((count * sizeof(long)) + sizeof(ResultArray));

		if(results == NULL) {
			_set_errno(12);
			perror("Failed to allocate memory for results array");
			exit(1);
		}

		memset(results, 0, (count * sizeof(long)) + sizeof(size_t));
		results->results = (long*)((unsigned char*)results + sizeof(ResultArray));
		results->length = count;

		// print expression with highlighting
		// operators are highlighted yellow, numbers are highlighted green, everything else is cyan
		// operators: = + - * / % ^
		// only integers allowed
		
		for(size_t i = 0; i < results->length; i++) {
			results->results[i] = parse_expr(lines[i]);
		}

		// CLEANUP
		for(size_t i = 0; i < count; i++) {
			free(lines[i]);
		}
		free(lines);
	}
	return results;
}

void skip_whitespace(Parser* parser) {
	while (isspace((unsigned char)parser->input[parser->pos])) {
		parser->pos++;
	}
}

bool match(Parser* parser, char c) {
	if (parser->input[parser->pos] == c) {
		parser->pos++;
		return true;
	}
	return false;
}

void syntax_error(Parser* parser, const char* message) {
	fprintf(
		stderr,
		"Syntax error at position %zu: %s\n",
		parser->pos,
		message
	);
	fprintf(stderr, "    %s\n    ", parser->input);
	for (size_t i = 0; i < parser->pos; i++) {
		fputc(' ', stderr);
	}
	fprintf(stderr, "^\n");
	exit(EXIT_FAILURE);
}

long parse_expr(char* expr) {
	syntax_print(expr);

	Parser parser = {
		.input = expr,
		.pos = 0
	};

	long result = parse_comparison(&parser);

	skip_whitespace(&parser);

	// double check to make sure no leftover characters
	if (parser.input[parser.pos] != '\0') {
		syntax_error(&parser, "Unexpected character");
	}

	return result;
}

long parse_comparison(Parser* parser) {
	long left = parse_addition(parser);

	while (true) {
		skip_whitespace(parser);

		if (match(parser, '=')) {
			long right = parse_addition(parser);
			left = (left == right);
		} else if (match(parser, '>')) {
			long right = parse_addition(parser);
			left = (left > right);
		} else if (match(parser, '<')) {
			long right = parse_addition(parser);
			left = (left < right);
		} else {
			break;
		}
	}
	return left;
}

long parse_addition(Parser* parser) {
	long left = parse_multiplication(parser);
	while (true) {
		skip_whitespace(parser);
		if (match(parser, '+')) {
			long right = parse_multiplication(parser);
			left += right;
		} else if (match(parser, '-')) {
			long right = parse_multiplication(parser);
			left -= right;
		} else {
			break;
		}
	}
	return left;
}

long nCr(long left, long right) {
	double sum = 1;
	
	for (size_t i = 1; i <= right; i++) {
		sum = sum * (left - right + i) / i;
	}

	return (long)sum;
}

long parse_multiplication(Parser* parser) {
	long left = parse_unary(parser);

	while (true) {
		skip_whitespace(parser);
		if (match(parser, '*')) {
			long right = parse_unary(parser);
			left *= right;
		}	else if (match(parser, '/')) {
			long right = parse_unary(parser);
			if (right == 0) {
				syntax_error(parser, "Division by zero");
			}
			left /= right;
		} else if (match(parser, '%')) {
			long right = parse_unary(parser);
			if (right == 0) {
				syntax_error(parser, "Modulo by zero");
			}
			left %= right;
		} else if (match(parser, 'c')) {
			long right = parse_unary(parser);
			left = nCr(left, right);
		} else {
			break;
		}
	}

	return left;
}

long parse_unary(Parser* parser) {
	skip_whitespace(parser);
	if (match(parser, '-')) {
		return -parse_unary(parser);
	}
	return parse_power(parser);
}

long parse_power(Parser* parser) {
	long base = parse_primary(parser);

	skip_whitespace(parser);

	if (match(parser, '^')) {
		long exponent = parse_power(parser);
		if (exponent < 0) {
			syntax_error(parser, "Negative exponent");
		}

		long result = 1;
		
		for (long i = 0; i < exponent; i++) {
			result *= base;
		}
		return result;
	}   

	return base;
}

long parse_primary(Parser* parser) {
	skip_whitespace(parser);

	char c = parser->input[parser->pos];

	// parenthesis
	if (match(parser, '(')) {
		long result = parse_comparison(parser);
		skip_whitespace(parser);
		if (!match(parser, ')')) {
			syntax_error(parser, "Expected ')'");
		}
		return result;
	}

	// abs() 
	if (match(parser, '|')) {
		long result = parse_comparison(parser);
		skip_whitespace(parser);
		if (!match(parser, '|')) {
			syntax_error(parser, "Expected '|'");
		}
		return result < 0 ? -result : result;
	}

	// ints 
	if (isdigit((unsigned char)c)) {
		long result = 0;
		while (isdigit((unsigned char)parser->input[parser->pos])) {
			int digit = parser->input[parser->pos] - '0';
			result = result * 10 + digit;
			parser->pos++;
		}
		return result;
	}

	syntax_error(parser, "Expected integer, '(' or '|'");
	UNREACHABLE
}

// SYNTAX HIGHLIGHTING

bool is_operator(char c) {
	return c == '=' || c == '<' || c == '>' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == 'c' || c == '^';
}

#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void syntax_print(char* expr) {
	printf("Expression: ");

	for (size_t i = 0; expr[i] != '\0'; ) {
		char c = expr[i];

		if (isdigit(c)) { // integers
			printf(GREEN);
			while (isdigit(expr[i])) {
				putchar(expr[i]);
				i++;
			}
			printf(RESET);
		} else if (is_operator(c)) {
			printf(YELLOW"%c"RESET,c);
			i++;
		} else { // catch-all
			printf(CYAN"%c"RESET, c);
			i++;
		}
	}

	printf("\n");
}
