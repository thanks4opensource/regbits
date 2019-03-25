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

#include "LPC8xx.h"



extern void run();


#define NUM_REGS_DEFINE      4
#define NUM_TESTS_DEFINE    46

static const unsigned   NUM_REGS  __attribute__((unused)) = NUM_REGS_DEFINE,
                        NUM_TESTS __attribute__((unused)) = NUM_TESTS_DEFINE,
                        REPEATS                           = 1               ;

uint32_t    registers[NUM_TESTS_DEFINE][NUM_REGS_DEFINE];


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



void unittest_record_registers(
unsigned    test_num ,
uint32_t    register1,
uint32_t    register2,
uint8_t     byte     ,
uint32_t    register3)
{
    registers[test_num][0] = register1;
    registers[test_num][1] = register2;
    registers[test_num][2] = byte     ;
    registers[test_num][3] = register3;
}



uint32_t __attribute__((unused)) start ,
         __attribute__((unused)) finish;


int main()
{
    LPC_SYSCON->SYSAHBCLKDIV = 1;

    SysTick->CTRL = 0;   // halt
    SysTick->VAL  = 0;   // ensure will start from LOAD value
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->LOAD = 0xffffff;  // is 24 bits, max

    start = SysTick->VAL;

    uint32_t    repeat;
    for (repeat = 0 ; repeat < REPEATS ; ++repeat) run();

    finish = SysTick->VAL;

    exit: asm("nop");   // for GDB breakpoint
    goto exit;          // if no breakpoint
}
