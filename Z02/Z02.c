#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <inttypes.h>

#define NBYTES 4

typedef union {
	int32_t sign;
	char bytes[NBYTES];
} TNumber;

uint8_t menu(int32_t val) {
	uint8_t ch = 0;

	system("cls");
	printf("Value: %i.\n\n", val);

	printf("Menu:\n");
	printf("1 - Input integer value.\n");
	printf("2 - Print bytes of the value.\n");
	printf("3 - Print byte of the value.\n");
	printf("4 - Print bytes of the value in digit and hex system.\n");
	printf("5 - Exit.\n");
	printf("Choice: ");
	scanf("%hhu", &ch);

	return ch;
}

uint8_t inputValue(TNumber* num) {
	printf("Inpur value: ");
	return scanf("%i", &(num->sign));
}

int8_t printByte(TNumber* num, uint8_t btnum) {
	if (btnum < 1 || btnum > NBYTES) {
		return 0;
	}

	printf("%5hhi", num->bytes[btnum - 1]);

	return 1;
}

void printBytes(TNumber* num) {
	for (uint8_t i = 0; i < NBYTES; i++) {
		printByte(num, i + 1);
	}
	printf("\n");
}

void printDigits(TNumber* num) {
	for (uint8_t i = 0; i < NBYTES; i++) {
		uint8_t mask = 128;

		printf(" ");
		for (uint8_t j = 0; j < 8; j++) {
			printf(mask & num->bytes[i] ? "1" : "0");
			mask >>= 1;
		}
	}

	printf(".\n");
}

void printHex(TNumber* num) {
	for (uint8_t i = 0; i < NBYTES; i++) {
		printf(" %x", num->bytes[i]);
	}
	printf("\n");
}

int main(void) {
	TNumber number = {0};
	uint8_t ch = 0;

	while ((ch = menu(number.sign)) != 5) {
		switch (ch) {
		case 1:
			inputValue(&number);
			break;

		case 2:
			printf("Bytes of the number: ");
			printBytes(&number);
			break;

		case 3: {
			uint8_t num = 0;
			printf("Input number of a byte: ");
			scanf("%hhu", &num);

			printf("Byte number %hhu: ", num);
			if (!printByte(&number, num)) {
				printf("Wrong input.\n");
			}
			printf(".\n");
			break;
		}
		
		case 4:
			printf("Bits of the number: ");
			printDigits(&number);

			printf("Hex bytes of the number: ");
			printHex(&number);
			break;

		default:
			printf("Wrong input!\n");
		}

		printf("Done. Press any key.\n");
		_getch();
	}

	return 0;
}