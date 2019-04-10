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


namespace app_config {
static const Serial::Config::pos_t
SERIAL_CONFIG_POS = Serial::Config::POLARITY_POS;

static const Serial::Config::bits_t
SERIAL_CONFIG_BITS = Serial::Config::POLARITY;

static const Serial::Config::mskd_t
SERIAL_CONFIG_MSKD = Serial::Config::DATALEN_16_BITS;

#ifdef GCC_ARM_BUG
#include <stddef.h>
static volatile uint32_t&         GPIO_WORD
                                = *(  reinterpret_cast<uint32_t*>(gpio1)
                                    + (offsetof(mcu::Gpio, words) >> 2 )
                                    + 3                                );
#else
static volatile uint32_t&       GPIO_WORD = gpio1->words.WORDS<3>();
#endif

static const Timer::Prescale::shft_t
TIMER_PRESCALER_SHIFT = Timer::Prescale::PRESCALER_HIGH_SHFT;

static Serial* const    SERIAL = serial2;
}




__attribute__((noinline)) void zero_reg()
{
    serial2->config = 0;
}



__attribute__((noinline)) void zero_array()
{
    gpio1->words.WORDS<3>() = 0;
}




__attribute__((noinline)) void set_singl_bits_operator()
{
    serial2->config |= Serial::Config::POLARITY ;
}



__attribute__((noinline)) void set_singl_bits_method()
{
    serial2->config.set(Serial::Config::POLARITY);
}



__attribute__((noinline)) void clr_singl_bits_operator()
{
    serial2->config -=Serial::Config::POLARITY ;
}



__attribute__((noinline)) void clr_singl_bits_method()
{
    serial2->config.clr(Serial::Config::POLARITY);
}



__attribute__((noinline)) void set_singl_mskd_operator()
{
    serial2->config |=Serial::Config::DATALEN_16_BITS ;
}



