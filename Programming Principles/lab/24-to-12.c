#include <stdio.h>
#include <errno.h>

int main(void) {
	int hours_24;
	int minutes_24;

	printf("Enter your 24-hour timestamp as <hours>:<minutes>: ");
	scanf_s("%d:%d", &hours_24, &minutes_24);

	if(hours_24 > 24 || minutes_24 > 59) {
		_set_errno(22);
		perror("Invalid hours or minutes");
		return 1;
	}

	if(hours_24 < 0 || minutes_24 < 0) {
		_set_errno(22);
		perror("Invalid hours or minutes");
		return 1;
	}

	char* time_of_day = hours_24 >= 12? "PM" : "AM";
	int hours_12 = hours_24 > 12? hours_24 - 12 : hours_24;
	if(hours_12 == 0) hours_12 = 12;

	printf("12-hour format: %02d:%02d%s\n", hours_12, minutes_24, time_of_day);
	return 0;
}
