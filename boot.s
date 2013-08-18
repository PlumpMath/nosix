// various multiboot related constants:

// multiboot magic value:
.set mboot_magic, 0x1badb002

// flags we're using, and our checksum:
.set mboot_flags, 0
.set mboot_checksum, -(mboot_magic + mboot_flags)

.globl _mboot
_mboot:
	.int mboot_magic
	.int mboot_flags
	.int mboot_checksum

.globl _start
_start:
	jmp _start
