#include <stdio.h>

enum VehicleTypes {
	CAR = 1, TRUCK, BIKE
};

int main(void) {
	enum VehicleTypes vehicle; 

	scanf("%d", &vehicle);

	switch(vehicle) {
		case CAR:
			printf("Car!\n");
			break;
		case TRUCK:
			printf("Truck!\n");
			break;
		case BIKE:
			printf("Bike!\n");
			break;
		default:
			printf("Unknown Vehicle Type!\n");
			return 1; // failure, invalid data
	}

	return 0;
}
