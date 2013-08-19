#ifndef KLOG_H
#define KLOG_H

#include <stdint.h>

/* logging/debugging routines for the kernel. */

/* a destination for logging information */
typedef struct output_t output_t;
struct output_t {
	void (*putc)(output_t *, uint8_t byte);
};

typedef enum{
	KLOG_DEBUG = 100
} loglevel_t;

/* The default destination for kernel daiagnostic logging */
extern output_t *stdklog;

/* printf-like logging function. if LOGLEVEL < level, then this does nothing.
   (LOGLEVEL should be defined in CFLAGS to a valid loglevel_t, above. */
/* right now the functionality isn't as complete as printf's. only the
 * specifiers p, u, s, and c are implemented, and no additonal flags,
 * precision, etc. is supported.  */
void klogf(loglevel_t level, char *fmt, ...);

#endif
