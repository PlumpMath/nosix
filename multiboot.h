#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct mboot_info_t mboot_info_t;
struct mboot_info_t {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	/* there are more fields, but we aren't interested. (yet.) */
};

#endif
