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


#include "bitops.h"
#include "mcu_raw.h"



static const uint32_t   SERIAL_CONFIG_POS    = SERIAL_CONFIG_POLARITY_POS       ,
                        SERIAL_CONFIG_BITS   = SERIAL_CONFIG_POLARITY           ,
                        SERIAL_CONFIG_MASK   = SERIAL_CONFIG_DATALEN_MSK        ,
                        SERIAL_CONFIG_MSKD   = SERIAL_CONFIG_DATALEN_16_BITS    ,
                        TIMER_PRESCALER_MASK = TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                        TIMER_PRESCALER_SHFT = TIMER_PRESCALE_PRESCALER_HIGH_POS;

static volatile uint32_t* const     GPIO_WORDS = GPIO1 + GPIO_WORDS_OFFSET + 3;

static volatile uint32_t* const     SERIAL = SERIAL2;




__attribute__((noinline)) void zero_reg()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET )    = 0;
}



__attribute__((noinline)) void zero_array()
{
     (GPIO1   + GPIO_WORDS_OFFSET    )[3] = 0;
}



__attribute__((noinline)) void set_singl_bits_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void set_singl_bits_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void clr_singl_bits_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) &= ~SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void clr_singl_bits_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) &= ~SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void set_singl_mskd_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void set_singl_mskd_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void clr_singl_mskd_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) &= ~SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void clr_singl_mskd_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) &= ~SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_singl_bits_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_singl_bits_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_singl_mskd_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_singl_mskd_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void flp_singl_bits_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) ^= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void flp_singl_bits_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) ^= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void flp_singl_mskd_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) ^= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void flp_singl_mskd_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) ^= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void ins_singl_mskd_operator()
{
    CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET),
             SERIAL_CONFIG_DATALEN_MSK,
             SERIAL_CONFIG_DATALEN_32_BITS);
}



__attribute__((noinline)) void ins_singl_mskd_method()
{
    CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET),
             SERIAL_CONFIG_DATALEN_MSK,
             SERIAL_CONFIG_DATALEN_32_BITS);
}



__attribute__((noinline)) void set_multi_bits_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |=   SERIAL_CONFIG_ENDIAN
                                         | SERIAL_CONFIG_MODE  ;
}



__attribute__((noinline)) void set_multi_bits_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |=   SERIAL_CONFIG_ENDIAN
                                         | SERIAL_CONFIG_MODE  ;
}



__attribute__((noinline)) void ins_multi_mskd_operator()
{
    CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET),
             SERIAL_CONFIG_DATALEN_MSK | SERIAL_CONFIG_RXPORT_MSK,
             SERIAL_CONFIG_DATALEN_16_BITS | (3 << SERIAL_CONFIG_RXPORT_POS));
}



__attribute__((noinline)) void ins_multi_mskd_method()
{
    CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET),
             SERIAL_CONFIG_DATALEN_MSK | SERIAL_CONFIG_RXPORT_MSK,
             SERIAL_CONFIG_DATALEN_16_BITS | (3 << SERIAL_CONFIG_RXPORT_POS));
}



__attribute__((noinline)) void equ_multi_bits_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_multi_bits_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_multi_mskd_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) =    SERIAL_CONFIG_PARITY_EVEN
                                        | (6 << SERIAL_CONFIG_RXPORT_POS);
}



__attribute__((noinline)) void equ_multi_mskd_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) =    SERIAL_CONFIG_PARITY_EVEN
                                        | (6 << SERIAL_CONFIG_RXPORT_POS);
}



__attribute__((noinline)) void equ_bits_mskd_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_bits_mskd_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_mskd_bits_operator()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) =   SERIAL_CONFIG_DATALEN_32_BITS
                                        | SERIAL_CONFIG_POLARITY           ;
}



__attribute__((noinline)) void equ_mskd_bits_method()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) =   SERIAL_CONFIG_DATALEN_32_BITS
                                        | SERIAL_CONFIG_POLARITY           ;
}



