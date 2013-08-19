ENTRY(_start)
SECTIONS {
	/* this is where the rpi expects the kernel to run from: */
	.init 0x8000 : {
		*(.init)
	}
	.text : {
		*(.text)
		*(.data)
	}
	.bss : {
		*(.bss)
	}
}
