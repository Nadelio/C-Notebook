#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// returns a pseudo-random number between min (inclusive) and max (exclusive).
int get_random(int min, int max) {
	return (rand() % max) + min;
}


int main() {
	srand(time(NULL));
	int secret = get_random(1, 101); // random number between 1 and 100
	
	int guess; // declare the user's guess variable to keep track of later
	
	printf("Please type a number between 1 and 100.\n");
	
	while(guess != secret) {
		int result = scanf_s("%d", &guess); // result is the success/fail result of scanf_s("%d", &guess)
																				// the success value is stored in guess

		if(result == EOF) { // EOF is the error code for nothing being given to scanf_s(), if so, tell the player
			printf("Received no input, try again!");
		}

		if(result == 0) { // if garbage string, consume stdin until the string is gone
			while(fgetc(stdin) != '\n');
		}

		// hints
		if(guess > secret) {
			printf("Lower!\n");
		} else if(guess < secret) {
			printf("Higher!\n");
		}
	}

	printf("You guessed correctly! The number was: %d", secret);
}
