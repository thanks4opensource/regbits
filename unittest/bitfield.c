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
#include "mcu_bitfield.h"


static const enum SERIAL_CONFIG     SERIAL_CONFIG_BITS = POLARITY,
                                    SERIAL_CONFIG_MASK = DATALEN ;

static const uint32_t       SERIAL_CONFIG_MSKD = SERIAL_CONFIG_DATALEN_16_BITS;

static const enum TIMER_PRESCALE    TIMER_PRESCALER_SHIFT = PRESCALER_HIGH;


static volatile uint32_t* const  GPIO_WORDS = &((gpio_t*)(GPIO1_BASE))->words[3];
static          serial_t* const  SERIAL     = (serial_t*)(SERIAL2_BASE)         ;




__attribute__((noinline)) void zero_reg()
{
    SERIAL2->config  .word = 0;
}



__attribute__((noinline)) void zero_array()
{
    GPIO1  ->words[3]      = 0;
}



__attribute__((noinline)) void set_singl_bits_operator()
{
    SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void set_singl_bits_method()
{
    SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void clr_singl_bits_operator()
{
    SERIAL2->config.polarity = 0;
}



__attribute__((noinline)) void clr_singl_bits_method()
{
    SERIAL2->config.polarity = 0;
}



__attribute__((noinline)) void set_singl_mskd_operator()
{
    SERIAL2->config.datalen |= 1;
}



__attribute__((noinline)) void set_singl_mskd_method()
{
    SERIAL2->config.datalen |= 1;
}



__attribute__((noinline)) void clr_singl_mskd_operator()
{
    SERIAL2->config.datalen &= ~SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void clr_singl_mskd_method()
{
    SERIAL2->config.datalen &= ~SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_singl_bits_operator()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_singl_bits_method()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_singl_mskd_operator()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_singl_mskd_method()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void flp_singl_bits_operator()
{
    SERIAL2->config.polarity = !SERIAL2->config.polarity;
}



__attribute__((noinline)) void flp_singl_bits_method()
{
    SERIAL2->config.polarity = !SERIAL2->config.polarity;
}



__attribute__((noinline)) void flp_singl_mskd_operator()
{
    SERIAL2->config.datalen ^= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void flp_singl_mskd_method()
{
    SERIAL2->config.datalen ^= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void ins_singl_mskd_operator()
{
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void ins_singl_mskd_method()
{
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void set_multi_bits_operator()
{
    SERIAL2->config.mode   = 1;
    SERIAL2->config.endian = 1;
}



__attribute__((noinline)) void set_multi_bits_method()
{
    SERIAL2->config.mode   = 1;
    SERIAL2->config.endian = 1;
}



__attribute__((noinline)) void ins_multi_mskd_operator()
{
    SERIAL2->config.rxport   = 3;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void ins_multi_mskd_method()
{
    SERIAL2->config.rxport   = 3;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_multi_bits_operator()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_multi_bits_method()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_multi_mskd_operator()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.parity   = SERIAL_CONFIG_PARITY_EVEN;
    SERIAL2->config.rxport   = 6;
}



__attribute__((noinline)) void equ_multi_mskd_method()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.parity   = SERIAL_CONFIG_PARITY_EVEN;
    SERIAL2->config.rxport   = 6;
}



__attribute__((noinline)) void equ_bits_mskd_operator()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_bits_mskd_method()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_mskd_bits_operator()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_32_BITS;
    SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void equ_mskd_bits_method()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_32_BITS;
    SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void equ_bits_var()
{
    uint32_t    config = SERIAL_CONFIG_POLARITY;

    SERIAL2->config.word     = 0     ;
    SERIAL2->config.polarity = config;

    config = SERIAL_CONFIG_MODE;

    SERIAL2->config.word     = 0 ;
    SERIAL2->config.mode = config;
}



__attribute__((noinline)) void equ_mskd_var()
{
    uint32_t    config = SERIAL_CONFIG_DATALEN_16_BITS;

    SERIAL2->config.word     = 0    ;
    SERIAL2->config.datalen = config;

    config = 3;

    SERIAL2->config.word     = 0    ;
    SERIAL2->config.rxport = config;
}



__attribute__((noinline)) void cmp_equ_zero()
{
    SERIAL2->config.word = 0;

    TIMER1->prescale.word = 0;
    if (SERIAL2->config.word == 0)
        TIMER1->prescale.prescaler_high = 29;
    else
        TIMER1->prescale.prescaler_high = 17;
}



__attribute__((noinline)) void cmp_neq_zero()
{
    SERIAL2->config.word   =  0;

    if (SERIAL2->config.word != 0)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
    else
        SERIAL2->config.endian  = 1;
}



__attribute__((noinline)) void cmp_equ_bits()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.polarity = 1;

    if (SERIAL2->config.polarity)
        TIMER1->prescale.prescaler_high = 11;
    else
        TIMER1->prescale.prescaler_high = 13;

}



__attribute__((noinline)) void cmp_neq_bits()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.polarity = 1;

    if (!SERIAL2->config.polarity) {
        SERIAL2->config.word     = 0;
        SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
    }
    else {
        SERIAL2->config.word     = 0;
        SERIAL2->config.endian   = 1                            ;
    }
}



__attribute__((noinline)) void cmp_equ_multi_bits()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.endian   = 1;
    SERIAL2->config.polarity = 1;

    if (SERIAL2->config.endian && SERIAL2->config.polarity) {
        TIMER1->prescale.word           =  0;
        TIMER1->prescale.prescaler_high = 17;
    }
    else {
        TIMER1->prescale.word           =  0;
        TIMER1->prescale.prescaler_high = 23;
    }
}



__attribute__((noinline)) void cmp_neq_multi_bits()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.endian   = 1;
    SERIAL2->config.polarity = 1;

    if (!SERIAL2->config.endian && !SERIAL2->config.polarity) {
        TIMER1->prescale.word           =  0;
        TIMER1->prescale.prescaler_high = 29;
    }
    else {
        TIMER1->prescale.word           =  0;
        TIMER1->prescale.prescaler_high = 31;
    }
}



__attribute__((noinline)) void cmp_equ_mskd()
{
    SERIAL2->config.word   =  0;
    SERIAL2->config.txport = 29;

    if (SERIAL2->config.txport == 17)
        TIMER1->prescale.prescaler_high = 7;
    else
        TIMER1->prescale.prescaler_high = 17;
}



__attribute__((noinline)) void cmp_neq_mskd()
{
    SERIAL2->config.word   =  0;
    SERIAL2->config.txport = 29;

    if (SERIAL2->config.txport != 17)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
    else
        SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void cmp_equ_reg()
{
    SERIAL2->config.word    = 0                              ;
    SERIAL2->config.endian  = 1                              ;
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;

    if (   SERIAL2->config.mode  == 0
        && SERIAL2->config.datalen   == SERIAL_CONFIG_DATALEN_16_BITS
        && SERIAL2->config.mode  == 0
        && SERIAL2->config.endian    == 1
        && SERIAL2->config.polarity == 0
        && SERIAL2->config.rxport    == 0
        && SERIAL2->config.txport    == 0) {
        TIMER1->prescale.word           = 0 ;
        TIMER1->prescale.prescaler_high = 21;
    }
    else {
        TIMER1->prescale.word           = 0 ;
        TIMER1->prescale.prescaler_high = 23;
    }
}



__attribute__((noinline)) void cmp_neq_reg()
{
    SERIAL2->config.word    = 0                              ;
    SERIAL2->config.endian  = 1                              ;
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;

    if (!(   SERIAL2->config.mode      == 0
          && SERIAL2->config.datalen  == SERIAL_CONFIG_DATALEN_16_BITS
          && SERIAL2->config.mode      == 0
          && SERIAL2->config.endian   == 1
          && SERIAL2->config.polarity == 0
          && SERIAL2->config.rxport   == 0
          && SERIAL2->config.txport   == 0)) {
        SERIAL2->config.word    = 0;
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    }
    else {
        SERIAL2->config.word   = 0;
        SERIAL2->config.endian = 1;
    }
}



__attribute__((noinline)) void bits_val(
const enum SERIAL_CONFIG    bit  ,
const uint32_t              value)
{
    switch (bit) {
        case MODE:
            SERIAL2->config.mode     = value;
            SERIAL2->config.mode     = value;
            break;
        case POLARITY:
            SERIAL2->config.polarity = value;
            SERIAL2->config.polarity = value;
            break;
        case ENDIAN:
            SERIAL2->config.endian   = value;
            SERIAL2->config.endian   = value;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_bits_val_const()
{
    bits_val(POLARITY, SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void call_bits_val_var()
{
    bits_val(POLARITY, SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void constexpr_bits_array()
{
    GPIO1->words[3]   = 0x6;
    GPIO1->set.word   = 0;
    GPIO1->set.port13 = 1;
}



__attribute__((noinline)) void runtime_bits_array()
{
    volatile unsigned   index = 3;

    GPIO1->words[index] = 0x21;

    index = 7;

    GPIO1->set.word  = 0;
    if (index == 7) GPIO1->set.port7 = 1;
}




__attribute__((noinline)) void bits_ref(
const enum SERIAL_CONFIG    *bit  ,
const uint32_t              *value)
{
    switch (*bit) {
        case MODE:
            SERIAL2->config.mode     = *value;
            SERIAL2->config.mode     = *value;
            break;
        case POLARITY:
            SERIAL2->config.polarity = *value;
            SERIAL2->config.polarity = *value;
            break;
        case ENDIAN:
            SERIAL2->config.endian   = *value;
            SERIAL2->config.endian   = *value;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_bits_ref_const()
{
    const enum SERIAL_CONFIG    config = MODE              ;
    const uint32_t              value  = SERIAL_CONFIG_MODE;

    bits_ref(&config, &value);
}



__attribute__((noinline)) void call_bits_ref_var()
{
    const enum SERIAL_CONFIG    config = MODE              ;
    const uint32_t              value  = SERIAL_CONFIG_MODE;

    bits_ref(&config, &value);
}



__attribute__((noinline)) void mskd_val(
const enum SERIAL_CONFIG    config ,
const uint32_t              value)
{
    switch (config) {
        case MODE:
            SERIAL2->config.mode     = value;
            SERIAL2->config.mode     = value;
            break;
        case DATALEN:
            SERIAL2->config.datalen  = value;
            SERIAL2->config.datalen  = value;
            break;
        case PARITY:
            SERIAL2->config.parity   = value;
            SERIAL2->config.parity   = value;
            break;
        case ENDIAN:
            SERIAL2->config.endian   = value;
            SERIAL2->config.endian   = value;
            break;
        case POLARITY:
            SERIAL2->config.parity   = value;
            SERIAL2->config.parity   = value;
            break;
        case RXPORT:
            SERIAL2->config.rxport   = value;
            SERIAL2->config.rxport   = value;
            break;
        case TXPORT:
            SERIAL2->config.txport   = value;
            SERIAL2->config.txport   = value;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_mskd_val_const()
{
    uint32_t    bits = SERIAL_CONFIG_DATALEN_16_BITS;

    mskd_val(DATALEN, bits                          );
    mskd_val(DATALEN, SERIAL_CONFIG_DATALEN_16_BITS);
}



__attribute__((noinline)) void call_mskd_val_var()
{
    uint32_t    bits = SERIAL_CONFIG_DATALEN_16_BITS;

    mskd_val(DATALEN, bits                          );
    mskd_val(DATALEN, SERIAL_CONFIG_DATALEN_16_BITS);
}




__attribute__((noinline)) void mskd_ref(
const enum SERIAL_CONFIG    *config ,
const uint32_t              *value)
{
    switch (*config) {
        case MODE:
            SERIAL2->config.mode     = *value;
            SERIAL2->config.mode     = *value;
            break;
        case DATALEN:
            SERIAL2->config.datalen  = *value;
            SERIAL2->config.datalen  = *value;
            break;
        case PARITY:
            SERIAL2->config.parity   = *value;
            SERIAL2->config.parity   = *value;
            break;
        case ENDIAN:
            SERIAL2->config.endian   = *value;
            SERIAL2->config.endian   = *value;
            break;
        case POLARITY:
            SERIAL2->config.parity   = *value;
            SERIAL2->config.parity   = *value;
            break;
        case RXPORT:
            SERIAL2->config.rxport   = *value;
            SERIAL2->config.rxport   = *value;
            break;
        case TXPORT:
            SERIAL2->config.txport   = *value;
            SERIAL2->config.txport   = *value;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_mskd_ref_const()
{
    const enum SERIAL_CONFIG    config = DATALEN                      ;
    const uint32_t              value  = SERIAL_CONFIG_DATALEN_32_BITS;

    mskd_ref(&config, &value);
}



__attribute__((noinline)) void call_mskd_ref_var()
{
    const enum SERIAL_CONFIG    config = DATALEN                      ;
    const uint32_t              value  = SERIAL_CONFIG_DATALEN_16_BITS;

    mskd_ref(&config, &value);
}



__attribute__((noinline)) void periph_bits(
serial_t*               serial)
{
    serial->config.polarity = 1;
}

__attribute__((noinline)) void call_periph_bits()
{
    periph_bits(SERIAL2);
}



__attribute__((noinline)) void periph_bits_val(
serial_t*                   serial  ,
const enum SERIAL_CONFIG    polarity)
{
    switch (polarity) {
        case POLARITY:
            serial->config.polarity = 1;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_periph_bits_val()
{
    periph_bits_val(SERIAL2, POLARITY);
}



__attribute__((noinline)) void reg_bits_val(
union SERIAL_CONFIG_T       *config  ,
const enum SERIAL_CONFIG     polarity)
{
    switch (polarity) {
        case POLARITY:
            config->polarity = 1;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_reg_bits_val()
{
    reg_bits_val(&SERIAL2->config, POLARITY);
}



__attribute__((noinline)) void periph_bits_ref(
serial_t                    *serial ,
const enum SERIAL_CONFIG    *polarity)
{
    switch (*polarity) {
        case POLARITY:
            serial->config.polarity = 1;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_periph_bits_ref()
{
    const enum SERIAL_CONFIG    polarity = POLARITY;

    periph_bits_ref(SERIAL2, &polarity);
}



__attribute__((noinline)) void reg_bits_ref(
union SERIAL_CONFIG_T       *config  ,
const enum SERIAL_CONFIG     *polarity)
{
    switch (*polarity) {
        case POLARITY:
            config->polarity = 1;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_reg_bits_ref()
{
    const enum SERIAL_CONFIG    polarity = POLARITY;

    reg_bits_ref(&SERIAL2->config, &polarity);
}



__attribute__((noinline)) void periph_mskd(
serial_t*               serial)
{
    serial->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
}

__attribute__((noinline)) void call_periph_mskd()
{
    periph_mskd(SERIAL2);
}



__attribute__((noinline)) void periph_mskd_val(
serial_t*                   serial  ,
const enum SERIAL_CONFIG    datalen)
{
    switch (datalen) {
        case DATALEN:
            serial->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_periph_mskd_val()
{
    periph_mskd_val(SERIAL2, DATALEN);
}



__attribute__((noinline)) void reg_mskd_val(
union SERIAL_CONFIG_T       *config  ,
const enum SERIAL_CONFIG     datalen)
{
    switch (datalen) {
        case DATALEN:
            config->datalen = SERIAL_CONFIG_DATALEN_16_BITS;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_reg_mskd_val()
{
    reg_mskd_val(&SERIAL2->config, DATALEN);
}



__attribute__((noinline)) void periph_mskd_ref(
serial_t                    *serial ,
const enum SERIAL_CONFIG    *datalen)
{
    switch (*datalen) {
        case DATALEN:
            serial->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_periph_mskd_ref()
{
    const enum SERIAL_CONFIG    datalen = DATALEN;

    periph_mskd_ref(SERIAL2, &datalen);
}



__attribute__((noinline)) void reg_mskd_ref(
union SERIAL_CONFIG_T       *config  ,
const enum SERIAL_CONFIG     *datalen)
{
    switch (*datalen) {
        case DATALEN:
            config->datalen = SERIAL_CONFIG_DATALEN_16_BITS;
            break;
        default:
            break;
    }
}

__attribute__((noinline)) void call_reg_mskd_ref()
{
    const enum SERIAL_CONFIG    datalen = DATALEN;

    reg_mskd_ref(&SERIAL2->config, &datalen);
}



__attribute__((noinline)) uint32_t return_bits()
{
    return SERIAL_CONFIG_ENDIAN;
}



__attribute__((noinline)) void call_return_bits()
{
    uint32_t    config_bits = return_bits();

    TIMER1->prescale.word = 0;

    if (config_bits == SERIAL_CONFIG_ENDIAN)
        TIMER1->prescale.prescaler_high = 21;
    else
        TIMER1->prescale.prescaler_high = 31;
}



__attribute__((noinline)) void return_mskd(
enum SERIAL_CONFIG  *config,
uint32_t            *bits  )
{
    *config = PARITY                   ;
    *bits   = SERIAL_CONFIG_PARITY_EVEN;
}



__attribute__((noinline)) void call_return_mskd()
{
    enum SERIAL_CONFIG  config;
    uint32_t            bits  ;

    return_mskd(&config, &bits);

    TIMER1->prescale.word = 0;

    if (config == PARITY && bits == SERIAL_CONFIG_PARITY_EVEN)
        TIMER1->prescale.prescaler_high = 17;
    else
        TIMER1->prescale.prescaler_high = 19;
}



__attribute__((noinline)) volatile union SERIAL_CONFIG_T* return_reg()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.polarity = 1;

    return &SERIAL2->config;
}



__attribute__((noinline)) void call_return_reg()
{
    volatile union SERIAL_CONFIG_T      *config= return_reg();

    TIMER1->prescale.word = 0;

    if (config->polarity)
        TIMER1->prescale.prescaler_high = 15;
    else
        TIMER1->prescale.prescaler_high = 23;
}



__attribute__((noinline)) serial_t* return_periph()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.polarity = 1;

    return SERIAL2;
}



__attribute__((noinline)) void call_return_periph()
{
    serial_t*   serial = return_periph();

    if (serial->config.polarity)
        TIMER1->prescale.prescaler_high = 19;
    else
        TIMER1->prescale.prescaler_high = 21;
}



__attribute__((noinline)) void pos_val(
const enum SERIAL_CONFIG    pos)
{
    if (pos == ENDIAN)
        GPIO1->words[3] = 0x33;
    else if (pos == POLARITY)
        GPIO1->words[3] = 0x44;
    else
        GPIO1->words[3] = 0x55;
}



__attribute__((noinline)) void call_pos_val()
{
    pos_val(ENDIAN);

    enum SERIAL_CONFIG  pos = POLARITY;

    pos_val(pos);
}



__attribute__((noinline)) void pos_ref(
const enum SERIAL_CONFIG        *pos)
{
    if (*pos == ENDIAN)
        GPIO1->words[3] = 0x66;
    else if (*pos == POLARITY)
        GPIO1->words[3] = 0x77;
    else
        GPIO1->words[3] = 0x88;
}



__attribute__((noinline)) void call_pos_ref()
{
    enum SERIAL_CONFIG  pos = ENDIAN;

    pos_ref(&pos);
    pos_ref(&pos);
}




__attribute__((noinline)) void runtime_range_val(
uint8_t     txport)
{
    SERIAL2->config.txport = txport;
}



__attribute__((noinline)) void call_range_val(
unsigned    port)
{
    runtime_range_val(port);
}



__attribute__((noinline)) void call_range_val_port()
{
    call_range_val(31);
}




__attribute__((noinline)) void runtime_range_ref(
unsigned    *txport)
{
    SERIAL2->config.txport = *txport;
}



__attribute__((noinline)) void call_range_ref(
unsigned    port)
{
    runtime_range_ref(&port);
}



__attribute__((noinline)) void call_range_ref_port()
{
    call_range_ref(0xc);
}



__attribute__((noinline)) void check_array_range_pass(
const unsigned  port)
{
    if (port <= GPIO_MAX_PORT_NUM)
        GPIO1->words[3] = 127;
    else
        GPIO1->words[3] = 131;
}



__attribute__((noinline)) void check_array_range_fail(
const unsigned  port)
{
    if (port <= GPIO_MAX_PORT_NUM)
        GPIO1->words[3] = 149;
    else
        GPIO1->words[3] = 151;
}



__attribute__((noinline)) void check_bits_range_pass(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        GPIO1->words[3] = 157;
    else
        GPIO1->words[3] = 163;
}



__attribute__((noinline)) void check_bits_range_fail(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        GPIO1->words[3] = 167;
    else
        GPIO1->words[3] = 173;
}



__attribute__((noinline)) void check_mskd_range_pass(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        GPIO1->words[3] = 179;
    else
        GPIO1->words[3] = 181;
}



__attribute__((noinline)) void check_mskd_range_fail(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        GPIO1->words[3] = 191;
    else
        GPIO1->words[3] = 193;
}



__attribute__((noinline)) void prescaler_low()
{
    TIMER1->prescale.prescaler_low = 119;

    GPIO1->words[3] = TIMER1->prescale.prescaler_low;
}



__attribute__((noinline)) void prescaler_high()
{
    TIMER1->prescale.prescaler_high = 29;

    GPIO1->words[3] = TIMER1->prescale.prescaler_high;
}



__attribute__((noinline)) void reg_mskd_lss()
{
    TIMER1->prescale.prescaler_high = 27;

    SERIAL2->config.word = 0;

    if (TIMER1->prescale.prescaler_high < 28)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_leq()
{
    TIMER1->prescale.prescaler_high = 23;

    SERIAL2->config.word = 0;

    if (   TIMER1->prescale.prescaler_high <= 23
        && TIMER1->prescale.prescaler_high <= 24)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_gtr()
{
    TIMER1->prescale.prescaler_high = 19;

    SERIAL2->config.word = 0;

    if (TIMER1->prescale.prescaler_high > 18)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void reg_mskd_geq()
{
    TIMER1->prescale.prescaler_high = 17;

    SERIAL2->config.word = 0;

    if (   TIMER1->prescale.prescaler_high >= 16
        && TIMER1->prescale.prescaler_high >= 17)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void pos_cmp_eq()
{
    SERIAL2->config.word = 0;

    uint32_t    duplicate = ENDIAN;

    if (duplicate == ENDIAN)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void pos_cmp_ne()
{
    SERIAL2->config.word = 0;

    uint32_t    duplicate = POLARITY;

    if (duplicate == POLARITY)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void bits_extract_eq()
{
    SERIAL2->config.polarity = 1;

    union SERIAL_CONFIG_T   extracted;
                            extracted.word = SERIAL2->config.word;

    SERIAL2->config.word = 0;

    if (extracted.polarity)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void bits_extract_ne()
{
    SERIAL2->config.endian = 1;

    union SERIAL_CONFIG_T   extracted;
                            extracted.word = SERIAL2->config.word;

    SERIAL2->config.word = 0;

    if (!extracted.endian)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void mskd_extract_eq()
{
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;

    union SERIAL_CONFIG_T   extracted;
                            extracted.word = SERIAL2->config.word;

    SERIAL2->config.word = 0;

    if (extracted.datalen == SERIAL_CONFIG_DATALEN_16_BITS)
        SERIAL2->config.endian = 1;
    else
        SERIAL2->config.polarity = 1;
}

__attribute__((noinline)) void mskd_extract_ne()
{
    SERIAL2->config.word    = 0                            ;
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;

    union SERIAL_CONFIG_T   extracted;
                            extracted.word = SERIAL2->config.word;

    SERIAL2->config.word = 0;

    if (extracted.datalen != SERIAL_CONFIG_DATALEN_32_BITS)
        SERIAL2->config.endian = 1;
    else
        SERIAL2->config.polarity = 1;
}

__attribute__((noinline)) void mskd_extract_lss()
{
    TIMER1->prescale.   word        =  0;
    TIMER1->prescale.prescaler_high = 11;

    union TIMER_PRESCALE_T  extracted;
                            extracted.word = TIMER1->prescale.word;

    SERIAL2->config.word = 0;

    if (extracted.prescaler_high < 12)
        SERIAL2->config.endian = 1;
    else
        SERIAL2->config.polarity = 1;
}

__attribute__((noinline)) void mskd_extract_leq()
{
    TIMER1->prescale.word           =  0;
    TIMER1->prescale.prescaler_high = 23;

    union TIMER_PRESCALE_T  extracted;
                            extracted.word = TIMER1->prescale.word;

    SERIAL2->config.word = 0;

    if (   extracted.prescaler_high <= 23
        && extracted.prescaler_high <= 24)
        SERIAL2->config.endian = 1;
    else
        SERIAL2->config.polarity = 1;
}

__attribute__((noinline)) void mskd_extract_gtr()
{
    TIMER1->prescale.word           =  0;
    TIMER1->prescale.prescaler_high = 19;

    union TIMER_PRESCALE_T  extracted;
                            extracted.word = TIMER1->prescale.word;

    SERIAL2->config.word = 0;

    if (extracted.prescaler_high > 18)
        SERIAL2->config.endian = 1;
    else
        SERIAL2->config.polarity = 1;
}

__attribute__((noinline)) void mskd_extract_geq()
{
    TIMER1->prescale.word           =  0;
    TIMER1->prescale.prescaler_high = 11;

    union TIMER_PRESCALE_T  extracted;
                            extracted.word = TIMER1->prescale.word;

    SERIAL2->config.word = 0;

    if (   extracted.prescaler_high >= 10
        && extracted.prescaler_high >= 11)
        SERIAL2->config.endian = 1;
    else
        SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void set_bits_global()
{
    if (SERIAL_CONFIG_BITS == POLARITY)
        SERIAL2->config.polarity = 1;
}

__attribute__((noinline)) void ins_mskd_global()
{

    if (SERIAL_CONFIG_MSKD == DATALEN)
        SERIAL2->config.datalen = SERIAL_CONFIG_MSKD;
}

__attribute__((noinline)) void assign_array_global()
{
    *GPIO_WORDS = 189;
}

__attribute__((noinline)) void shifted_global()
{
    TIMER1->prescale.prescaler_high = 23;

    if (TIMER_PRESCALER_SHIFT == PRESCALER_HIGH)
        GPIO1->words[3] = TIMER1->prescale.prescaler_high;
}

__attribute__((noinline)) void assign_register_global()
{
    SERIAL->config.word    = 0                            ;
    SERIAL->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void call_pos_val_global()
{
    pos_val(SERIAL_CONFIG_BITS);
}

__attribute__((noinline)) void call_pos_ref_global()
{
    enum SERIAL_CONFIG  serial_config_bits = SERIAL_CONFIG_BITS;

    pos_ref(&serial_config_bits);
}

__attribute__((noinline)) void call_bits_val_global()
{
    bits_val(SERIAL_CONFIG_BITS, SERIAL_CONFIG_POLARITY);
}

__attribute__((noinline)) void call_bits_ref_global()
{
    enum SERIAL_CONFIG  serial_config_bits     = SERIAL_CONFIG_BITS    ;
    uint32_t            serial_config_polarity = SERIAL_CONFIG_POLARITY;

    bits_ref(&serial_config_bits, &serial_config_polarity);
}

__attribute__((noinline)) void call_mskd_val_global()
{
    mskd_val(SERIAL_CONFIG_MASK, SERIAL_CONFIG_MSKD);
}

__attribute__((noinline)) void call_mskd_ref_global()
{
    enum SERIAL_CONFIG  serial_config_mask = SERIAL_CONFIG_MASK;
    uint32_t            serial_config_mskd = SERIAL_CONFIG_MSKD;

    mskd_ref(&serial_config_mask, &serial_config_mskd);
}


__attribute__((noinline)) void shifted_val(
const enum TIMER_PRESCALE   shift)
{
    TIMER1->prescale.word           =  0;
    TIMER1->prescale.prescaler_high = 23;

    if (shift == PRESCALER_HIGH)
        GPIO1->words[3] = TIMER1->prescale.prescaler_high;
}

__attribute__((noinline)) void call_shifted_const_val()
{
    shifted_val(PRESCALER_HIGH);
}

__attribute__((noinline)) void call_shifted_var_val()
{
    enum TIMER_PRESCALE     shift = PRESCALER_HIGH;

    shifted_val(shift);
}

__attribute__((noinline)) void call_shifted_global_val()
{
    shifted_val(TIMER_PRESCALER_SHIFT);
}

__attribute__((noinline)) void shifted_ref(
const enum TIMER_PRESCALE   *shift)
{
    TIMER1->prescale.word           =  0;
    TIMER1->prescale.prescaler_high = 23;

    if (*shift == PRESCALER_HIGH)
        GPIO1->words[3] = TIMER1->prescale.prescaler_high;
}

__attribute__((noinline)) void call_shifted_const_ref()
{
    enum TIMER_PRESCALE     shift = PRESCALER_HIGH;

    shifted_ref(&shift);
}

__attribute__((noinline)) void call_shifted_var_ref()
{
    enum TIMER_PRESCALE     shift = PRESCALER_HIGH;

    shifted_ref(&shift);
}

__attribute__((noinline)) void call_shifted_global_ref()
{
    enum TIMER_PRESCALE     timer_prescaler_shift = TIMER_PRESCALER_SHIFT;

    shifted_ref(&timer_prescaler_shift);
}



__attribute__((noinline)) void copy_bits_equ()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;

    uint32_t     copy = SERIAL2->config.polarity;

    SERIAL2->config.word = 0;

    if (copy == SERIAL_CONFIG_POLARITY)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_bits_neq()
{
    SERIAL2->config.word     = 0                       ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY ;

    uint32_t     copy = SERIAL2->config.polarity;

    SERIAL2->config.word = 0;

    if (copy != SERIAL_CONFIG_POLARITY)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_equ()
{
    TIMER1->prescale.word      =  0;
    TIMER1->prescale.prescaler_high = 11;

    uint32_t     copy = TIMER1->prescale.prescaler_high;

    SERIAL2->config.word = 0;

    if (copy == 11)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_neq()
{
    TIMER1->prescale.word      =  0;
    TIMER1->prescale.prescaler_high = 13;

    uint32_t     copy = TIMER1->prescale.prescaler_high;

    SERIAL2->config.word = 0;

    if (copy != 13)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_lss()
{
    TIMER1->prescale.word      =  0;
    TIMER1->prescale.prescaler_high = 27;

    uint32_t     copy = TIMER1->prescale.prescaler_high;

    SERIAL2->config.word = 0;

    if (copy < 28)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_leq()
{
    TIMER1->prescale.word      =  0;
    TIMER1->prescale.prescaler_high = 23;

    uint32_t     copy = TIMER1->prescale.prescaler_high;

    SERIAL2->config.word = 0;

    if (   copy <= 23
        && copy <= 24)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_gtr()
{
    TIMER1->prescale.word      =  0;
    TIMER1->prescale.prescaler_high = 19;

    uint32_t     copy = TIMER1->prescale.prescaler_high;

    SERIAL2->config.word = 0;

    if (copy > 18)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_mskd_geq()
{
    TIMER1->prescale.word      =  0;
    TIMER1->prescale.prescaler_high = 17;

    uint32_t     copy = TIMER1->prescale.prescaler_high;

    SERIAL2->config.word = 0;

    if (   copy >= 16
        && copy >= 17)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_shifted()
{
    TIMER1->prescale.word      =  0;
    TIMER1->prescale.prescaler_high = 11;

    uint32_t     copy = TIMER1->prescale.prescaler_high ;

    SERIAL2->config.word = 0;

    if (copy == 11)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void copy_bits_val(
const uint32_t      copy)
{
    SERIAL2->config.word = 0;

    if (copy == SERIAL_CONFIG_POLARITY)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void call_copy_bits_val()
{
    SERIAL2->config.word     = 0                       ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY ;

    uint32_t     copy = SERIAL2->config.polarity;

    copy_bits_val(copy);
}

__attribute__((noinline)) void copy_bits_ref(
uint32_t    *copy)
{
    SERIAL2->config.word = 0;

    if (*copy == SERIAL_CONFIG_POLARITY)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}

__attribute__((noinline)) void call_copy_bits_ref()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;

    uint32_t     copy = SERIAL2->config.polarity;

    copy_bits_ref(&copy);
}






extern void do_test(void                        (*test)(),
                    volatile uint32_t* const      regster,
                    uint32_t                      testnum);


__attribute__((noinline)) void run()
{
    typedef volatile uint32_t* const        ptr_t;

    static ptr_t    serial2_config  = (ptr_t)(&SERIAL2->config  .word),
                    timer1_prescale = (ptr_t)(&TIMER1 ->prescale.word),
                    gpio1_words_3   = (ptr_t)(&GPIO1  ->words[3]     ),
                    gpio1_set       = (ptr_t)(&GPIO1  ->set     .word);

#include "do_tests.inl"

}  // run()