__attribute__((noinline)) void set_singl_mskd_method()
{
    serial2->config.set(Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void clr_singl_mskd_operator()
{
    serial2->config -=Serial::Config::DATALEN_16_BITS ;
}



__attribute__((noinline)) void clr_singl_mskd_method()
{
    serial2->config.clr(Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void equ_singl_bits_operator()
{
    serial2->config = Serial::Config::POLARITY ;
}



__attribute__((noinline)) void equ_singl_bits_method()
{
    serial2->config.wrt(Serial::Config::POLARITY);
}



__attribute__((noinline)) void equ_singl_mskd_operator()
{
    serial2->config = Serial::Config::DATALEN_16_BITS ;
}



__attribute__((noinline)) void equ_singl_mskd_method()
{
    serial2->config.wrt(Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void flp_singl_bits_operator()
{
    serial2->config ^= Serial::Config::POLARITY ;
}



__attribute__((noinline)) void flp_singl_bits_method()
{
    serial2->config.flp(Serial::Config::POLARITY);
}



__attribute__((noinline)) void flp_singl_mskd_operator()
{
    serial2->config ^= Serial::Config::DATALEN_16_BITS ;
}



__attribute__((noinline)) void flp_singl_mskd_method()
{
    serial2->config.flp(Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void ins_singl_mskd_operator()
{
    serial2->config /= Serial::Config::DATALEN_32_BITS ;
}



__attribute__((noinline)) void ins_singl_mskd_method()
{
    serial2->config.ins(Serial::Config::DATALEN_32_BITS);
}



__attribute__((noinline)) void set_multi_bits_operator()
{
    serial2->config |= Serial::Config::ENDIAN | Serial::Config::MODE;
}



__attribute__((noinline)) void set_multi_bits_method()
{
    serial2->config.set(Serial::Config::ENDIAN | Serial::Config::MODE) ;
}



__attribute__((noinline)) void ins_multi_mskd_operator()
{
    serial2->config /=    Serial::Config::DATALEN_16_BITS
                        | Serial::Config::RXPORT<3>()     ;

}



__attribute__((noinline)) void ins_multi_mskd_method()
{
    serial2->config.ins(  Serial::Config::DATALEN_16_BITS
                        | Serial::Config::RXPORT<3>()    );

}



__attribute__((noinline)) void equ_multi_bits_operator()
{
    serial2->config = Serial::Config::ENDIAN | Serial::Config::POLARITY ;
}



__attribute__((noinline)) void equ_multi_bits_method()
{
    serial2->config.wrt(Serial::Config::ENDIAN | Serial::Config::POLARITY);
}



__attribute__((noinline)) void equ_multi_mskd_operator()
{
    serial2->config =   Serial::Config::PARITY_EVEN
                      | Serial::Config::RXPORT<6>() ;
}



__attribute__((noinline)) void equ_multi_mskd_method()
{
    serial2->config.wrt(  Serial::Config::PARITY_EVEN
                        | Serial::Config::RXPORT<6>());
}



__attribute__((noinline)) void equ_bits_mskd_operator()
{
    serial2->config =   Serial::Config::ENDIAN
                      | Serial::Config::DATALEN_16_BITS ;
}



__attribute__((noinline)) void equ_bits_mskd_method()
{
    serial2->config.wrt(  Serial::Config::ENDIAN
                        | Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void equ_mskd_bits_operator()
{
    serial2->config =   Serial::Config::DATALEN_32_BITS
                      | Serial::Config::POLARITY       ;
}



__attribute__((noinline)) void equ_mskd_bits_method()
{
    serial2->config.wrt(  Serial::Config::DATALEN_32_BITS
                        | Serial::Config::POLARITY       );
}



__attribute__((noinline)) void equ_bits_var()
{
    Serial::Config::bits_t  config = Serial::Config::POLARITY;

    serial2->config = config;

    config = Serial::Config::MODE;

    serial2->config = config;
}



__attribute__((noinline)) void equ_mskd_var()
{
    Serial::Config::mskd_t  config = Serial::Config::DATALEN_16_BITS;

    serial2->config = config;

    config = Serial::Config::RXPORT<3>();

    serial2->config = config;
}



__attribute__((noinline)) void cmp_equ_zero()
{
    serial2->config = 0;

    if (serial2->config == 0)
        timer1->prescale = Timer::Prescale::PRESCALER_HIGH<29>();
    else
        timer1->prescale = Timer::Prescale::PRESCALER_HIGH<17>();
}



__attribute__((noinline)) void cmp_neq_zero()
{
    serial2->config = 0;

    if (serial2->config != 0)
        serial2->config = Serial::Config::DATALEN_32_BITS;
    else
        serial2->config = Serial::Config::ENDIAN           ;
}



__attribute__((noinline)) void cmp_equ_bits()
{
    serial2->config = Serial::Config::POLARITY ;

    if (serial2->config == Serial::Config::POLARITY)
        timer1->prescale = Timer::Prescale::PRESCALER_HIGH<11>();
    else
        timer1->prescale = Timer::Prescale::PRESCALER_HIGH<13>();
}



__attribute__((noinline)) void cmp_neq_bits()
{
    serial2->config = Serial::Config::POLARITY ;

    if (serial2->config != Serial::Config::POLARITY)
        serial2->config  = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config  = Serial::Config::ENDIAN         ;
}



__attribute__((noinline)) void cmp_equ_mskd()
{
    serial2->config = Serial::Config::TXPORT<29>();

    if (serial2->config  == Serial::Config::TXPORT<17>())
        timer1->prescale /= Timer::Prescale::PRESCALER_HIGH<7>();
    else
        timer1->prescale /= Timer::Prescale::PRESCALER_HIGH<17>();
}



__attribute__((noinline)) void cmp_neq_mskd()
{
    serial2->config = Serial::Config::TXPORT<29>();

    if (serial2->config != Serial::Config::TXPORT<17>())
        serial2->config /= Serial::Config::DATALEN_32_BITS;
    else
        serial2->config |= Serial::Config::POLARITY        ;
}



__attribute__((noinline)) void cmp_equ_reg()
{
    uint32_t word = (  Serial::Config::ENDIAN
                     | Serial::Config::DATALEN_16_BITS).bits();

    serial2->config = word;

    if (serial2->config == word)
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<21>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<23>();
}



__attribute__((noinline)) void cmp_neq_reg()
{
    uint32_t word = (  Serial::Config::ENDIAN
                     | Serial::Config::DATALEN_16_BITS).bits();

    serial2->config = word;

    if (serial2->config != word)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::ENDIAN         ;
}



__attribute__((noinline)) void bits_val(
const Serial::Config::bits_t        config)
{
    serial2->config |= config;
}



__attribute__((noinline)) void call_bits_val_const()
{
    bits_val(+Serial::Config::POLARITY);
}



__attribute__((noinline)) void call_bits_val_var()
{
    Serial::Config::bits_t  config = Serial::Config::POLARITY;

    bits_val(config);
}



__attribute__((noinline)) void constexpr_bits_array()
{
    gpio1->words.WORDS<3>() = 0x6;
    gpio1->set              = Gpio::Set::SET<13>();
}



__attribute__((noinline)) void runtime_bits_array()
{
    volatile unsigned   index = 3;

    gpio1->words.words(index) = 0x21;

    index = 7;

    gpio1->set = Gpio::Set::set(index);
}



__attribute__((noinline)) void bits_ref(
const Serial::Config::bits_t        &config)
{
    serial2->config |=  config;
}



__attribute__((noinline)) void call_bits_ref_const()
{
    bits_ref(+Serial::Config::MODE);
}



__attribute__((noinline)) void call_bits_ref_var()
{
    Serial::Config::bits_t  config = Serial::Config::MODE;

    bits_ref(config);
}



__attribute__((noinline)) void mskd_val(
const Serial::Config::mskd_t    config)
{
    serial2->config.ins(config);
}



__attribute__((noinline)) void call_mskd_val_const()
{
    mskd_val(+Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void call_mskd_val_var()
{
    Serial::Config::mskd_t  config = Serial::Config::DATALEN_16_BITS;

    mskd_val(config);
}



__attribute__((noinline)) void mskd_ref(
const Serial::Config::mskd_t        &config)
{
    serial2->config /=  config;
}



__attribute__((noinline)) void call_mskd_ref_const()
{
    mskd_ref(+Serial::Config::DATALEN_32_BITS);
}



__attribute__((noinline)) void call_mskd_ref_var()
{
    Serial::Config::mskd_t  config = Serial::Config::DATALEN_16_BITS;

    mskd_ref(config);
}



__attribute__((noinline)) void periph_bits(
Serial      *serial)
{
    serial->config |= Serial::Config::POLARITY ;
}

__attribute__((noinline)) void call_periph_bits()
{
    periph_bits(serial2);
}



__attribute__((noinline)) void periph_bits_val(
Serial                          *serial,
const Serial::Config::bits_t     bits  )

{
    serial->config |= bits;
}

__attribute__((noinline)) void call_periph_bits_val()
{
    periph_bits_val(serial2, +Serial::Config::POLARITY);
}



__attribute__((noinline)) void reg_bits_val(
Reg<uint32_t, Serial::Config>   &config,
const Serial::Config::bits_t     bits  )
{
    config |= bits;
}

__attribute__((noinline)) void call_reg_bits_val()
{
    reg_bits_val(serial2->config, +Serial::Config::POLARITY);
}



__attribute__((noinline)) void periph_bits_ref(
Serial                          *serial,
const Serial::Config::bits_t    &bits  )

{
    serial->config |= bits;
}

__attribute__((noinline)) void call_periph_bits_ref()
{
    periph_bits_ref(serial2, +Serial::Config::POLARITY);
}



__attribute__((noinline)) void reg_bits_ref(
Reg<uint32_t, Serial::Config>   &config,
const Serial::Config::bits_t    &bits  )
{
    config |= bits;
}

__attribute__((noinline)) void call_reg_bits_ref()
{
    reg_bits_ref(serial2->config, +Serial::Config::POLARITY);
}



__attribute__((noinline)) void periph_mskd(
Serial      *serial)
{
    serial->config /= Serial::Config::DATALEN_16_BITS ;
}

__attribute__((noinline)) void call_periph_mskd()
{
    periph_mskd(serial2);
}



__attribute__((noinline)) void periph_mskd_val(
Serial                          *serial,
const Serial::Config::mskd_t     mask )

{
    serial->config /= mask;
}

__attribute__((noinline)) void call_periph_mskd_val()
{
    periph_mskd_val(serial2, +Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void reg_mskd_val(
Reg<uint32_t, Serial::Config>   &config,
const Serial::Config::mskd_t     mask )
{
    config /= mask;
}

__attribute__((noinline)) void call_reg_mskd_val()
{
    reg_mskd_val(serial2->config, +Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void periph_mskd_ref(
Serial                          *serial,
const Serial::Config::mskd_t     mask )

{
    serial->config /= mask;
}

__attribute__((noinline)) void call_periph_mskd_ref()
{
    periph_mskd_ref(serial2, +Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void reg_mskd_ref(
Reg<uint32_t, Serial::Config>   &config,
const Serial::Config::mskd_t     mask )
{
    config /= mask;
}

__attribute__((noinline)) void call_reg_mskd_ref()
{
    reg_mskd_ref(serial2->config, +Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) Serial::Config::bits_t return_bits()
{
    return Serial::Config::ENDIAN;
}



__attribute__((noinline)) void call_return_bits()
{
    Serial::Config::bits_t  config_bits = return_bits();

    if (config_bits == Serial::Config::ENDIAN)
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<21>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<3>();
}



__attribute__((noinline)) Serial::Config::mskd_t return_mskd()
{
    return +Serial::Config::PARITY_EVEN;
}



__attribute__((noinline)) void call_return_mskd()
{
    Serial::Config::mskd_t  config_mskd = return_mskd();

    if (config_mskd == Serial::Config::PARITY_EVEN)
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<17>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<19>();
}



__attribute__((noinline)) Serial::config_t* return_reg()
{
    serial2->config = Serial::Config::POLARITY;

    return &serial2->config;
}



__attribute__((noinline)) void call_return_reg()
{
    Serial::config_t    *config = return_reg();

    if (*config == Serial::Config::POLARITY)
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<15>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<23>();
}



__attribute__((noinline)) Serial* return_periph()
{
    serial2->config = Serial::Config::POLARITY;

    return serial2;
}



__attribute__((noinline)) void call_return_periph()
{
    Serial*     serial = return_periph();

    if (serial->config == Serial::Config::POLARITY)
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<19>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER_HIGH<21>();
}



__attribute__((noinline)) void pos_val(
const Serial::Config::pos_t     pos)
{
    if (pos == Serial::Config::ENDIAN_POS)
        gpio1->words.WORDS<3>() = 0x33;
    else if (pos == Serial::Config::POLARITY_POS)
        gpio1->words.WORDS<3>() = 0x44;
    else
        gpio1->words.WORDS<3>() = 0x55;
}



__attribute__((noinline)) void call_pos_val()
{
    pos_val(+Serial::Config::ENDIAN_POS);

    Serial::Config::pos_t   pos = Serial::Config::POLARITY_POS;

    pos_val(pos);
}



__attribute__((noinline)) void pos_ref(
const Serial::Config::pos_t     &pos)
{
    if (pos == Serial::Config::ENDIAN_POS)
        gpio1->words.WORDS<3>() = 0x66;
    else if (pos == Serial::Config::POLARITY_POS)
        gpio1->words.WORDS<3>() = 0x77;
    else
        gpio1->words.WORDS<3>() = 0x88;
}



__attribute__((noinline)) void call_pos_ref()
{
    pos_ref(+Serial::Config::ENDIAN_POS);

    Serial::Config::pos_t   pos = Serial::Config::ENDIAN_POS;

    pos_ref(pos);
}



__attribute__((noinline)) void runtime_range_val(
const Serial::Config::mskd_t    txport)
{
    serial2->config /= txport;
}



__attribute__((noinline)) void call_range_val(
unsigned    port)
{
    runtime_range_val(Serial::Config::txport(port));
}



__attribute__((noinline)) void call_range_val_port()
{
    call_range_val(31);
}



__attribute__((noinline)) void runtime_range_ref(
const Serial::Config::mskd_t    txport)
{
    serial2->config /= txport;
}



__attribute__((noinline)) void call_range_ref(
unsigned    port)
{
    runtime_range_ref(Serial::Config::txport(port));
}



__attribute__((noinline)) void call_range_ref_port()
{
    call_range_ref(0xc);
}



__attribute__((noinline)) void check_array_range_pass(
const unsigned  port)
{
    if (Gpio::Words::words_valid(port))
        gpio1->words.WORDS<3>() = 127;
    else
        gpio1->words.WORDS<3>() = 131;
}



__attribute__((noinline)) void check_array_range_fail(
const unsigned  port)
{
    if (Gpio::Words::words_valid(port))
        gpio1->words.WORDS<3>() = 149;
    else
        gpio1->words.WORDS<3>() = 151;
}



__attribute__((noinline)) void check_bits_range_pass(
const unsigned  bit_num)
{
    if (Gpio::Set::set_valid(bit_num))
        gpio1->words.WORDS<3>() = 157;
    else
        gpio1->words.WORDS<3>() = 163;
}



__attribute__((noinline)) void check_bits_range_fail(
const unsigned  bit_num)
{
    if (Gpio::Set::set_valid(bit_num))
        gpio1->words.WORDS<3>() = 167;
    else
        gpio1->words.WORDS<3>() = 173;
}



__attribute__((noinline)) void check_mskd_range_pass(
unsigned port)
{
    if (Serial::Config::rxport_valid(port))  // check valid_txport() below
        gpio1->words.WORDS<3>() = 179;
    else
        gpio1->words.WORDS<3>() = 181;
}



__attribute__((noinline)) void check_mskd_range_fail(
unsigned port)
{
    if (Serial::Config::txport_valid(port))  // check rxport_valid() aove
        gpio1->words.WORDS<3>() = 191;
    else
        gpio1->words.WORDS<3>() = 193;
}



__attribute__((noinline)) void prescaler_low()
{
    timer1->prescale = Timer::Prescale::PRESCALER_LOW<119>();

      gpio1->words.WORDS<3>()
    = timer1->prescale >> Timer::Prescale::PRESCALER_LOW_SHFT;
}



__attribute__((noinline)) void prescaler_high()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<29>();

      gpio1->words.WORDS<3>()
    = timer1->prescale >> Timer::Prescale::PRESCALER_HIGH_SHFT;
}



__attribute__((noinline)) void reg_mskd_lss()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<27>();

    if (timer1->prescale < Timer::Prescale::PRESCALER_HIGH<28>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_leq()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<23>();

    if (   timer1->prescale <= Timer::Prescale::PRESCALER_HIGH<23>()
        && timer1->prescale <= Timer::Prescale::PRESCALER_HIGH<24>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_gtr()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<19>();

    if (timer1->prescale > Timer::Prescale::PRESCALER_HIGH<18>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_geq()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<17>();

    if (   timer1->prescale >= Timer::Prescale::PRESCALER_HIGH<16>()
        && timer1->prescale >= Timer::Prescale::PRESCALER_HIGH<17>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}



__attribute__((noinline)) void pos_cmp_eq()
{
    Serial::Config::pos_t   duplicate(Serial::Config::ENDIAN_POS.pos());

    if (duplicate == Serial::Config::ENDIAN_POS)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void pos_cmp_ne()
{
    Serial::Config::pos_t   duplicate(Serial::Config::POLARITY_POS.pos());

    if (duplicate == Serial::Config::POLARITY_POS)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}



__attribute__((noinline)) void bits_extract_eq()
{
    serial2->config = Serial::Config::POLARITY;

    Serial::Config::bits_t  extracted = serial2->config;

    if (extracted == Serial::Config::POLARITY)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void bits_extract_ne()
{
    serial2->config = Serial::Config::ENDIAN;

    Serial::Config::bits_t  extracted = serial2->config;

    if (extracted != Serial::Config::ENDIAN)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}



__attribute__((noinline)) void mskd_extract_eq()
{
    serial2->config = Serial::Config::DATALEN_16_BITS;

    Serial::Config::mskd_t  extracted = Serial::Config::DATALEN_8_BITS;
                            extracted = serial2->config;

    if (extracted == Serial::Config::DATALEN_16_BITS)
        serial2->config = Serial::Config::ENDIAN;
    else
        serial2->config = Serial::Config::POLARITY;
}

__attribute__((noinline)) void mskd_extract_ne()
{
    serial2->config = Serial::Config::DATALEN_32_BITS;

    Serial::Config::mskd_t  extracted = Serial::Config::DATALEN_8_BITS;
                            extracted = serial2->config;

    if (extracted != Serial::Config::DATALEN_32_BITS)
        serial2->config = Serial::Config::ENDIAN;
    else
        serial2->config = Serial::Config::POLARITY;
}

__attribute__((noinline)) void mskd_extract_lss()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<11>();

    Timer::Prescale::mskd_t     extracted = Timer::Prescale::PRESCALER_HIGH<1>();
                                extracted = timer1->prescale;

    if (extracted < Timer::Prescale::PRESCALER_HIGH<12>())
        serial2->config = Serial::Config::ENDIAN;
    else
        serial2->config = Serial::Config::POLARITY;
}

__attribute__((noinline)) void mskd_extract_leq()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<23>();

    Timer::Prescale::mskd_t     extracted = Timer::Prescale::PRESCALER_HIGH<1>();
                                extracted = timer1->prescale;

    if (   extracted <= Timer::Prescale::PRESCALER_HIGH<23>()
        && extracted <= Timer::Prescale::PRESCALER_HIGH<24>())
        serial2->config = Serial::Config::ENDIAN;
    else
        serial2->config = Serial::Config::POLARITY;
}

__attribute__((noinline)) void mskd_extract_gtr()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<19>();

    Timer::Prescale::mskd_t     extracted = Timer::Prescale::PRESCALER_HIGH<1>();
                                extracted = timer1->prescale;

    if (extracted > Timer::Prescale::PRESCALER_HIGH<18>())
        serial2->config = Serial::Config::ENDIAN;
    else
        serial2->config = Serial::Config::POLARITY;
}

__attribute__((noinline)) void mskd_extract_geq()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<11>();

    Timer::Prescale::mskd_t     extracted = Timer::Prescale::PRESCALER_HIGH<1>();
                                extracted = timer1->prescale;

    if (   extracted >= Timer::Prescale::PRESCALER_HIGH<10>()
        && extracted >= Timer::Prescale::PRESCALER_HIGH<11>())
        serial2->config = Serial::Config::ENDIAN;
    else
        serial2->config = Serial::Config::POLARITY;
}



__attribute__((noinline)) void set_bits_global()
{
    serial2->config |= app_config::SERIAL_CONFIG_BITS;
}

__attribute__((noinline)) void ins_mskd_global()
{
    serial2->config /= app_config::SERIAL_CONFIG_MSKD;
}

__attribute__((noinline)) void assign_array_global()
{
    app_config::GPIO_WORD = 189;
}

__attribute__((noinline)) void shifted_global()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<23>();

      gpio1->words.WORDS<3>()
    = timer1->prescale.shifted(+app_config::TIMER_PRESCALER_SHIFT);
}

__attribute__((noinline)) void assign_register_global()
{
    app_config::SERIAL->config = Serial::Config::DATALEN_32_BITS;
}



__attribute__((noinline)) void call_pos_val_global()
{
    pos_val(+app_config::SERIAL_CONFIG_POS);
}

__attribute__((noinline)) void call_pos_ref_global()
{
    pos_ref(+app_config::SERIAL_CONFIG_POS);
}

__attribute__((noinline)) void call_bits_val_global()
{
    bits_val(+app_config::SERIAL_CONFIG_BITS);
}

__attribute__((noinline)) void call_bits_ref_global()
{
    bits_ref(+app_config::SERIAL_CONFIG_BITS);
}

__attribute__((noinline)) void call_mskd_val_global()
{
    mskd_val(+app_config::SERIAL_CONFIG_MSKD);
}

__attribute__((noinline)) void call_mskd_ref_global()
{
    mskd_ref(+app_config::SERIAL_CONFIG_MSKD);
}


__attribute__((noinline)) void shifted_val(
const Timer::Prescale::shft_t       shift)
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<23>();

    gpio1->words.WORDS<3>() = timer1->prescale.shifted(shift);
}

__attribute__((noinline)) void call_shifted_const_val()
{
    shifted_val(+Timer::Prescale::PRESCALER_HIGH_SHFT);
}

__attribute__((noinline)) void call_shifted_var_val()
{
    Timer::Prescale::shft_t     shift = Timer::Prescale::PRESCALER_HIGH_SHFT;

    shifted_val(shift);
}

__attribute__((noinline)) void call_shifted_global_val()
{
    shifted_val(+app_config::TIMER_PRESCALER_SHIFT);
}

__attribute__((noinline)) void shifted_ref(
const Timer::Prescale::shft_t       &shift)
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<23>();

    gpio1->words.WORDS<3>() = timer1->prescale.shifted(shift);
}

__attribute__((noinline)) void call_shifted_const_ref()
{
    shifted_ref(+Timer::Prescale::PRESCALER_HIGH_SHFT);
}

__attribute__((noinline)) void call_shifted_var_ref()
{
    Timer::Prescale::shft_t     shift = Timer::Prescale::PRESCALER_HIGH_SHFT;

    shifted_ref(shift);
}

__attribute__((noinline)) void call_shifted_global_ref()
{
    shifted_ref(+app_config::TIMER_PRESCALER_SHIFT);
}



__attribute__((noinline)) void copy_bits_equ()
{
    serial2->config = Serial::Config::POLARITY;

    Copy<uint32_t, Serial::Config> copy(serial2->config);

    if (copy == Serial::Config::POLARITY)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_bits_neq()
{
    serial2->config = Serial::Config::POLARITY;

    Copy<uint32_t, Serial::Config> copy(serial2->config);

    if (copy != Serial::Config::POLARITY)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_equ()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<11>();

    Copy<uint32_t, Timer::Prescale> copy(timer1->prescale);

    if (copy == Timer::Prescale::PRESCALER_HIGH<11>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_neq()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<13>();

    Copy<uint32_t, Timer::Prescale> copy(timer1->prescale);

    if (copy != Timer::Prescale::PRESCALER_HIGH<13>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_lss()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<27>();

    Copy<uint32_t, Timer::Prescale> copy(timer1->prescale);

    if (copy < Timer::Prescale::PRESCALER_HIGH<28>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_leq()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<23>();

    Copy<uint32_t, Timer::Prescale> copy(timer1->prescale);

    if (   copy <= Timer::Prescale::PRESCALER_HIGH<23>()
        && copy <= Timer::Prescale::PRESCALER_HIGH<24>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_gtr()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<19>();

    Copy<uint32_t, Timer::Prescale> copy(timer1->prescale);

    if (copy > Timer::Prescale::PRESCALER_HIGH<18>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_geq()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<17>();

    Copy<uint32_t, Timer::Prescale> copy(timer1->prescale);

    if (   copy >= Timer::Prescale::PRESCALER_HIGH<16>()
        && copy >= Timer::Prescale::PRESCALER_HIGH<17>())
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_shifted()
{
    timer1->prescale = Timer::Prescale::PRESCALER_HIGH<11>();

    Copy<uint32_t, Timer::Prescale> copy(timer1->prescale);

    if (copy.shifted(Timer::Prescale::PRESCALER_HIGH_SHFT) == 11)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_bits_val(
const Copy<uint32_t, Serial::Config>    copy)
{
    if (copy == Serial::Config::POLARITY)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void call_copy_bits_val()
{
    serial2->config = Serial::Config::POLARITY;

    Copy<uint32_t, Serial::Config> copy(serial2->config);

    copy_bits_val(copy);
}

__attribute__((noinline)) void copy_bits_ref(
const Copy<uint32_t, Serial::Config>    &copy)
{
    if (copy == Serial::Config::POLARITY)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}

__attribute__((noinline)) void call_copy_bits_ref()
{
    serial2->config = Serial::Config::POLARITY;

    Copy<uint32_t, Serial::Config> copy(serial2->config);

    copy_bits_ref(copy);
}






extern "C" void do_test(void                        (*test)(),
                        volatile uint32_t* const      regster,
                        uint32_t                      testnum);


extern "C" __attribute__((noinline)) void run()
{
    using ptr_t = volatile uint32_t* const;

    static ptr_t
    serial2_config  = reinterpret_cast<ptr_t>(&serial2->config        ),
    timer1_prescale = reinterpret_cast<ptr_t>(&timer1  ->prescale     ),
    gpio1_words_3   = reinterpret_cast<ptr_t>(&gpio1->words.WORDS<3>()),
    gpio1_set       = reinterpret_cast<ptr_t>(&gpio1    ->set         );

#include "do_tests.inl"

}  // run()
