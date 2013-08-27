
#include <stdint.h>

#define GDT_S_SYSTEM 0
#define GDT_S_CODE_OR_DATA 1

#define GDT_DB_SEG16 0
#define GDT_DB_SEG32 1
/*
	see the intel system programming guide, section 3.4.5: "segment
	descriptors" for a full explanation of this structure.
*/
typedef struct gdt_t gdt_t;
struct gdt_t {
	uint64_t limit_lo  : 16; 
	uint64_t base_lo   : 24; 
	uint64_t type      :  4; /* segment type */
	uint64_t s         :  1; /* descriptor type */
	uint64_t dpl       :  2; /* descriptor priviledge level */
	uint64_t p         :  1; /* present? */
	uint64_t limit_hi  :  4;
	uint64_t avl       :  1; /* available */
	uint64_t l         :  1; /* 64-bit code segment (i.e. Long mode) */
	uint64_t db        :  1; /* default operation size (16 vs 32 bit) */
	uint64_t g         :  1; /* granularity */
	uint64_t base_hi   :  8;
	
}__attribute__((packed));
_Static_assert(sizeof(gdt_t) == 8, "GDT packing error");
