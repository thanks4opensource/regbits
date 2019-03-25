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



__attribute__((noinline)) void zero()
{
    SERIAL2->config  .word = 0;
    TIMER1 ->prescale.word = 0;
    GPIO1  ->bytes[3]      = 0;
    GPIO1  ->set     .word = 0;
}



__attribute__((noinline)) void set_singl_bits()
{
    SERIAL2->config.polarity = 1;
    SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void clr_singl_bits()
{
    SERIAL2->config.polarity = 0;
    SERIAL2->config.polarity = 0;
}



__attribute__((noinline)) void set_singl_mskd()
{
    SERIAL2->config.datalen = 1;
    SERIAL2->config.datalen = 1;
}



__attribute__((noinline)) void clr_singl_mskd()
{
    SERIAL2->config.datalen = 0;
    SERIAL2->config.datalen = 0;
}



__attribute__((noinline)) void equ_singl_bits()
{
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_singl_mskd()
{
    SERIAL2->config.word    = 0                            ;
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void flp_singl_bits()
{
    SERIAL2->config.polarity = !SERIAL2->config.polarity;
    SERIAL2->config.polarity = !SERIAL2->config.polarity;
    SERIAL2->config.polarity = !SERIAL2->config.polarity;
}



__attribute__((noinline)) void flp_singl_mskd()
{
    SERIAL2->config.datalen ^= SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->config.datalen ^= SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->config.datalen ^= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void ins_singl_mskd()
{
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
    SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void set_multi_bits()
{
    SERIAL2->config.endian = 1;
    SERIAL2->config.mode   = 1;
    SERIAL2->config.endian = 1;
    SERIAL2->config.mode   = 1;
}



__attribute__((noinline)) void ins_multi_mskd()
{
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->config.rxport   = 3;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->config.rxport   = 3;
}



__attribute__((noinline)) void equ_multi_bits()
{
    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;

    SERIAL2->config.word     = 0                     ;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.polarity = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_multi_mskd()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.parity   = SERIAL_CONFIG_PARITY_EVEN;
    SERIAL2->config.rxport   = 6;

    SERIAL2->config.word     = 0;
    SERIAL2->config.parity   = SERIAL_CONFIG_PARITY_EVEN;
    SERIAL2->config.rxport   = 6;
}


__attribute__((noinline)) void equ_bits_mskd()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;

    SERIAL2->config.word     = 0;
    SERIAL2->config.endian   = SERIAL_CONFIG_ENDIAN  ;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_mskd_bits()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_32_BITS;
    SERIAL2->config.polarity = 1;

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



__attribute__((noinline)) void cmp_zero()
{
    SERIAL2->config.word = 0;
    SERIAL2->config.word = 0;

    TIMER1->prescale.word = 0;
    if (SERIAL2->config.word == 0)
        TIMER1->prescale.prescaler = 43;
    else
        TIMER1->prescale.prescaler = 17;

    if (SERIAL2->config.word != 0)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
    else
        SERIAL2->config.endian  = 1;
}



__attribute__((noinline)) void cmp_bits()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.polarity = 1;

    if (SERIAL2->config.polarity)
        TIMER1->prescale.prescaler = 11;
    else
        TIMER1->prescale.prescaler = 67;

    if (!SERIAL2->config.polarity) {
        SERIAL2->config.word     = 0;
        SERIAL2->config.datalen  = SERIAL_CONFIG_DATALEN_16_BITS;
    }
    else {
        SERIAL2->config.word     = 0;
        SERIAL2->config.endian   = 1                            ;
    }
}



__attribute__((noinline)) void cmp_mskd()
{
    SERIAL2->config.word   =  0;
    SERIAL2->config.txport = 29;

    if (SERIAL2->config.txport == 17)
        TIMER1->prescale.prescaler = 113;
    else
        TIMER1->prescale.prescaler = 173;

    if (SERIAL2->config.txport != 17)
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
    else
        SERIAL2->config.polarity = 1;
}



__attribute__((noinline)) void cmp_reg()
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
        TIMER1->prescale.word      = 0  ;
        TIMER1->prescale.prescaler = 223;
    }
    else {
        TIMER1->prescale.word      = 0  ;
        TIMER1->prescale.prescaler = 241;
    }

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



__attribute__((noinline)) void constexpr_bits_array()
{
    GPIO1->bytes[3]   = 0x6;
    GPIO1->set.word   = 0;
    GPIO1->set.port13 = 1;
}



__attribute__((noinline)) void runtime_bits_array()
{
    volatile unsigned   index = 3;

    GPIO1->bytes[index] = 0x21;

    index = 7;

    GPIO1->set.word  = 0;
    if (index == 7) GPIO1->set.port7 = 1;
}



__attribute__((noinline)) void call_bits_val()
{
    bits_val(POLARITY, SERIAL_CONFIG_POLARITY);
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



__attribute__((noinline)) void call_bits_ref()
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



__attribute__((noinline)) void call_mskd_val()
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



__attribute__((noinline)) void call_mskd_ref()
{
    const enum SERIAL_CONFIG    config_a = DATALEN                      ,
                                config_b = DATALEN                      ;
    const uint32_t              value_a  = SERIAL_CONFIG_DATALEN_16_BITS,
                                value_b  = SERIAL_CONFIG_DATALEN_32_BITS;

    mskd_ref(&config_a, &value_a);
    mskd_ref(&config_b, &value_b);

    SERIAL2->config.polarity = 0;  // clear for periph_reg_bits_val
}



__attribute__((noinline)) void periph_reg_bits_val(
      serial_t*             serial  ,
const enum SERIAL_CONFIG    polarity,
const uint32_t              bit     )
{
    switch (polarity) {
        case POLARITY:
            SERIAL2->config.polarity = bit;
            SERIAL2->config.polarity = bit;
            serial ->config.polarity = bit;
            serial ->config.polarity = bit;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_periph_reg_bits_val()
{
    periph_reg_bits_val(SERIAL2, POLARITY, SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void periph_reg_bits_ref(
         serial_t*              serial  ,
const    enum SERIAL_CONFIG*    polarity,
const    uint32_t* const        bit     )
{
    switch (*polarity) {
        case POLARITY:
            SERIAL2->config.polarity = *bit;
            SERIAL2->config.polarity = *bit;
            serial ->config.polarity = *bit;
            serial ->config.polarity = *bit;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_periph_reg_bits_ref()
{
    const enum SERIAL_CONFIG    polarity = POLARITY              ;
    const uint32_t              bit      = SERIAL_CONFIG_POLARITY;

    periph_reg_bits_ref(SERIAL2, &polarity, &bit);
}



__attribute__((noinline)) void periph_reg_mskd_val(
         serial_t*              serial ,
const    enum SERIAL_CONFIG     datalen,
const    uint32_t               mskd   )
{
    switch (datalen) {
        case DATALEN:
            SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
            SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_16_BITS;
            serial ->config.datalen = mskd;
            serial ->config.datalen = mskd;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_periph_reg_mskd_val()
{
    periph_reg_mskd_val(SERIAL2, DATALEN, SERIAL_CONFIG_DATALEN_16_BITS);
}



__attribute__((noinline)) void periph_reg_mskd_ref(
         serial_t*              serial ,
const    enum SERIAL_CONFIG*    datalen,
const    uint32_t*              mskd   )
{
    switch (*datalen) {
        case DATALEN:
            SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
            SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
            serial ->config.datalen = *mskd;
            serial ->config.datalen = *mskd;
            break;
        default:
            break;
    }
}



__attribute__((noinline)) void call_periph_reg_mskd_ref()
{
    const enum SERIAL_CONFIG    config = DATALEN                      ;
    const uint32_t              mskd   = SERIAL_CONFIG_DATALEN_32_BITS;

    periph_reg_mskd_ref(SERIAL2, &config, &mskd);
}



__attribute__((noinline)) uint32_t return_bits()
{
    return SERIAL_CONFIG_ENDIAN;
}



__attribute__((noinline)) void call_return_bits()
{
    uint32_t    config_bits = return_bits();

    if (config_bits == SERIAL_CONFIG_ENDIAN)
        TIMER1->prescale.prescaler  = 83;
    else
        TIMER1->prescale.prescaler  = 89;
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

    if (config == PARITY && bits == SERIAL_CONFIG_PARITY_EVEN)
        TIMER1->prescale.prescaler  = 157;
    else
        TIMER1->prescale.prescaler  = 163;
}



__attribute__((noinline)) volatile union CONFIG_T* return_reg()
{
    SERIAL2->config.word     = 0;
    SERIAL2->config.polarity = 1;

    return &SERIAL2->config;
}



__attribute__((noinline)) void call_return_reg()
{
    volatile union CONFIG_T     *config= return_reg();

    if (config->polarity)
        TIMER1->prescale.prescaler  = 53;
    else
        TIMER1->prescale.prescaler  = 59;
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
        TIMER1->prescale.prescaler  = 199;
    else
        TIMER1->prescale.prescaler  = 211;
}



__attribute__((noinline)) void pos_val(
const enum SERIAL_CONFIG    pos)
{
    if (pos == ENDIAN)
        GPIO1->bytes[3] = 0x33;
    else if (pos == POLARITY)
        GPIO1->bytes[3] = 0x44;
    else
        GPIO1->bytes[3] = 0x55;
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
        GPIO1->bytes[3] = 0x66;
    else if (*pos == POLARITY)
        GPIO1->bytes[3] = 0x77;
    else
        GPIO1->bytes[3] = 0x88;
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
    SERIAL2->config.rxport = port;
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
    SERIAL2->config.rxport = port;
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
        GPIO1->bytes[3] = 127;
    else
        GPIO1->bytes[3] = 131;
}



__attribute__((noinline)) void check_array_range_fail(
const unsigned  port)
{
    if (port <= GPIO_MAX_PORT_NUM)
        GPIO1->bytes[3] = 149;
    else
        GPIO1->bytes[3] = 151;
}



__attribute__((noinline)) void check_bits_range_pass(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        GPIO1->bytes[3] = 157;
    else
        GPIO1->bytes[3] = 163;
}



__attribute__((noinline)) void check_bits_range_fail(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        GPIO1->bytes[3] = 167;
    else
        GPIO1->bytes[3] = 173;
}



__attribute__((noinline)) void check_mskd_range_pass(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        GPIO1->bytes[3] = 179;
    else
        GPIO1->bytes[3] = 181;
}



__attribute__((noinline)) void check_mskd_range_fail(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        GPIO1->bytes[3] = 191;
    else
        GPIO1->bytes[3] = 193;
}



__attribute__((noinline)) void check_bits_extract()
{
    SERIAL2->config.polarity = 1;
    SERIAL2->config.endian   = 1;

    union CONFIG_T  extracted                          ;
                    extracted.word = SERIAL_CONFIG_MODE;

    extracted.word = SERIAL2->config.word;

    if (extracted.polarity && extracted.endian)
        GPIO1->bytes[3] = 199;
    else
        GPIO1->bytes[3] = 227;

    SERIAL2->config.word = 0;
    SERIAL2->config.mode = 1;

    extracted.word = SERIAL2->config.word;

    if (!extracted.mode) {
        SERIAL2->config.word   = 0;
        SERIAL2->config.endian = 1;
    }
    else {
        SERIAL2->config.word    = 0                            ;
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_32_BITS;
    }
}



__attribute__((noinline)) void check_mskd_extract()
{
    SERIAL2->config.rxport = 23;

    union CONFIG_T  extracted;
                    extracted.rxport = 11;

    extracted.word = SERIAL2->config.word;

    if (extracted.rxport == 23)
        GPIO1->bytes[3] = 229;
    else
        GPIO1->bytes[3] = 233;


    SERIAL2->config.rxport = 7                   ;
    extracted.word         = SERIAL2->config.word;

    if (extracted.rxport != 7) {
        SERIAL2->config.word   = 0                       ;
        SERIAL2->config.parity = SERIAL_CONFIG_PARITY_CRC;
    }
    else {
        SERIAL2->config.word   = 0;
        SERIAL2->config.endian = 1;
    }
}






extern void unittest_record_registers(unsigned,
                                      uint32_t,
                                      uint32_t,
                                      uint8_t ,
                                      uint32_t);

__attribute__((noinline)) void record_registers(
unsigned    test_num)
{
    unittest_record_registers(test_num,
                              SERIAL2->config  .word,
                              TIMER1 ->prescale.word,
                              GPIO1  ->bytes    [3] ,
                              GPIO1  ->set     .word);
}



__attribute__((noinline)) void run()
{
    zero();                     record_registers( 0);
    set_singl_bits();           record_registers( 1);
    clr_singl_bits();           record_registers( 2);
    set_singl_mskd();           record_registers( 3);
    clr_singl_mskd();           record_registers( 4);
    equ_singl_bits();           record_registers( 5);
    equ_singl_mskd();           record_registers( 6);
    flp_singl_bits();           record_registers( 7);
    flp_singl_mskd();           record_registers( 8);
    ins_singl_mskd();           record_registers( 9);
    set_multi_bits();           record_registers(10);
    ins_multi_mskd();           record_registers(11);
    equ_multi_bits();           record_registers(12);
    equ_multi_mskd();           record_registers(13);
    equ_bits_mskd();            record_registers(14);
    equ_mskd_bits();            record_registers(15);
    equ_bits_var();             record_registers(16);
    equ_mskd_var();             record_registers(17);
    cmp_zero();                 record_registers(18);
    cmp_bits();                 record_registers(19);
    cmp_mskd();                 record_registers(20);
    cmp_reg();                  record_registers(21);
    constexpr_bits_array();     record_registers(22);
    runtime_bits_array();       record_registers(23);
    call_bits_val();            record_registers(24);
    call_bits_ref();            record_registers(25);
    call_mskd_val();            record_registers(26);
    call_mskd_ref();            record_registers(27);
    call_periph_reg_bits_val(); record_registers(28);
    call_periph_reg_bits_ref(); record_registers(39);
    call_periph_reg_mskd_val(); record_registers(30);
    call_periph_reg_mskd_ref(); record_registers(31);
    call_return_bits();         record_registers(32);
    call_return_mskd();         record_registers(33);
    call_return_reg();          record_registers(34);
    call_return_periph();       record_registers(35);
    call_pos_val();             record_registers(36);
    call_pos_ref();             record_registers(37);
    check_array_range_pass(22); record_registers(38);
    check_array_range_fail(23); record_registers(39);
    check_bits_range_pass (31); record_registers(40);
    check_bits_range_fail (32); record_registers(41);
    check_mskd_range_pass (31); record_registers(42);
    check_mskd_range_fail (32); record_registers(43);
    check_bits_extract();       record_registers(44);
    check_mskd_extract();       record_registers(45);

}  // run()
