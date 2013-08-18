#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct mboot_info_t mboot_info_t;
struct mboot_info_t {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	uint32_t syms[4];
	uint32_t mmap_length;
	uint32_t mmap_addr;
	/* there are more fields, but we aren't interested. (yet.) */
};

typedef struct mmap_t mmap_t;
struct mmap_t {
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
};

#endif
