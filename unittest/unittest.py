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



architecture  = sys.argv[1]
compile_flags = sys.argv[2]

outs  = []
funcs = []

found_run = False
with open(sys.argv[3], 'r') as file:
    for line in file:
        if 'do_test(' in line:
            funcs.append(line.split()[0].split('(')[1])

for filename in [name for name in sys.argv[4:] if name.endswith('.out')]:
    with open(filename, 'r') as file:
        lines = file.readlines()
        outs.append((filename, lines))

sizes = []
times = []

print()
for (name, lines) in outs:
    sizes.append(lines[0].split()[1])
    times.append(lines[2].split()[1])

if outs:
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

dmp_names = [name for name in sys.argv[4:] if name.endswith('.o.dmp')]
if not dmp_names: sys.exit(0)

dump_sizes = {}
funcs      = set()

for dmp_name in dmp_names:
    name_sizes = {}
    with open(dmp_name, 'r') as file:
        size = -1
        for line in file:
            if line.endswith('>:\n'):
                func = line.split()[1]
                func = func[1:-len('>:')]
                if '(' in func:
                    func = func[:func.find('(')]
                splits = line.split()
                if splits[-2] == '[clone':
                    func += splits[-1][:-3]
                funcs.add(func)
                size = 0
            elif line == '\n' and size > 0:
                name_sizes[func] = size
                size = -1
            elif size >= 0 and len(line) > 15:
                if architecture == 'arm':
                    size += 2 if line[15] == " " else 4
                elif architecture == 'intel':
                    size += len(line[10:30].split())
        name_sizes[func] = size
    dump_sizes[dmp_name[:-len('.o.dmp')]] = name_sizes

print('compile:', " ".join(compile_flags.split()))
for name in ('regbits', 'struct', 'raw', 'bitfield'):
    if name in dump_sizes:
        print("  %8s" % name, end='')
print()
func_list = list(funcs)
func_list.sort()
for func in func_list:
    best = 0xffffffff
    for name in ('regbits', 'struct', 'raw', 'bitfield'):
        if name in dump_sizes and func in dump_sizes[name]:
            if dump_sizes[name][func] < best:
                best = dump_sizes[name][func]
    for name in ('regbits', 'struct', 'raw', 'bitfield'):
        if name in dump_sizes and func in dump_sizes[name]:
            size = dump_sizes[name][func]
            print(  "%8d%s"
                  % (size, " *" if size == best else "  "),
                  end='')
        else:
            print("          ", end='')
    print("    %s" % func)

print('compile:', " ".join(compile_flags.split()))
for name in ('regbits', 'struct', 'raw', 'bitfield'):
    if name in dump_sizes:
        print("  %8s" % name, end='')
print()
func_list = list(funcs)
func_list.sort()
for func in func_list:
    best = 0xffffffff
    for name in ('regbits', 'struct', 'raw', 'bitfield'):
        if name in dump_sizes and func in dump_sizes[name]:
            if dump_sizes[name][func] < best:
                best = dump_sizes[name][func]
    if    (    func in dump_sizes['regbits']
           and func in dump_sizes['struct' ]
           and         dump_sizes['regbits'][func]
                     > dump_sizes['struct' ][func] ) \
       or (    func in dump_sizes['regbits']
           and func in dump_sizes['raw'    ]
           and         dump_sizes['regbits'][func]
                     > dump_sizes['raw'    ][func]):
        for name in ('regbits', 'struct', 'raw', 'bitfield'):
            if name in dump_sizes and func in dump_sizes[name]:
                size = dump_sizes[name][func]
                print(  "%8d%s"
                      % (size, " *" if size == best else "  "),
                      end='')
            else:
                print("          ", end='')
        print("    %s" % func)

if outs:
    print()
    print('compile:', " ".join(compile_flags.split()))
    for ndx in range(len(sizes)):
        print(  "%-16s\tsize: %s\ttime: %s"
              % (outs[ndx][0], sizes[ndx], times[ndx]))
