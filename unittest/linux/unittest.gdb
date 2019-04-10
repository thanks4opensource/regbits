# regbits: C++ templates for type-safe bit manipulation
# Copyright (C) 2019 Mark R. Rubin
#
# This file is part of regbits.
#
# The regbits program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# The regbits program is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License (LICENSE.txt) along with the regbits program.	 If not, see
# <https://www.gnu.org/licenses/gpl.html>


set height 0
set logging on
printf "size:    %d\n", &do_test - &zero_reg
printf "repeats: %d\n", REPEATS

set logging off
break main:exit
run

set logging on
if start.tv_nsec > finish.tv_nsec
    set var finish.tv_sec  -= 1
    set var finish.tv_nsec += 1000000000
end
printf "time:    %d.%09d\n", \
       finish.tv_sec  - start.tv_sec, \
       finish.tv_nsec - start.tv_nsec

set var $ndx = 0
while $ndx < NUM_TESTS * 2
    printf "%-2d  %08x %08x\n", \
           $ndx / 2, \
           results[$ndx    ], \
           results[$ndx + 1]
    set var $ndx = $ndx + 2
end

set logging off
continue
quit