__attribute__((noinline)) void equ_bits_var()
{
    uint32_t    config = SERIAL_CONFIG_POLARITY;

    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = config;

    config = SERIAL_CONFIG_MODE;

    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = config;
}



__attribute__((noinline)) void equ_mskd_var()
{
    uint32_t    config = SERIAL_CONFIG_DATALEN_16_BITS;

    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = config;

    config = 3 << SERIAL_CONFIG_RXPORT_POS;

    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = config;
}



__attribute__((noinline)) void cmp_equ_zero()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = 0;

    if (*(SERIAL2 + SERIAL_CONFIG_OFFSET) == 0)
        *(TIMER1 + TIMER_PRESCALE_OFFSET) = 29 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
        *(TIMER1 + TIMER_PRESCALE_OFFSET) = 17 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) void cmp_neq_zero()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = 0;

    if (*(SERIAL2 + SERIAL_CONFIG_OFFSET) != 0)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN         ;
}



__attribute__((noinline)) void cmp_equ_bits()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;

    if (   (*(SERIAL2 + SERIAL_CONFIG_OFFSET) & SERIAL_CONFIG_POLARITY)
        == SERIAL_CONFIG_POLARITY)
          *(TIMER1 + TIMER_PRESCALE_OFFSET)
        = 11 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
          *(TIMER1 + TIMER_PRESCALE_OFFSET)
        = 13 << TIMER_PRESCALE_PRESCALER_HIGH_POS ;
}



__attribute__((noinline)) void cmp_neq_bits()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;

    if (!(*(SERIAL2 + SERIAL_CONFIG_OFFSET) & SERIAL_CONFIG_POLARITY))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET)  = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET)  = SERIAL_CONFIG_ENDIAN        ;
}



__attribute__((noinline)) void cmp_equ_multi_bits()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) =   SERIAL_CONFIG_ENDIAN
                                        | SERIAL_CONFIG_POLARITY;

    if (   (  *(SERIAL2 + SERIAL_CONFIG_OFFSET)
            & (SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY))
        == (SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY    ))
          *(TIMER1 + TIMER_PRESCALE_OFFSET)
        = 17 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
          *(TIMER1 + TIMER_PRESCALE_OFFSET)
        = 23 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) void cmp_neq_multi_bits()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) =   SERIAL_CONFIG_ENDIAN
                                        | SERIAL_CONFIG_POLARITY;

    if (   (  *(SERIAL2 + SERIAL_CONFIG_OFFSET)
            & (SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY))
        != (SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY    ))
          *(TIMER1 + TIMER_PRESCALE_OFFSET)
        = 29 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
          *(TIMER1 + TIMER_PRESCALE_OFFSET)
        = 31 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) void cmp_equ_mskd()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = 29 << SERIAL_CONFIG_TXPORT_POS;

    if (    (*(SERIAL2 + SERIAL_CONFIG_OFFSET) & SERIAL_CONFIG_TXPORT_MSK)
         == (17 << SERIAL_CONFIG_TXPORT_POS)                              )
        CHG_BITS(*(TIMER1 + TIMER_PRESCALE_OFFSET)  ,
                 TIMER_PRESCALE_PRESCALER_HIGH_MSK      ,
                 7 << TIMER_PRESCALE_PRESCALER_HIGH_POS);
    else
        CHG_BITS(*(TIMER1 + TIMER_PRESCALE_OFFSET)  ,
                 TIMER_PRESCALE_PRESCALER_HIGH_MSK      ,
                 17 << TIMER_PRESCALE_PRESCALER_HIGH_POS);
}


