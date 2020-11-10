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
