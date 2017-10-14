#include <stdio.h>
#include <inttypes.h>

int main(void) {
	union number {
		int32_t sign;
		uint32_t usign;
	} val;

	printf("Input signed value: ");
	scanf_s("%i", &(val.sign));
	printf("Signed value: %i.\n", val.sign);
	printf("Unsigned value: %u.\n", val.usign);

	printf("\nInput unsigned value: ");
	scanf_s("%ui", &(val.usign));
	printf("Signed value: %i.\n", val.sign);
	printf("Unsigned value: %u.\n", val.usign);

	return 0;
}