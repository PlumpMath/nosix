#include "multiboot.h"
#include "serial.h"

/* TODO: find a good place for this. we'll want more formatted io routines
 * eventually, this should be located with the rest of them. */
void print_hex32(uint16_t port, uint32_t n) {
	uint32_t mask = 0x10000000;
	int i;
	uint8_t digit;
	for(i = 0; i < 8; i++) {
		digit = "0123456789abcdef"[n/mask];
		serial_putc(port, digit);
		n %= mask;
		mask /= 0x10;
	}
}

void main(mboot_info_t *mboot) {
	serial_init(COM1);
	print_hex32(COM1, mboot->mem_lower);
	serial_putc(COM1, '\n');
	print_hex32(COM1, mboot->mem_upper);
	serial_putc(COM1, '\n');
}
