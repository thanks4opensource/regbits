/* Linker script for STM32F103 ("BluePill") */

ENTRY(init)

MEMORY
{
    /*
        /usr/local/doc/hardware/st/STM32F103x8,B_datasheet.pdf
            p.10  2.1
            Table 2. STM32F103xx medium-density device features and peripheral
                     counts
                STM32F103Tx
                Flash - Kybytes  64 or 128
                SRAM  - Kybytes  20
            p.34  4 Memory mapping
            Figure 11. Memory map
            (SRAM and Flash base addresses, except Flash, SRAM, or System Memory
             can alias to 0x00000000 depending on BOOT configuration)
    */
    FLASH (rx)  : org = 0x08000000, LENGTH = 64k
    RAM   (rwx) : org = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    . = ORIGIN(RAM);
    .text : {
        *(.vectors); /* The interrupt vectors */
        *(.text);
    } > RAM

    .data : {
        . = ALIGN(4);
        *(.data);
    } > RAM

    BSS_START = .;
    .bss : {
        . = ALIGN(4);
        *(.bss);
    } > RAM
    BSS_END = .;

    end = .;   /* for gnu-arm libc.a */

    TOP_OF_STACK = ORIGIN(RAM) + LENGTH(RAM);
}
