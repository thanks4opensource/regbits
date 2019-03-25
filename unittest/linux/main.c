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


#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


extern void run();


#define NUM_REGS_DEFINE      4
#define NUM_TESTS_DEFINE    46

static const unsigned   NUM_REGS  = NUM_REGS_DEFINE ,
                        NUM_TESTS = NUM_TESTS_DEFINE,
                        REPEATS   = 100000          ;

uint32_t    registers[NUM_TESTS_DEFINE][NUM_REGS_DEFINE];



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




int main()
{
    if (brk((void*)BRK) != 0) {
        fprintf(stdout,
                "brk(0x%x) failed: %s(%d)\n",
                BRK,
                strerror(errno),
                errno);
        return 1;
    }

    struct timespec     start,
                        finish;
    unsigned            repeat;

    clock_gettime(CLOCK_REALTIME, &start);
    for (repeat = 0 ; repeat < REPEATS ; ++repeat) run();
    clock_gettime(CLOCK_REALTIME, &finish);

    goto exit;      // silence compiler warning
    exit: return 0; // for GDB breakpoint
}
