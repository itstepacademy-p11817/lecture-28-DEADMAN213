#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <stdbool.h>

#define NBYTES 8
#define CHOICE 4

typedef enum { RED, WHITE, BLACK, GREEN } TColor;
const char* colors[] = { "RED","WHITE","BLACK","GREEN" };

typedef enum { BMW, MERS, VOLGA, JEEP } TModel;
const char* models[] = { "BMW","MERS","VOLGA","JEEP" };

typedef struct {
	TColor color;
	TModel model;
	bool numtype;
	union {
		int64_t intnum;
		char bytes[NBYTES];
	};
} TMachine;


void printMachine(TMachine* vehicle) {
	system("cls");

	printf("Machine: %s.\n", models[vehicle->model]);
	printf("Color: %s.\n", colors[vehicle->color]);
	printf("Number: ");
	vehicle->numtype ? printf("%s.\n", vehicle->bytes) : printf("%lli.\n", vehicle->intnum);
}

void passInput() {
	while (getchar() != '\n')
		continue;
}

uint8_t menu(TMachine* val) {
	uint8_t ch = 0;

	system("cls");
	printMachine(val);

	printf("Menu:\n");
	printf("1 - Input machine.\n");
	printf("2 - Print machine.\n");
	printf("3 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void inputMachine(TMachine* vehicle) {
	uint8_t ch = 0;

	system("cls");
	
	printf("Color: \n");
	for (uint8_t i = 0; i < CHOICE; i++) {
		printf("%hhu - %s.\n", i +1, colors[i]);
	}
	printf("Input color: ");
	scanf("%hhu", &ch);
	vehicle->color = ch - 1;

	printf("Type: \n");
	for (uint8_t i = 0; i < CHOICE; i++) {
		printf("%hhu - %s.\n", i + 1, models[i]);
	}
	printf("Input type: ");
	scanf("%hhu", &ch);
	vehicle->model = ch - 1;

	printf("Type of number: \n");
	printf("1 - number.\n");
	printf("2 - string.\n");
	printf("Input type of number: ");
	scanf("%hhu", &ch);
	vehicle->numtype = ch - 1;

	if (vehicle->numtype) {
		printf("Input string: ");
		scanf("%s", vehicle->bytes);
	}
	else {
		printf("Input number: ");
		scanf("%lli", &(vehicle->intnum));
	}
}

int main(void) {
	TMachine car = { 0 };
	uint8_t ch = 0;

	while ((ch = menu(&car)) != 3) {
		switch (ch) {
		case 1:
			inputMachine(&car);
			break;

		case 2:
			printMachine(&car);
			break;

		default:
			printf("Wrong input.\n");
			passInput();
		}

		printf("Press any key.\n");
		_getch();
	}

	return 0;
}