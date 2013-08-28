.globl gdt_load
gdt_load:
	movl 4(%esp), %eax
	lgdt (%eax)
	// Load the privileged data segment (gdt[2]).
	// We use the same segment for all of our data regions.
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	// Far-jump to our privileged code segment (gdt[1]).
	jmpl $0x08, $code_seg
code_seg:
	ret
