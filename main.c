#include "serial.h"

void main(void) {
	serial_init(COM1);
	serial_putc(COM1, 'A');
}
