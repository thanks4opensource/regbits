#!/usr/bin/env python3

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
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License (LICENSE.txt) along with the regbits program.  If not, see
# <https://www.gnu.org/licenses/gpl.html>


import sys



outs  = []
funcs = []

found_run = False
with open(sys.argv[1], 'r') as file:
    for line in file:
        if found_run and 'record_registers(' in line:
            funcs.append(line.split()[0][:-1])
        elif 'run()' in line:
            found_run = True

for filename in sys.argv[2:]:
    with open(filename, 'r') as file:
        lines = file.readlines()
        outs.append((filename, lines))

sizes = []
times = []
for (name, lines) in outs:
    sizes.append(lines[0].split()[1])
    times.append(lines[2].split()[1])

for ndx in range(len(sizes)):
    print("%-16s\tsize: %s\ttime: %s" % (outs[ndx][0], sizes[ndx], times[ndx]))
print()

for line in range(3, len(outs[0][1])):
    matched = True
    current = outs[0][1][line]
    for out in range(1, len(outs)):
        if outs[out][1][line] != current:
            matched = False
            break
        current = outs[out][1][line]
    if not matched:
        print('\t', funcs[int(outs[0][1][line].split()[0])])
        for out in range(len(outs)):
            print("%-16s\t%s" % (outs[out][0], outs[out][1][line]), end='')
        print()
