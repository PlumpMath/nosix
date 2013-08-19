#ifndef PORTIO_H
#define PORTIO_H

#include <stdint.h>

static inline
void out8(uint16_t port, uint8_t byte) {
	asm volatile("outb %b[byte], %w[port]"
		:: [byte] "a" (byte), [port] "Nd" (port));
}

static inline
uint8_t in8(uint16_t port) {
	uint8_t ret;
	asm volatile("inb %w[port], %b[ret]"
		: [ret] "=a" (ret)
		: [port] "Nd" (port));
	return ret;
}

#endif
