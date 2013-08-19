#include "klog.h"
#include <stdarg.h>

output_t *stdklog;

/* outputs the single byte `byte` */
static
void klog_putc(uint8_t byte) {
	stdklog->putc(stdklog, byte);
}

/* outputs the null terminated string `s`. */
static
void kputs(char *s) {
	while(*s) {
		klog_putc(*s);
		s++;
	}
}

/* outputs the number `num` in base `base`, where 2 <= base <= 16. */
void klog_putnum(unsigned long long num, int base, int min_digits) {
	int num_digits = 1;
	unsigned long long mask = base;
	int i;
	while(num/mask >= base || num_digits < min_digits) {
		num_digits++;
		mask *= base;
	}
	for(i = 0; i < num_digits; i++) {
		mask /= base;
		klog_putc("0123456789abcdef"[num/mask]);
		num %= mask;
	}
}

void klogf(loglevel_t level, char *fmt, ...) {
	if(level <= LOGLEVEL) {
		uintptr_t num_val;
		int c;
		char *s;
		va_list ap;
		va_start(ap, fmt);
		while(*fmt) {
			if(*fmt == '%') {
			fmt++;
			switch(*fmt) {
			case '%':
				klog_putc('%');
				break;
			case 'p':
				num_val = va_arg(ap, uintptr_t);
				kputs("0x");
				klog_putnum(num_val, 16, 2*sizeof(uintptr_t));
				break;
			case 'u':
				num_val = va_arg(ap, uintptr_t);
				klog_putnum(num_val, 10, 0);
				break;
			case 'c':
				c = va_arg(ap, int);
				klog_putc(c);
				break;
			case 's':
				s = va_arg(ap, char *);
				kputs(s);
				break;
			}
			} else {
				klog_putc(*fmt);
			}
			fmt++;
		}

	}
}