__attribute__((noinline)) void cmp_neq_mskd()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = 29 << SERIAL_CONFIG_TXPORT_POS;

    if (   (*(SERIAL2 + SERIAL_CONFIG_OFFSET) & SERIAL_CONFIG_TXPORT_MSK)
        != (17 << SERIAL_CONFIG_TXPORT_POS)                              )
        CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET),
                 SERIAL_CONFIG_DATALEN_MSK        ,
                 SERIAL_CONFIG_DATALEN_32_BITS    );
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void cmp_equ_reg()
{
      *(SERIAL2 + SERIAL_CONFIG_OFFSET)
    = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS;

    if (   *(SERIAL2 + SERIAL_CONFIG_OFFSET)
        == (SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS))
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 21 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 23 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) void cmp_neq_reg()
{
    uint32_t word   = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS;

    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = word;

    if (*(SERIAL2 + SERIAL_CONFIG_OFFSET) != word)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET)  = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN         ;
}



__attribute__((noinline)) void bits_val(
const uint32_t  config)
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= config;
}



__attribute__((noinline)) void call_bits_val_const()
{
    bits_val(SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void call_bits_val_var()
{
    bits_val(SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void constexpr_bits_array()
{
     (GPIO1 + GPIO_WORDS_OFFSET)[3] = 0x6    ;
    *(GPIO1 + GPIO_SET_OFFSET)      = 1 << 13;
}



__attribute__((noinline)) void runtime_bits_array()
{
    volatile unsigned   index = 3;

    (GPIO1 + GPIO_WORDS_OFFSET)[index] = 0x21;
}



__attribute__((noinline)) void bits_ref(
const uint32_t  *config)
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= *config;
}



__attribute__((noinline)) void call_bits_ref_const()
{
    uint32_t    config = SERIAL_CONFIG_MODE;

    bits_ref(&config);
}



__attribute__((noinline)) void call_bits_ref_var()
{
    uint32_t    config = SERIAL_CONFIG_MODE;

    bits_ref(&config);
}



__attribute__((noinline)) void mskd_val(
const uint32_t  mask,
const uint32_t  bits)
{
       *(SERIAL2 + SERIAL_CONFIG_OFFSET)
    = (*(SERIAL2 + SERIAL_CONFIG_OFFSET) & ~mask) | bits;
}



__attribute__((noinline)) void call_mskd_val_const()
{
    uint32_t    mask = SERIAL_CONFIG_DATALEN_MSK    ,
                bits = SERIAL_CONFIG_DATALEN_16_BITS;

    mskd_val(mask                     , bits                         );
    mskd_val(SERIAL_CONFIG_DATALEN_MSK, SERIAL_CONFIG_DATALEN_16_BITS);
}



__attribute__((noinline)) void call_mskd_val_var()
{
    uint32_t    mask = SERIAL_CONFIG_DATALEN_MSK    ,
                bits = SERIAL_CONFIG_DATALEN_16_BITS;

    mskd_val(mask                     , bits                         );
    mskd_val(SERIAL_CONFIG_DATALEN_MSK, SERIAL_CONFIG_DATALEN_16_BITS);
}





__attribute__((noinline)) void mskd_ref(
const uint32_t  *mask_bits)
{
       *(SERIAL2 + SERIAL_CONFIG_OFFSET)
    = (*(SERIAL2 + SERIAL_CONFIG_OFFSET) & ~mask_bits[0]) | mask_bits[1];
}



__attribute__((noinline)) void call_mskd_ref_const()
{
    uint32_t    mask_bits[2] = {SERIAL_CONFIG_DATALEN_MSK      ,
                                SERIAL_CONFIG_DATALEN_32_BITS};

    mskd_ref(mask_bits);
}



__attribute__((noinline)) void call_mskd_ref_var()
{
    uint32_t    mask_bits[2] = {SERIAL_CONFIG_DATALEN_MSK      ,
                                SERIAL_CONFIG_DATALEN_16_BITS};

    mskd_ref(mask_bits);
}



__attribute__((noinline)) void periph_bits(
volatile uint32_t*  serial)
{
    *(serial + SERIAL_CONFIG_OFFSET) |= SERIAL_CONFIG_POLARITY;
}

__attribute__((noinline)) void call_periph_bits()
{
    periph_bits(SERIAL2);
}



__attribute__((noinline)) void periph_bits_val(
volatile uint32_t*  serial,
const    uint32_t   bits  )
{
    *(serial + SERIAL_CONFIG_OFFSET) |= bits;
}

__attribute__((noinline)) void call_periph_bits_val()
{
    periph_bits_val(SERIAL2, SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void reg_bits_val(
volatile uint32_t*  config,
const    uint32_t   bits  )
{
    *config |= bits ;
}

__attribute__((noinline)) void call_reg_bits_val()
{
    reg_bits_val(SERIAL2 + SERIAL_CONFIG_OFFSET,
                 SERIAL_CONFIG_POLARITY        );
}



__attribute__((noinline)) void periph_bits_ref(
volatile uint32_t   *serial,
const    uint32_t   *bits  )
{
    *(serial + SERIAL_CONFIG_OFFSET) |= *bits;
}

__attribute__((noinline)) void call_periph_bits_ref()
{
    uint32_t    serial_config_polarity = SERIAL_CONFIG_POLARITY;

    periph_bits_ref(SERIAL2, &serial_config_polarity);
}



__attribute__((noinline)) void reg_bits_ref(
volatile uint32_t   *config,
const    uint32_t   *bits  )
{
    *config |= *bits ;
}

__attribute__((noinline)) void call_reg_bits_ref()
{
    uint32_t    serial_config_polarity = SERIAL_CONFIG_POLARITY;

    reg_bits_ref(SERIAL2 + SERIAL_CONFIG_OFFSET,
                 &serial_config_polarity       );
}



__attribute__((noinline)) void periph_mskd(
volatile uint32_t   *serial)
{
    CHG_BITS(*(serial + SERIAL_CONFIG_OFFSET),
             SERIAL_CONFIG_DATALEN_MSK,
             SERIAL_CONFIG_DATALEN_16_BITS);
}

__attribute__((noinline)) void call_periph_mskd()
{
    periph_mskd(SERIAL2);
}



__attribute__((noinline)) void periph_mskd_val(
volatile uint32_t   *serial,
const    uint32_t    mask  ,
const    uint32_t    bits  )
{
    CHG_BITS(*(serial + SERIAL_CONFIG_OFFSET), mask, bits);
}

__attribute__((noinline)) void call_periph_mskd_val()
{
    periph_mskd_val(SERIAL2,
                    SERIAL_CONFIG_DATALEN_MSK,
                    SERIAL_CONFIG_DATALEN_16_BITS);
}



__attribute__((noinline)) void reg_mskd_val(
volatile uint32_t*  config,
const uint32_t      mask  ,
const uint32_t      bits  )
{
    CHG_BITS(*config, mask, bits);
}

__attribute__((noinline)) void call_reg_mskd_val()
{
    reg_mskd_val(SERIAL2 + SERIAL_CONFIG_OFFSET,
                 SERIAL_CONFIG_DATALEN_MSK,
                 SERIAL_CONFIG_DATALEN_16_BITS);
}



__attribute__((noinline)) void periph_mskd_ref(
volatile uint32_t*          serial   ,
const    uint32_t* const    mask_bits)
{
    CHG_BITS(*(serial + SERIAL_CONFIG_OFFSET), mask_bits[0], mask_bits[1]);
}

__attribute__((noinline)) void call_periph_mskd_ref()
{
    uint32_t    mask_bits[2] = { SERIAL_CONFIG_DATALEN_MSK,
                                 SERIAL_CONFIG_DATALEN_16_BITS
                               };

    periph_mskd_ref(SERIAL2, mask_bits);
}



__attribute__((noinline)) void reg_mskd_ref(
volatile uint32_t           *config   ,
const    uint32_t* const     mask_bits)
{
    CHG_BITS(*config, mask_bits[0], mask_bits[1]);
}

__attribute__((noinline)) void call_reg_mskd_ref()
{
    uint32_t    mask_bits[2] = { SERIAL_CONFIG_DATALEN_MSK,
                                 SERIAL_CONFIG_DATALEN_16_BITS
                               };

    reg_mskd_ref(SERIAL2 + SERIAL_CONFIG_OFFSET, mask_bits);
}



__attribute__((noinline)) uint32_t return_bits()
{
    return SERIAL_CONFIG_ENDIAN;
}



__attribute__((noinline)) void call_return_bits()
{
    uint32_t    config_bits = return_bits();

    if (config_bits == SERIAL_CONFIG_ENDIAN)
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 21 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 31 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) void return_mskd(
uint32_t    *mask,
uint32_t    *bits)
{
    *mask = SERIAL_CONFIG_PARITY_MSK ;
    *bits = SERIAL_CONFIG_PARITY_EVEN;
}



__attribute__((noinline)) void call_return_mskd()
{
    uint32_t    mask,
                bits;

    return_mskd(&mask, &bits);

    if (mask == SERIAL_CONFIG_PARITY_MSK && bits == SERIAL_CONFIG_PARITY_EVEN)
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 17 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 19 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) volatile uint32_t* return_reg()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;

    return &*(SERIAL2 + SERIAL_CONFIG_OFFSET);
}



__attribute__((noinline)) void call_return_reg()
{
    volatile uint32_t*  config = return_reg();

    if (*config == SERIAL_CONFIG_POLARITY)
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 15 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 23 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) volatile uint32_t* return_periph()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;

    return SERIAL2;
}



__attribute__((noinline)) void call_return_periph()
{
    volatile uint32_t*      serial = return_periph();

    if (*(serial + SERIAL_CONFIG_OFFSET) == SERIAL_CONFIG_POLARITY)
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 19 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
    else
        *(TIMER1 + TIMER_PRESCALE_OFFSET)  = 21 << TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) void pos_val(
const uint8_t       pos)
{
    if (pos == SERIAL_CONFIG_ENDIAN_POS)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 0x33;
    else if (pos == SERIAL_CONFIG_POLARITY_POS)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 0x44;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 0x55;
}



__attribute__((noinline)) void call_pos_val()
{
    pos_val(SERIAL_CONFIG_ENDIAN_POS);

    uint8_t     pos = SERIAL_CONFIG_POLARITY_POS;

    pos_val(pos);
}



__attribute__((noinline)) void pos_ref(
const uint8_t       *pos)
{
    if (*pos == SERIAL_CONFIG_ENDIAN_POS)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 0x66;
    else if (*pos == SERIAL_CONFIG_POLARITY_POS)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 0x77;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 0x88;
}



__attribute__((noinline)) void call_pos_ref()
{
    uint8_t     pos = SERIAL_CONFIG_ENDIAN_POS;

    pos_ref(&pos);
    pos_ref(&pos);
}



__attribute__((noinline)) void runtime_range_val(
uint32_t    mask  ,
uint32_t    txport)
{
    CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET), mask, txport);
}



__attribute__((noinline)) void call_range_val(
unsigned    port)
{
    runtime_range_val(           SERIAL_CONFIG_TXPORT_MSK ,
                        (port << SERIAL_CONFIG_TXPORT_POS)
                      &          SERIAL_CONFIG_TXPORT_MSK );
}



__attribute__((noinline)) void call_range_val_port()
{
    call_range_val(31);
}




__attribute__((noinline)) void runtime_range_ref(
const uint32_t* const   mask_txport)
{
    CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET), mask_txport[0], mask_txport[1]);
}



