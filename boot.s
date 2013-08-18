// various multiboot related constants:

// flags:
.set mboot_meminfo, (1<<1)

// multiboot magic value:
.set mboot_magic, 0x1badb002

// flags we're using, and our checksum:
.set mboot_flags, mboot_meminfo
.set mboot_checksum, -(mboot_magic + mboot_flags)

.globl _mboot
.align 4
_mboot:
	.int mboot_magic
	.int mboot_flags
	.int mboot_checksum

.globl _start
_start:
	// clear interrupts, set up our stack, and call our c code.
	cli
	movl $0x0,%ebp
	movl $_boot_stack, %esp
	// pass a pointer to the multiboot info to main().
	// TODO: gcc reqires 16 byte stack alignment; should we be
	// adjusting where our stack is so that this doesn't throw it off?
	pushl %ebx
	call main
hang$:
	// If main returns, just sit here.
	jmp hang$

.bss
.align 16
.space 4096 
_boot_stack:
