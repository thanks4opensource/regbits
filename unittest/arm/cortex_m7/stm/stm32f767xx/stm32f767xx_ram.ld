/* Linker script for STM32F767xx */

ENTRY(init)

MEMORY
{
    ITCM_RAM    (rwx) : org = 0x00000000, LENGTH =  16K
    DTCM_RAM    (rwx) : org = 0x20000000, LENGTH = 128K
    SRAM1       (rwx) : org = 0x20020000, LENGTH = 368K
    SRAM2       (rwx) : org = 0x2007C000, LENGTH =  16K
}

PROVIDE(MINIMUM_STACK_SIZE = 1K);

SECTIONS
{
    . = ORIGIN(ITCM_RAM);
    .fast_text : {
    } > ITCM_RAM

    . = ORIGIN(DTCM_RAM);
    .fast_data : {
    } > DTCM_RAM

    . = ORIGIN(SRAM1);
    .text : {
        *(.vectors); /* The interrupt vectors */
        *(.text);
    } > SRAM1

    .data : {
        . = ALIGN(4);
        *(.data);
    } > SRAM1

    BSS_START = .;
    .bss : {
        . = ALIGN(4);
        *(.bss);
    } > SRAM1
    BSS_END = .;

    end = .;   /* for gnu-arm libc.a */

    TOP_OF_STACK = ORIGIN(SRAM1) + LENGTH(SRAM1);

    ASSERT(end + MINIMUM_STACK_SIZE < TOP_OF_STACK, "too big to fit in RAM")
}