__attribute__((noinline)) void call_range_ref(
unsigned    port)
{

    uint32_t    msk_txport[2] = {           SERIAL_CONFIG_TXPORT_MSK ,
                                 (  port << SERIAL_CONFIG_TXPORT_POS)
                                  &         SERIAL_CONFIG_TXPORT_MSK };

    runtime_range_ref(msk_txport);
}



__attribute__((noinline)) void call_range_ref_port()
{
    call_range_ref(0xc);
}


__attribute__((noinline)) void check_array_range_pass(
const unsigned  port)
{
    if (port <= GPIO_MAX_PORT_NUM)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 127;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 131;
}



__attribute__((noinline)) void check_array_range_fail(
const unsigned  port)
{
    if (port <= GPIO_MAX_PORT_NUM)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 149;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 151;
}



__attribute__((noinline)) void check_bits_range_pass(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 157;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 163;
}



__attribute__((noinline)) void check_bits_range_fail(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 167;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 173;
}



__attribute__((noinline)) void check_mskd_range_pass(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 179;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 181;
}



__attribute__((noinline)) void check_mskd_range_fail(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 191;
    else
        (GPIO1 + GPIO_WORDS_OFFSET)[3] = 193;
}



__attribute__((noinline)) void prescaler_low()
{
      *(TIMER1 + TIMER_PRESCALE_OFFSET)
    = 119 << TIMER_PRESCALE_PRESCALER_LOW_POS;

      (GPIO1 + GPIO_WORDS_OFFSET)[3]
    =    (  *(TIMER1 + TIMER_PRESCALE_OFFSET)
          & TIMER_PRESCALE_PRESCALER_LOW_MSK)
      >> TIMER_PRESCALE_PRESCALER_LOW_POS;
}



