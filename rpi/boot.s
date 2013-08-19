.section .init
.globl _start
_start:
	// set up the stack
	mov sp,#0x8000

	// call our c entry point
	bl main

	// if main returns, stop here.
hang$:
	b hang$
