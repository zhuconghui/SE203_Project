MEMORY 
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    SRAM1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
    SRAM2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}

_stack = ORIGIN(SRAM2) + LENGTH(SRAM2); /* 0x10008000 */

SECTIONS
{
    .vtor : {
        *(.vtor)
    } > FLASH

    .text : {
        *(.text)
        /* _etext = .; */
    } > FLASH

    .rodata :{
        /* _rodata = .; */
        *(.rodata)
        /* _erodata = .; */
    } > FLASH

    .data : {
        /* .data = .; */
        *(.data)
        /* _edata = .; */
    } > FLASH

    .bss : {
        _bstart = .;
        *(.bss) *(COMMON)
        _bend = .;
    } > SRAM1
}

ENTRY(_start)