__attribute__((noinline)) void prescaler_high()
{
      *(TIMER1 + TIMER_PRESCALE_OFFSET)
    = 29 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

      (GPIO1 + GPIO_WORDS_OFFSET)[3]
    =    (  *(TIMER1 + TIMER_PRESCALE_OFFSET)
          & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
      >> TIMER_PRESCALE_PRESCALER_HIGH_POS;
}



__attribute__((noinline)) void reg_mskd_lss()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 27 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

    if (  (*(TIMER1 + TIMER_PRESCALE_OFFSET) & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
        < (28 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_leq()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 23 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

    if (   (   (*(TIMER1 + TIMER_PRESCALE_OFFSET) & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
            <= (23 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        && (   (*(TIMER1 + TIMER_PRESCALE_OFFSET) & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
            <= (24 << TIMER_PRESCALE_PRESCALER_HIGH_POS)))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_gtr()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 19 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

    if (  (*(TIMER1 + TIMER_PRESCALE_OFFSET) & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
        > (18 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_geq()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 17 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

    if (   (   (*(TIMER1 + TIMER_PRESCALE_OFFSET) & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
            >= (16 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        && (   (*(TIMER1 + TIMER_PRESCALE_OFFSET) & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
            >= (17 << TIMER_PRESCALE_PRESCALER_HIGH_POS)))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void pos_cmp_eq()
{
    uint32_t    duplicate = SERIAL_CONFIG_ENDIAN_POS;

    if (duplicate == SERIAL_CONFIG_ENDIAN_POS)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void pos_cmp_ne()
{
    uint32_t    duplicate = SERIAL_CONFIG_POLARITY_POS;

    if (duplicate == SERIAL_CONFIG_POLARITY_POS)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void bits_extract_eq()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;

    uint32_t    extracted = *(SERIAL2 + SERIAL_CONFIG_OFFSET);

    if (extracted == SERIAL_CONFIG_POLARITY)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void bits_extract_ne()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN;

    uint32_t    extracted = *(SERIAL2 + SERIAL_CONFIG_OFFSET);

    if (extracted != SERIAL_CONFIG_ENDIAN)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void mskd_extract_eq()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;

    uint32_t    mask = SERIAL_CONFIG_DATALEN_MSK,
                valu = *(SERIAL2 + SERIAL_CONFIG_OFFSET)            ;

    if ((valu & mask) == SERIAL_CONFIG_DATALEN_16_BITS)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}

__attribute__((noinline)) void mskd_extract_ne()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;

    uint32_t    mask = SERIAL_CONFIG_DATALEN_MSK,
                valu = *(SERIAL2 + SERIAL_CONFIG_OFFSET)            ;

    if ((valu & mask) != SERIAL_CONFIG_DATALEN_32_BITS)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}

__attribute__((noinline)) void mskd_extract_lss()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (11 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    mask = TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                valu = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if ((valu & mask) < (12 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}

__attribute__((noinline)) void mskd_extract_leq()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (23 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    mask = TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                valu = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (   (valu & mask) <= (23 << TIMER_PRESCALE_PRESCALER_HIGH_POS)
        && (valu & mask) <= (24 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}

__attribute__((noinline)) void mskd_extract_gtr()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (19 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    mask = TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                valu = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if ((valu & mask) > (18 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}

__attribute__((noinline)) void mskd_extract_geq()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (11 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    mask = TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                valu = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (   (valu & mask) >= (10 << TIMER_PRESCALE_PRESCALER_HIGH_POS)
        && (valu & mask) >= (11 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_ENDIAN;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void set_bits_global()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) |= SERIAL_CONFIG_BITS;
}

__attribute__((noinline)) void ins_mskd_global()
{
    CHG_BITS(*(SERIAL2 + SERIAL_CONFIG_OFFSET),
             SERIAL_CONFIG_MASK,
             SERIAL_CONFIG_MSKD);
}

__attribute__((noinline)) void assign_array_global()
{
    *GPIO_WORDS = 189;
}

__attribute__((noinline)) void shifted_global()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 23 << TIMER_PRESCALER_SHFT;

      (GPIO1 + GPIO_WORDS_OFFSET)[3]
    =    (*(TIMER1 + TIMER_PRESCALE_OFFSET) & TIMER_PRESCALER_MASK)
      >> TIMER_PRESCALER_SHFT;
}

__attribute__((noinline)) void assign_register_global()
{
    *(SERIAL + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void call_pos_val_global()
{
    pos_val(SERIAL_CONFIG_POS);
}

__attribute__((noinline)) void call_pos_ref_global()
{
    uint8_t serial_config_pos = SERIAL_CONFIG_POS;

    pos_ref(&serial_config_pos);
}

__attribute__((noinline)) void call_bits_val_global()
{
    bits_val(SERIAL_CONFIG_BITS);
}

__attribute__((noinline)) void call_bits_ref_global()
{
    uint32_t serial_config_bits = SERIAL_CONFIG_BITS    ;

    bits_ref(&serial_config_bits);
}

__attribute__((noinline)) void call_mskd_val_global()
{
    mskd_val(SERIAL_CONFIG_MASK, SERIAL_CONFIG_MSKD);
}

__attribute__((noinline)) void call_mskd_ref_global()
{
    uint32_t    mask_bits[2] = {SERIAL_CONFIG_MASK,
                                SERIAL_CONFIG_MSKD};

    mskd_ref(mask_bits);
}


__attribute__((noinline)) void shifted_val(
uint32_t    mask,
uint32_t    shft)
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 23 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

      (GPIO1 + GPIO_WORDS_OFFSET)[3]
    = (*(TIMER1 + TIMER_PRESCALE_OFFSET) & mask) >> shft;
}

__attribute__((noinline)) void call_shifted_const_val()
{
    shifted_val(TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                TIMER_PRESCALE_PRESCALER_HIGH_POS);
}

__attribute__((noinline)) void call_shifted_var_val()
{
    uint32_t    mask = TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                shft = TIMER_PRESCALE_PRESCALER_HIGH_POS;

    shifted_val(mask, shft);
}

__attribute__((noinline)) void call_shifted_global_val()
{
    shifted_val(TIMER_PRESCALER_MASK, TIMER_PRESCALER_SHFT);
}

__attribute__((noinline)) void shifted_ref(
const uint32_t* const   mask_shft)
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 23 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

      (GPIO1 + GPIO_WORDS_OFFSET)[3]
    = (*(TIMER1 + TIMER_PRESCALE_OFFSET) & mask_shft[0]) >> mask_shft[1];
}

__attribute__((noinline)) void call_shifted_const_ref()
{
    uint32_t    mask_shft[2] = {TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                                TIMER_PRESCALE_PRESCALER_HIGH_POS};

    shifted_ref(mask_shft);
}

__attribute__((noinline)) void call_shifted_var_ref()
{
    uint32_t    mask_shft[2] = {TIMER_PRESCALE_PRESCALER_HIGH_MSK,
                                TIMER_PRESCALE_PRESCALER_HIGH_POS};

    shifted_ref(mask_shft);
}

__attribute__((noinline)) void call_shifted_global_ref()
{
    uint32_t    mask_shft[2] = {TIMER_PRESCALER_MASK,
                                TIMER_PRESCALER_SHFT};

    shifted_ref(mask_shft);
}



__attribute__((noinline)) void copy_bits_equ()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY ;

    uint32_t copy = *(SERIAL2 + SERIAL_CONFIG_OFFSET);

    if (copy & SERIAL_CONFIG_POLARITY_MSK)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_bits_neq()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY ;

    uint32_t copy = *(SERIAL2 + SERIAL_CONFIG_OFFSET);

    if ((copy & SERIAL_CONFIG_POLARITY_MSK) != SERIAL_CONFIG_POLARITY)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_equ()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = 11 << TIMER_PRESCALE_PRESCALER_HIGH_POS;

    uint32_t    copy = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (   (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
        == (11 << TIMER_PRESCALE_PRESCALER_HIGH_POS)     )
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_neq()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (11 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    copy = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (   (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
        != (11 << TIMER_PRESCALE_PRESCALER_HIGH_POS)     )
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_lss()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (27 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    copy = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (  (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
        < ((28 << TIMER_PRESCALE_PRESCALER_HIGH_POS))   )
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_leq()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (23 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    copy = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (   (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK) <= (23 << TIMER_PRESCALE_PRESCALER_HIGH_POS)
        && (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK) <= (24 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_gtr()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (19 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    copy = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (  (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
        > (18 << TIMER_PRESCALE_PRESCALER_HIGH_POS)     )
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_geq()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (17 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    copy = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if (   (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK) >= (16 << TIMER_PRESCALE_PRESCALER_HIGH_POS)
        && (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK) >= (17 << TIMER_PRESCALE_PRESCALER_HIGH_POS))
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_shifted()
{
    *(TIMER1 + TIMER_PRESCALE_OFFSET) = (11 << TIMER_PRESCALE_PRESCALER_HIGH_POS);

    uint32_t    copy = *(TIMER1 + TIMER_PRESCALE_OFFSET);

    if ((    (copy & TIMER_PRESCALE_PRESCALER_HIGH_MSK)
              >> TIMER_PRESCALE_PRESCALER_HIGH_POS     )
          == 11 )
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_bits_val(
const uint32_t copy)
{
    if ((copy & SERIAL_CONFIG_POLARITY_MSK) == SERIAL_CONFIG_POLARITY)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void call_copy_bits_val()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY ;

    uint32_t copy = *(SERIAL2 + SERIAL_CONFIG_OFFSET);

    copy_bits_val(copy);
}

__attribute__((noinline)) void copy_bits_ref(
const uint32_t  *copy)
{
    if ((*copy & SERIAL_CONFIG_POLARITY_MSK) == SERIAL_CONFIG_POLARITY)
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void call_copy_bits_ref()
{
    *(SERIAL2 + SERIAL_CONFIG_OFFSET) = SERIAL_CONFIG_POLARITY ;

    uint32_t copy = *(SERIAL2 + SERIAL_CONFIG_OFFSET);

    copy_bits_ref(&copy);
}






extern void do_test(void                        (*test)(),
                    volatile uint32_t* const      regster,
                    uint32_t                      testnum);


__attribute__((noinline)) void run()
{
    typedef volatile uint32_t* const        ptr_t;

    static ptr_t
    serial2_config  = (ptr_t)(   SERIAL2 + SERIAL_CONFIG_OFFSET  ),
    timer1_prescale = (ptr_t)(   TIMER1  + TIMER_PRESCALE_OFFSET ),
    gpio1_words_3   = (ptr_t)(&((GPIO1   + GPIO_WORDS_OFFSET)[3]));

#include "do_tests.inl"

}  // run()
