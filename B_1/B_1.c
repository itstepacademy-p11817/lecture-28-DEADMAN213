#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <stdbool.h>

#define NBYTES 8
#define CHOICE 4
#define CARS 10

typedef enum { RED, WHITE, BLACK, GREEN } TColor;
const char* colors[] = { "RED","WHITE","BLACK","GREEN" };

typedef enum { BMW, MERS, VOLGA, JEEP } TModel;
const char* models[] = { "BMW","MERS","VOLGA","JEEP" };

typedef union {
	uint64_t intnum;
	char bytes[NBYTES];
} TNumber;

typedef struct {
	TColor color;
	TModel model;
	uint8_t numtype;
	TNumber number;
} TMachine;


void printHeader() {
	printf("%10s", "Machine");
	printf("%20s", "Color");
	printf("%30s", "Number");
	printf("\n");
}

void printMachine(TMachine* vehicle) {
	printf("%10s", models[vehicle->model]);
	printf("%20s", colors[vehicle->color]);
	vehicle->numtype == 1 ? printf("%30llu\n", vehicle->number.intnum) : printf("%30s\n", vehicle->number.bytes);
}

void printMachines(TMachine* vehicle) {
	system("cls");
	printHeader();

	for (uint8_t i = 0; i < CARS; i++) {
		printMachine(vehicle + i);
	}
}

uint8_t numberType() {
	uint8_t ch = 0;

	printf("Type of number: \n");
	printf("1 - number.\n");
	printf("2 - string.\n");
	printf("Input type of number: ");
	scanf("%hhu", &ch);
	
	return ch;
}

void inputMachine(TMachine* vehicle) {
	uint8_t ch = 0;

	printf("Color: \n");
	for (uint8_t i = 0; i < CHOICE; i++) {
		printf("%hhu - %s.\n", i + 1, colors[i]);
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

	if ((vehicle->numtype = numberType()) == 2) {
		printf("Input string: ");
		scanf("%s", vehicle->number.bytes);
	}
	else {
		printf("Input number: ");
		scanf("%llu", &(vehicle->number.intnum));
	}
}

void inputMachines(TMachine* vehicle) {
	for (uint8_t i = 0; i < CARS; i++) {
		system("cls");
		printf("Input %hhu car:\n", i);

		inputMachine(vehicle + i);
	}
}

void passInput() {
	while (getchar() != '\n')
		continue;
}

uint8_t menu(TMachine* val) {
	uint8_t ch = 0;

	system("cls");
	printMachines(val);

	printf("Menu:\n");
	printf("1 - Input machine.\n");
	printf("2 - Print machine.\n");
	printf("3 - Search number.\n");
	printf("4 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

bool searchNumber(TMachine* vehicles, TNumber* num) {
	bool flag = false;

	for (uint8_t i = 0; i < CARS; i++) {
		if (num->intnum == (vehicles + i)->number.intnum) {
			printMachine(vehicles + i);
			flag = true;
		}
	}

	return flag;
}

int main(void) {
	TMachine car[10] = { 0 };
	uint8_t ch = 0;

	while ((ch = menu(car)) != 4) {
		switch (ch) {
		case 1:
			inputMachines(car);
			break;

		case 2:
			printMachines(car);
			break;

		case 3: {
			TNumber temp = { 0 };

			if (numberType() == 2) {
				printf("Input string: ");
				scanf("%s", temp.bytes);
			}
			else {
				printf("Input number: ");
				scanf("%llu", &temp.intnum);
			}

			if (!searchNumber(car, &temp)) {
				printf("No match found.\n");
			}

			break;
		}
		
		default:
			printf("Wrong input.\n");
			passInput();
		}

		printf("Press any key.\n");
		_getch();
	}

	return 0;
}