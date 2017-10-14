#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>
#include <stdbool.h>

#define NBYTES 4

typedef union {
	int32_t sign;
	bool bytes[NBYTES];
} TNumber;

uint8_t menu(TNumber val) {
	uint8_t ch = 0;

	system("cls");
	printf("Number: %hhu.\n\n", val.sign);

	printf("Menu:\n");
	printf("1 - Input integer value.\n");
	printf("2 - Count zero bytes.\n");
	printf("3 - Print info about bytes (zero/nonzero).\n");
	printf("4 - Exit.\n");
	printf("Input choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void passInput() {
	while (getchar() != '\n')
		continue;
}

uint8_t inputValue(TNumber* num) {
	printf("Inpur value: ");
	return scanf("%i", &(num->sign));
}

uint8_t zeroBytes(TNumber* num) {
	uint8_t n = 0;

	for (uint8_t i = 0; i < NBYTES; i++) {
		if (num->bytes[i] == 0) {
			n += 1;
		}
	}

	return n;
}

void infoBytes(TNumber* num) {
	for (uint8_t i = 0; i < NBYTES; i++) {
		printf("%hhu byte is %s%s", i, num->bytes[i] == 0 ? "zero" : "not a zero", ".\n");
	}
}

int main(void) {
	TNumber number = { 0 };
	uint8_t ch = 0;

	while ((ch = menu(number)) != 4) {
		switch (ch) {
		case 1:
			if (!inputValue(&number)) {
				printf("Wrong input.\n");
			}
			passInput();
			break;

		case 2:
			printf("Number of a zero bytes: %hhu.\n", zeroBytes(&number));
			break;

		case 3:
			printf("Info about number:\n");
			infoBytes(&number);
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