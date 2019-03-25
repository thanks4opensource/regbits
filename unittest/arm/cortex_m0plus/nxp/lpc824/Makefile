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


ifndef GCC_ARM_ROOT
$(error set GCC_ARM_ROOT environment variable)
endif

ifndef GDB_OPENOCD
$(error set GDB_OPENOCD environment variable)
endif

CXX_STANDARD ?= c++11
OPTIMIZE     ?= -O1
DEBUG        ?= -g3
EXTRA_CCC    ?=
EXTRA_CXX    ?=

THUMB_ARM    ?= -mthumb
ACPU	     ?= cortex-m0plus
TUNE	     ?=
ARCH	     ?=
TPCS	     ?=
		# aapcs aapcs-linux apcs-gnu atpcs iwmmxt
ABI          ?= apcs-gnu

PERIPH_BASE  ?= 0x10001400

CC      = arm-none-eabi-gcc
CXX     = arm-none-eabi-g++
OBJDUMP = arm-none-eabi-objdump
READELF = arm-none-eabi-readelf

export PATH := $(GCC_ARM_ROOT)/bin:$(PATH)


C_ELFS   = $(subst ../../../../,,$(wildcard ../../../../*.c))
CXX_ELFS = $(subst ../../../../,,$(wildcard ../../../../*.cxx))
ELFS     = $(subst .c,.elf,$(C_ELFS)) $(subst .cxx,.elf,$(CXX_ELFS))
DMPS     = $(subst .elf,.elf.dmp,$(ELFS))
RLFS     = $(subst .elf,.elf.rdelf,$(ELFS))
OUTS     = $(subst .elf,.out,$(ELFS))

INIT_FILE = lpc8xx_ram_init

unittest: main.o $(INIT_FILE).o $(ELFS) $(DMPS) $(RLFS)
	@ tail -n 1 -v  *.elf.map

gdb: $(OUTS)
	@ ../../../../unittest.py ../../../../regbits.cxx *.out

.PHONY: clean
clean:
	rm -f *.o *.elf *.dmp *.map *.out *.rdelf


.PRECIOUS: %.o %.elf

INCLUDES = -I../../../.. -I../../../../.. -Iinclude
vpath %c	../../../..
vpath %cxx	../../../..

ARM_OPTS = $(THUMB_ARM)

ifdef ACPU
ARM_OPTS += -mcpu=$(ACPU)
endif

ifdef TUNE
ARM_OPTS += -mtune=$(TUNE)
endif

ifdef ARCH
ARM_OPTS += -march=$(ARCH)
endif

ifdef TPCS
ARM_OPTS += -m$(TPCS)
endif

ifdef ABI
ARM_OPTS += -mabi=$(ABI)
endif

# otherwise won't link without non-existent "unwind" library
ARM_OPTS += -fno-exceptions -fno-unwind-tables   


CCOPTS =  -Wall				\
	  $(OPTIMIZE)			\
	  $(DEBUG)			\
	  $(INCLUDES)			\
	  -D__VTOR_PRESENT		\
	  $(ARM_OPTS)			\
	  $(EXTRA_CC)			\
	  -DPERIPH_BASE=$(PERIPH_BASE)

CXXOPTS = -Wall				\
	  -std=$(CXX_STANDARD)		\
	  $(OPTIMIZE)			\
	  $(DEBUG)			\
	  $(INCLUDES)			\
	  $(ARM_OPTS)			\
	  $(EXTRA_CXX)			\
	  -DPERIPH_BASE=$(PERIPH_BASE)

LDOPTS    = -marmelf -static -M --print-memory-usage  # -nostdlib
LD_SCRIPT = lpc824_ram.ld


%.elf: %.o main.o
	$(LD) -o $@ $(INIT_FILE).o	\
		    $^   		\
		    $(LDOPTS)		\
		    $(GNU_ARM_LIBDIRS)	\
		    $(LDLIBS) 		\
		    -T $(LD_SCRIPT)	\
	      > $@.map

%.elf.dmp: %.elf
	$(OBJDUMP) -dC -j.text -j.rodata -j.data  $< > $@

%.out: %.elf
	@ rm -f $@
	@ $$GDB_OPENOCD $< -x ../../../../$(subst .elf,.gdb,$^) -x unittest.gdb

#	@ $$GDB_OPENOCD $< -q -x ../../../../$(subst .elf,.gdb,$^) -x unittest.gdb > /dev/null


%.elf.rdelf: %.elf
	$(READELF) -a $<  > $@

%.o.dmp: %.o
	$(OBJDUMP) -dC -j.text -j.rodata -j.data  $< > $@

%.o: %.c
	$(CC) -c $(CCOPTS) $< -o $@

%.o: %.cxx
	$(CXX) -c $(CXXOPTS) $< -o $@
