#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <stdbool.h>

#define CHOICE 3
#define CREATURES 10

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
		printf("%31s%3.2lf km/h.\n", "Height: ", creature->feature.height);
		break;

	case 1:
		printf("%29s%s.\n", "Type: ", creature->feature.mammals ? "Mammals" : "Non mammals");
		break;

	case 2:
		printf("%27s%llu.\n", "IQ: ", creature->feature.iq);
		break;
	}
}

void printCreatures(TCreature* creature) {
	system("cls");
	printHeader();

	for (uint8_t i = 0; i < CREATURES; i++) {
		printCreature(creature + i);
	}
}

TFeature creatureType(TType type) {
	TFeature temp = { 0.0 };

	switch (type) {
	case 0:
		printf("Height (m): ");
		scanf("%lf", &(temp.height));
		break;

	case 1:
		printf("Type (1 - mammals, 0 - non mammals): ");
		scanf("%i", &(temp.mammals));
		break;

	case 2:
		printf("IQ: ");
		scanf("%llu", &(temp.iq));
		break;
	}

	return temp;
}

void inputCreature(TCreature* creature) {
	int8_t ch = 0;

	printf("Speed (km/h): ");
	scanf("%hhu", &(creature->speed));

	printf("Type: \n");
	for (uint8_t i = 0; i < CHOICE; i++) {
		printf("%hhu - %s.\n", i + 1, types[i]);
	}
	printf("Input type: ");
	scanf("%hhu", &ch);
	creature->type = ch - 1;

	creature->feature = creatureType(creature->type);
}

void inputCreatures(TCreature* creature) {
	for (uint8_t i = 0; i < CREATURES; i++) {
		system("cls");
		printf("Input %hhu creature:\n", i);

		inputCreature(creature + i);
	}
}

void editCreature(TCreature* creature) {
	system("cls");
	inputCreature(creature);
}

bool findCreature(TCreature* creature, TFeature* feature) {
	bool flag = false;

	printHeader();
	for (uint8_t i = 0; i < CREATURES; i++) {
		if ((creature + i)->feature.iq == feature->iq) {
			printCreature(creature + i);
			flag = true;
		}
	}

	return flag;
}

void passInput() {
	while (getchar() != '\n')
		continue;
}

uint8_t menu(TCreature* creature) {
	uint8_t ch = 0;

	system("cls");
	printHeader();
	printCreatures(creature);

	printf("Menu:\n");
	printf("1 - Input information.\n");
	printf("2 - Edit information.\n");
	printf("3 - Print information.\n");
	printf("4 - Find creature.\n");
	printf("5 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

int main(void) {
	TCreature creatures[CREATURES] = { 0 };
	uint8_t ch = 0;

	while ((ch = menu(creatures)) != 5) {
		switch (ch) {
		case 1:
			inputCreatures(creatures);
			break;

		case 2: {
			uint8_t ch = 0;
			printf("Input number of record to edit: ");
			scanf("%hhu", &ch);

			editCreature(creatures + ch - 1);

			break;
		}

		case 3:
			printCreatures(creatures);
			break;

		case 4: {
			TFeature temp = { 0.0 };
			uint8_t ch = 0;

			printf("Type: \n");
			for (uint8_t i = 0; i < CHOICE; i++) {
				printf("%hhu - %s.\n", i + 1, types[i]);
			}
			printf("Input type: ");
			scanf("%hhu", &ch);

			temp = creatureType(ch - 1);

			if (!findCreature(creatures, &temp)) {
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