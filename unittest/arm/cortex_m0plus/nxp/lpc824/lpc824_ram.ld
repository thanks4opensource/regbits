/* Linker script for NXP LPC824 */

ENTRY(init)

MEMORY
{
    FLASH (rx)  : org = 0x00000000, LENGTH = 32K
    RAM   (rwx) : org = 0x10000000, LENGTH = 8K
}

PROVIDE(MINIMUM_STACK_SIZE = 32);

SECTIONS
{
    . = ORIGIN(RAM);
    .text : {
        *(.isr_vectors); /* The interrupt vectors */
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

    RAM_BASE_ADDR   = ORIGIN(RAM);
    FLASH_BASE_ADDR = ORIGIN(FLASH);
    TOP_OF_STACK    = ORIGIN(RAM) + LENGTH(RAM);

    ASSERT(end + MINIMUM_STACK_SIZE < TOP_OF_STACK, "too big to fit in RAM")

}
