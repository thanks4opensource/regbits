/*
regbits: C++ templates for type-safe bit manipulation
Copyright (C) 2019,2020 Mark R. Rubin

This file is part of regbits.

The regbits program is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

The regbits program is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
(LICENSE.txt) along with the regbits program. If not, see
<https:#www.gnu.org/licenses/gpl.html>
*/


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
