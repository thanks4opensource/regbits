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


#define NUM_TESTS_DEFINE    114

static const unsigned   NUM_TESTS = NUM_TESTS_DEFINE,
                        REPEATS   = 100000          ;

uint32_t    results[NUM_TESTS_DEFINE * 2];




void do_test(
void                        (*test)(),
volatile uint32_t* const      regster,
const    uint32_t             testnum)
{
    *regster = 0x00000000;
    test();
    results[testnum * 2] = *regster;

    *regster = 0xffffffff;
    test();
    results[testnum * 2 + 1] = *regster;
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
