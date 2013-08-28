#include "multiboot.h"
#include "serial.h"
#include "gdt.h"

#if 0
static
void print_mmap(uint32_t addr, uint32_t len) {
	uint32_t size;
	mmap_t *mmap;

	mmap = (mmap_t*)addr;
	for(;;){
		size = *(((uint32_t*)mmap)-1);
		klogf(KLOG_DEBUG, "%c %p : %p\n",
			(mmap->type == 1)? 'A' : 'R',
			mmap->base_addr,
			mmap->length);
		if(len <= size) {
			break;
		}
		mmap = (mmap_t*)(((uintptr_t)mmap)+size);
		len -= size;
	}
}
#endif

static
serial_out_t com1;

void main(mboot_info_t *mboot) {
	gdt_init();
	com1 = serial_init(COM1);
	stdklog = (output_t*)&com1;
	klogf(KLOG_DEBUG, "%p\n", mboot->flags);
	klogf(KLOG_DEBUG, "%p\n", mboot->mem_lower);
	klogf(KLOG_DEBUG, "%p\n", mboot->mem_upper);
/*	print_mmap(mboot->mmap_addr, mboot->mmap_length); */

	klogf(KLOG_DEBUG, "\n");
	klogf(KLOG_DEBUG, "Should print 0xdeadbaba : %p\n", 0xdeadbaba);
	klogf(KLOG_DEBUG, "Should print 0x0000017f : %p\n", 0x17f);
}
