#include "serial.h"
#include "portio.h"

#define DLAB_SET (1<<7)
#define DLAB_CLEAR 0
#define DATABITS_8 0x3
#define NO_PARITY 0
#define LINE_READY_STATUS (1<<5)

/* All of the following constants are addresses relative to the serial port
 * address: */
/* valid when DLAB = 0 : */
#define DATA_REG 0
#define INT_ENABLE 1
/* valid when DLAB = 1 : */
#define BAUD_DIV_LSB 0
#define BAUD_DIV_MSB 1
/* valid regardless of DLAB: */
#define INT_ID_FIFO 2
#define LINE_CNTL_REG 3 /* DLAB is the MSB */
#define MODEM_CNTL_REG 4
#define LINE_STATUS_REG 5
#define MODEM_STATUS_REG 6
#define SCRATCH_REG 7

void serial_init(uint16_t port) {
	out8(port+INT_ENABLE, 0); /* disable interrupts on the device. */
	out8(port+LINE_CNTL_REG, DLAB_SET); /* enable DLAB */
	/* set baud rate divisor: */
	out8(port+BAUD_DIV_LSB, 0x3);
	out8(port+BAUD_DIV_MSB, 0x0);
	/* clear DLAB, ask for 8 bit chars with no pairty: */
	out8(port+LINE_CNTL_REG, DLAB_CLEAR | DATABITS_8 | NO_PARITY);
}

void serial_putc(uint16_t port, uint8_t byte) {
	while(!(in8(port+LINE_STATUS_REG) & LINE_READY_STATUS));
	out8(port, byte);
}
