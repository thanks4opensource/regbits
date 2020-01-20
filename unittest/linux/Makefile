# regbits: C++ templates for type-safe bit manipulation
# Copyright (C) 2019,2020 Mark R. Rubin
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


CXX_STANDARD ?= c++11
OPTIMIZE     ?= -O1
DEBUG        ?= -g3
GCC_ARM_BUG  ?= -DGCC_ARM_BUG
EXTRA_CC     ?=
EXTRA_CXX    ?=
PERIPH_BASE  ?= 0x700000
BRK	     ?= 0x800000
BRK_MALLOC   ?= -DUSE_BRK

C_ELFS   = $(subst ../,,$(wildcard ../*.c))
CXX_ELFS = $(subst ../,,$(wildcard ../*.cxx))
ELFS     = $(subst .c,.elf,$(C_ELFS)) $(subst .cxx,.elf,$(CXX_ELFS))
DMPS     = $(subst .elf,.elf.dmp,$(ELFS)) $(subst .elf,.o.dmp,$(ELFS))
OUTS     = $(subst .elf,.out,$(ELFS))

unittest: main.o ../do_tests.inl $(ELFS) $(DMPS) $(OUTS)
	@ ../unittest.py intel '$(OPTIMIZE) $(DEBUG) $(GCC_ARM_BUG) $(EXTRA_CXX) $(CXX_STANDARD)' ../do_tests.inl *.out *.o.dmp

# manual check that all tests change at least one tracked register
uniq: regbits.out
	uniq -f 1 --group regbits.out

.PHONY: clean cleanbin
clean: cleanbin
	rm -f *.dmp *.out
cleanbin:
	rm -f *.o *.elf


.PRECIOUS: %.o %.elf

INCLUDES = -I.. -I../..
vpath %c	..
vpath %cxx	..

CCOPTS =  -Wall				\
	  -Wno-unused-const-variable	\
	  $(OPTIMIZE)			\
	  $(DEBUG)			\
	  $(INCLUDES)			\
	  $(EXTRA_CC)			\
	  -DBRK=$(BRK)			\
	   $(BRK_MALLOC)		\
	  -DREGBITS_PERIPH_BASE=$(PERIPH_BASE)

CXXOPTS = -Wall				\
	  -std=$(CXX_STANDARD)		\
	  $(OPTIMIZE)			\
	  $(DEBUG)			\
	  $(INCLUDES)			\
	  $(GCC_ARM_BUG)		\
	  $(EXTRA_CXX)			\
	  -DREGBITS_PERIPH_BASE=$(PERIPH_BASE)



%.elf: %.o main.o
	$(CXX) -o $@ $^

%.elf.dmp: %.elf
	objdump -dC -j.text -j.rodata -j.data  $< > $@

%.out: %.elf
	@ rm -f $@
	@ gdb -q -x ../$(subst .elf,.gdb,$^) -x unittest.gdb $< > /dev/null

%.o.dmp: %.o
	objdump -dC -j.text -j.rodata -j.data  $< > $@

%.o: %.c
	$(CC) -c $(CCOPTS) $< -o $@

%.o: %.cxx
	$(CXX) -c $(CXXOPTS) $< -o $@
