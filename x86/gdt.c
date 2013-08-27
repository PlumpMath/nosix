
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
	unsigned int limit_lo  : 16; 
	unsigned int base_lo   : 24; 
	unsigned int type      :  4; /* segment type */
	unsigned int s         :  1; /* descriptor type */
	unsigned int dpl       :  2; /* descriptor priviledge level */
	unsigned int p         :  1; /* present? */
	unsigned int limit_hi  :  4;
	unsigned int avl       :  1; /* available */
	unsigned int l         :  1; /* 64-bit code segment (i.e. Long mode) */
	unsigned int db        :  1; /* default operation size (16 vs 32 bit) */
	unsigned int g         :  1; /* granularity */
	unsigned int base_hi   :  8;
	
}__attribute__((packed));
_Static_assert(sizeof(gdt_t) == 8, "GDT packing error");
