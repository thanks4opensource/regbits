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
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License (LICENSE.txt) along with the regbits program.  If not, see
# <https://www.gnu.org/licenses/gpl.html>

MAKEFLAGS += --no-print-directory

all:
	@ echo make in linux
	@ (cd linux ; make )

	@ for dir in bad/linux bad/arm ; do		\
	    echo make in $$dir ;			\
	    (cd $$dir ; make) ;				\
	done

	@ for dir in cortex_m0plus/nxp/lpc824		\
		     cortex_m3/stm/stm32f103xb		\
		     cortex_m7/stm/stm32f767xx ; do	\
	    echo make in arm/$$dir ;			\
	    (cd arm/$$dir ; make) ;			\
	done

clean:
	@ echo make clean in linux
	@ (cd linux ; make clean )

	@ for dir in bad/linux bad/arm ; do		\
	    echo make clean in $$dir ;			\
	    (cd $$dir ; make clean) ;			\
	done

	@ for dir in cortex_m0plus/nxp/lpc824		\
		     cortex_m3/stm/stm32f103xb		\
		     cortex_m7/stm/stm32f767xx ; do	\
	    echo make clean in arm/$$dir ;		\
	    (cd arm/$$dir ; make clean) ;		\
	done

cleanbin:
	@ echo make cleanbin in linux
	@ (cd linux ; make cleanbin )

	@ for dir in bad/linux bad/arm ; do		\
	    echo make clean in $$dir ;			\
	    (cd $$dir ; make clean) ;			\
	done

	@ for dir in cortex_m0plus/nxp/lpc824		\
		     cortex_m3/stm/stm32f103xb		\
		     cortex_m7/stm/stm32f767xx ; do	\
	    echo make cleanbin arm/$$dir ;		\
	    (cd arm/$$dir ; make cleanbin) ;		\
	done
