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
