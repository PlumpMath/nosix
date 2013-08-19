#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include "klog.h"

typedef struct serial_out_t serial_out_t;
struct serial_out_t {
	output_t out;
	uint16_t port;
};

#define COM1 0x3f8

serial_out_t serial_init(uint16_t port);

void serial_putc(output_t *port, uint8_t byte);
	
#endif
