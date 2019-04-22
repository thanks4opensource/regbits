// regbits: C++ templates for type-safe bit manipulation
// Copyright (C) 2019 Mark R. Rubin
//
// This file is part of regbits.
//
// The regbits program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// The regbits program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License (LICENSE.txt) along with the regbits program.  If not, see
// <https://www.gnu.org/licenses/gpl.html>


#include <stddef.h>
#include <stdint.h>

#include "mcu.h"


extern void run();


#define NUM_TESTS_DEFINE    116

static const unsigned   NUM_TESTS __attribute__((unused)) = NUM_TESTS_DEFINE,
                        REPEATS                           = 1               ;

uint32_t    results[NUM_TESTS_DEFINE * 2];


// needed for -O3
// inefficient, but only used by init()
void *memset(
void        *mem,
int          val,
size_t       siz)
{
    volatile uint8_t    *ptr = (uint8_t*)mem,
                        *end = ptr + siz;

    while (ptr < end)
        *ptr++ = val;

    return mem;
}



uint32_t __attribute__((unused)) elapsed_time = 0;



void do_test(
void                        (*test)(),
volatile uint32_t* const      regster,
const    uint32_t             testnum)
{
    uint32_t    start,
                finish;

    SysTick->CTRL = 0;   // halt
    SysTick->VAL  = 0;   // ensure will start from LOAD value
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->LOAD = 0xffffff;  // is 24 bits, max

    // wait for SysTick to start up
    while (SysTick->VAL == 0)
        asm("nop");

    start = SysTick->VAL;

    *regster = 0x00000000;
    test();
    results[testnum * 2] = *regster;

    *regster = 0xffffffff;
    test();
    results[testnum * 2 + 1] = *regster;

    finish = SysTick->VAL;

    elapsed_time += start - finish;
}



int main()
{
    uint32_t    repeat;
    for (repeat = 0 ; repeat < REPEATS ; ++repeat) run();

    exit: asm("nop");   // for GDB breakpoint
    goto exit;          // if no breakpoint
}
