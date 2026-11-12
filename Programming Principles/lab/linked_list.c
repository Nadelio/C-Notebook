#include <stdlib.h>
#include <stdio.h>

struct Node {
	struct Node* next;
	int element;
};

typedef struct {
	int value;
	enum {
		OUT_OF_BOUNDS,
		FAILED_TO_ALLOC,
		NONEXISTENT_ELEMENT,
		EMPTY_LIST,
		UNIMPLEMENTED,
		OK
	} result;
} LL_RESULT;

struct Node* start_ll(int value);
size_t length(struct Node* ll_first);
LL_RESULT last(struct Node* ll_first);
LL_RESULT nth(struct Node* ll_first, size_t index);
LL_RESULT insert_at_nth(struct Node* ll_first, size_t index, int value);
LL_RESULT remove_nth(struct Node* ll_first, size_t index);
LL_RESULT pop(struct Node* ll_first);
LL_RESULT push(struct Node* ll_first, int value);

void handle_error(LL_RESULT result);

int main(void) {
	struct Node* first = start_ll(0);
	printf("First Element: %d\n", first->element);
	
	LL_RESULT result = push(first, 1);
	if(result.result != OK) {
		handle_error(result);
	}

	result = nth(first, 0);
	if(result.result != OK) {
		handle_error(result);
	} else {
		printf("Second Element: %d\n", result.value);
	}

	result = last(first);
	int last_node = -1;
	if(result.result != OK) {
		handle_error(result);
	} else {
		last_node = result.value;
	}
	printf("Last Element: %d\n", last_node);

	push(first, 10);
	printf("Pushed 10 to linked list.\n");
	result = pop(first);
	int popped_value = -1;
	if(result.result != OK) {
		handle_error(result);
	} else {
		popped_value = result.value;
	}
	printf("Popped Value: %d\n", popped_value);

	return 0;
}

void handle_error(LL_RESULT result) {
	switch(result.result) {
		case OUT_OF_BOUNDS:
			perror("Out of bounds.");
			break;
		case FAILED_TO_ALLOC:
			perror("Failed to allocate new node.");
			break;
		default: // OK
			break;
	}
}

struct Node* start_ll(int value) {
	struct Node* start = (struct Node*)malloc(sizeof(struct Node));
	if(start == NULL) {
		perror("Failed to allocate new node.");
		return NULL;
	}

	start->next = NULL;
	start->element = value;
	return start;
}

LL_RESULT push(struct Node* ll_first, int value) {
	struct Node* next = (struct Node*)malloc(sizeof(struct Node));

	if(next == NULL) {
		return (LL_RESULT){.value = -1, .result = FAILED_TO_ALLOC};
	}

	next->next = NULL;
	next->element = value;

	struct Node* last = NULL;
	last = ll_first->next;
	if(last == NULL) ll_first->next = next;
	else {
		while(last->next != NULL) last = last->next;
	}

	last->next = next;

	return (LL_RESULT){.value = value, .result = OK};
}

size_t length(struct Node* ll_first) {
	size_t len = 1; // always at least 1 node (the first node)
	for(struct Node* curr = ll_first; curr != NULL; curr = curr->next) {
		len++;
	}
	return len;
}

LL_RESULT last(struct Node* ll_first) {
	struct Node* curr = ll_first;
	for(; curr != NULL; curr = curr->next);
	return (LL_RESULT){ .value = curr->element, .result = OK };
}

LL_RESULT nth(struct Node* ll_first, size_t index) {
	// bounds check
	size_t len = length(ll_first);
	if(index + 1 > len) return (LL_RESULT){ .value = -1, .result = OUT_OF_BOUNDS };

	struct Node* curr = ll_first;
	for(size_t i = 0; i < index || curr->next != NULL; i++) {
		curr = curr->next;
	}
	return (LL_RESULT){ .value = curr->element, .result = OK };
}

LL_RESULT insert_at_nth(struct Node* ll_first, size_t index, int value) {
	size_t len = length(ll_first);
	if(index + 1 > len) return (LL_RESULT){ .value = -1, .result = OUT_OF_BOUNDS };
	struct Node* curr = ll_first;
	for(size_t i = 0; i < index || curr->next != NULL; i++) {
		curr = curr->next;
	}

	struct Node* inserted = (struct Node*)malloc(sizeof(struct Node));
	inserted->next = curr->next;
	curr->next = inserted;
	inserted->element = value;
	
	return (LL_RESULT){ .value = value, .result = OK };
}

LL_RESULT remove_nth(struct Node* ll_first, size_t index) {
	size_t len = length(ll_first);
	
	if(index + 1 > len) return (LL_RESULT){ .value = -1, .result = OUT_OF_BOUNDS };

	struct Node* curr = ll_first;
	for(size_t i = 0; i < index || curr->next != NULL; i++) {
		curr = curr->next;
	}

	struct Node* temp = curr->next->next;
	free(curr->next);
	curr->next = temp;

	return (LL_RESULT){ .value = 0, .result = OK };
}

LL_RESULT pop(struct Node* ll_first) {
	size_t len = length(ll_first);
	return remove_nth(ll_first, len);
}
