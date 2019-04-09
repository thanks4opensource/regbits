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


GOOD	     ?= -UGOOD

CXX_STANDARD ?= c++11
OPTIMIZE     ?= -O1
DEBUG        ?=
EXTRA_CXX    ?=
PERIPH_BASE  ?= 0x100000

SRCS = $(subst ../,,$(wildcard ../*.cxx))
OBJS = $(SRCS:.cxx=.o)

unittest: $(OBJS)
	@ rm -f *.o

.PHONY: clean
clean:
	rm -f *.o

INCLUDES = -I../.. -I../../..
vpath %.cxx	..

CXXOPTS =  -Wall		\
	  -std=$(CXX_STANDARD)	\
	  $(OPTIMIZE)		\
	  $(DEBUG)		\
	  $(INCLUDES)		\
	  $(EXTRA_CXX)		\
	  $(GOOD)		\
	  -DREGBITS_PERIPH_BASE=$(PERIPH_BASE)

%.o: %.cxx
	@- if $(CXX) -c $(CXXOPTS) $< -o $@			\
	> /dev/null 2>&1 ;					\
	then							\
	    if [ $(GOOD) == -UGOOD ] ; then			\
		    echo "$< compiled but should have failed" ;	\
	    fi							\
	elif [ $(GOOD) == -DGOOD ] ; then			\
	    echo "$< failed but should have compiled" ;		\
	fi
