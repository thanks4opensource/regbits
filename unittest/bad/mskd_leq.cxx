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


#include "mcu_regbits.hxx"

using namespace mcu;


void mskd_leq()
{
#ifdef GOOD
    Serial::Config::DATALEN_16_BITS <= Serial::Config::DATALEN_32_BITS;
#else
    Serial::Config::DATALEN_16_BITS <= Timer::Control::CLOCK_SOURCE_PLL;
#endif
}
