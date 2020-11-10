// regbits: C++ templates for type-safe bit manipulation
// Copyright (C) 2019,2020 Mark R. Rubin
//
// This file is part of regbits.
//
// The regbits program is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// The regbits program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// (LICENSE.txt) along with the regbits program. If not, see
// <https://www.gnu.org/licenses/gpl.html>


#include <stdint.h>

#include <stm32f103xb.h>

void    init(void);   // for 2nd entry in vector table
// The following are 'declared' in the linker script
extern uint8_t  BSS_START;
extern uint8_t  BSS_END;
extern uint8_t  TOP_OF_STACK;
#define INTERRUPT_VECTORS_CONST
#include "stm32f103_vectors_handlers.h"



int     main(void);


void __attribute__ ((isr)) init()
{
    uint8_t     *dest;
    uint32_t     len;

    // zero out the uninitialized global/static variables
    dest = &BSS_START;
    len  = &BSS_END - &BSS_START;
    while (len--)
        *dest++=0;

    // set CPU's vector table address
    SCB->VTOR = (uint32_t)INTERRUPT_VECTORS;

    // start program
    main();
}
