#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#define COM1 0x3f8

void serial_init(uint16_t port);

void serial_putc(uint16_t port, uint8_t byte);
	
#endif
