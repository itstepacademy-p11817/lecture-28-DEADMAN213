#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <stdbool.h>

#define CHOICE 3

typedef enum { BIRD, ANIMAL, HUMAN } TType;
const char* types[] = { "BIRD","ANIMAL","HUMAN" };

typedef union {
	double height;
	bool mammals;
	uint64_t iq;
} TFeature;

typedef struct {
	uint8_t speed;
	TType type;
	TFeature feature;
} TCreature;


void printHeader() {
	printf("%10s", "Speed");
	printf("%20s", "Type");
	printf("%30s", "Feature");
	printf("\n");
}

void printCreature(TCreature* creature) {
	printf("%10hhu", creature->speed);
	printf("%20s", types[creature->type]);

	switch (creature->type) {
	case 0: 
		printf("%31s%lf km.\n", "Height: ", creature->feature.height);
		break;

	case 1:
		printf("%29s%s.\n", "Type: ", creature->feature.mammals ? "Mammals": "Non mammals");
		break;

	case 2:
		printf("%27s%llu.\n", "IQ: ", creature->feature.iq);
		break;
	}
}

void inputCreature(TCreature* creature) {
	int8_t ch = 0;

	printf("Speed: ");
	scanf("%hhu", &(creature->speed));

	printf("Type: \n");
	for (uint8_t i = 0; i < CHOICE; i++) {
		printf("%hhu - %s.\n", i + 1, types[i]);
	}
	printf("Input type: ");
	scanf("%hhu", &ch);
	creature->type = ch - 1;

	switch (creature->type) {
	case 0:
		printf("Height: ");
		scanf("%lf", &(creature->feature.height));
		break;

	case 1:
		printf("Type (1 - mammals, 0 - non mammals): ");
		scanf("%i", &(creature->feature.mammals));
		break;

	case 2:
		printf("IQ: ");
		scanf("%llu", &(creature->feature.iq));
		break;
	}
}

void passInput() {
	while (getchar() != '\n')
		continue;
}

uint8_t menu(TCreature* creature) {
	uint8_t ch = 0;

	system("cls");
	printHeader();
	printCreature(creature);

	printf("Menu:\n");
	printf("1 - Input information.\n");
	printf("2 - Print information.\n");
	printf("3 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

int main(void) {
	TCreature creature = { 0 };
	uint8_t ch = 0;

	while ((ch = menu(&creature)) != 3) {
		switch (ch) {
		case 1:
			system("cls");
			inputCreature(&creature);
			break;

		case 2:
			system("cls");
			printHeader();
			printCreature(&creature);
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