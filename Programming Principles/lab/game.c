#include <stdio.h>
#include <stdbool.h>

int main(void) {
	int age, weight;
	printf("Enter your child's age: ");
	scanf_s("%d", &age);
	printf("Enter your child's weight: ");
	scanf_s("%d", &weight);

	bool cannot_play = false;
	if(age > 18) {
		cannot_play = true;
	}

	if(weight < 130) {
		cannot_play = true;
	}

	if(cannot_play) printf("Your child cannot play.");
	else printf("Your child can play.");

	return 0;
}
