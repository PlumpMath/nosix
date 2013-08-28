#include "gdt.h"
#include <stdint.h>

#define GDT_S_SYSTEM 0
#define GDT_S_CODE_OR_DATA 1

#define GDT_DB_SEG16 0
#define GDT_DB_SEG32 1

#define GDT_G_BYTE 0
#define GDT_G_PAGE 1

#define GDT_TYPE_RDEX ((1<<3) | (1<<1))
#define GDT_TYPE_RDWR (1<<1)

/*
	see the intel system programming guide, section 3.4.5: "segment
	descriptors" for a full explanation of this structure.
*/
typedef struct gdt_t gdt_t;
struct gdt_t {
	unsigned int limit_lo  : 16; 
	unsigned int base_lo   : 24; 
	unsigned int type      :  4; /* segment type */
	unsigned int s         :  1; /* descriptor type */
	unsigned int dpl       :  2; /* descriptor privilege level */
	unsigned int p         :  1; /* present? */
	unsigned int limit_hi  :  4;
	unsigned int avl       :  1; /* available */
	unsigned int l         :  1; /* 64-bit code segment (i.e. Long mode) */
	unsigned int db        :  1; /* default operation size (16 vs 32 bit) */
	unsigned int g         :  1; /* granularity */
	unsigned int base_hi   :  8;
	
}__attribute__((packed));
_Static_assert(sizeof(gdt_t) == 8, "sizeof(gdt_t) != 8");

typedef struct gdt_ptr_t gdt_ptr_t;
struct gdt_ptr_t {
	uint16_t len;
	uint32_t addr;
}__attribute__((packed));
_Static_assert(sizeof(gdt_ptr_t) == 6, "sizeof(gdt_ptr_t) != 6");

/* convenience macros for setting the various fragments of base & limit in one
 * place. */
#define BASE(base) \
	.base_lo = ((base) & 0x00ffffff), \
	.base_hi = (((base)>>24) & 0xff)

#define LIMIT(limit) \
	.limit_lo = ((limit) & 0xffff), \
	.limit_hi = (((limit)>>16) & 0xf)

static gdt_t gdt[] = {
	/* mandatory null segment: */
	{},
	/* privileged code segment: */
	{
		BASE(0),
		LIMIT(-1),
		.type = GDT_TYPE_RDEX,
		.s = 1,
		.dpl = 0,
		.p = 1,
		.avl = 0,
		.l = 0,
		.db = GDT_DB_SEG32,
		.g = GDT_G_PAGE
	},
	/* privileged data segment: */
	{
		BASE(0),
		LIMIT(-1),
		.type = GDT_TYPE_RDWR,
		.s = 1,
		.dpl = 0,
		.p = 1,
		.avl = 0,
		.l = 0,
		.db = GDT_DB_SEG32,
		.g = GDT_G_PAGE
	}
};
_Static_assert(sizeof gdt == sizeof(gdt_t) * 3, "sizeof gdt != sizeof(gdt_t) * 3");

static gdt_ptr_t gdt_ptr = {
	.addr = (uint32_t)&gdt[0],
	.len = sizeof gdt - 1
};

extern void gdt_load(gdt_ptr_t *);

void gdt_init(void) {
	gdt_load(&gdt_ptr);
}
