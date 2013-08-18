ENTRY(_start)
SECTIONS {
	/* We want to be loaded at the 1 MiB mark, right after the first block
	 * of IO ports. */
	.text 0x100000 : {
		*(.text)
		*(.data)
	}
	.bss : {
		*(.bss)
	}
}
