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
#include "mcu_struct.h"



__attribute__((noinline)) void zero()
{
    SERIAL2->CONFIG   = 0;
    TIMER1->PRESCALE  = 0;
    GPIO1  ->BYTES[3] = 0;
    GPIO1  ->SET      = 0;
}



__attribute__((noinline)) void set_singl_bits()
{
    SERIAL2->CONFIG |= SERIAL_CONFIG_POLARITY;
    SERIAL2->CONFIG |= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void clr_singl_bits()
{
    SERIAL2->CONFIG &= ~SERIAL_CONFIG_POLARITY;
    SERIAL2->CONFIG &= ~SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void set_singl_mskd()
{
    SERIAL2->CONFIG |= SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->CONFIG |= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void clr_singl_mskd()
{
    SERIAL2->CONFIG &= ~SERIAL_CONFIG_DATALEN_MSK;
    SERIAL2->CONFIG &= ~SERIAL_CONFIG_DATALEN_MSK;
}



__attribute__((noinline)) void equ_singl_bits()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_POLARITY;
    SERIAL2->CONFIG = SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_singl_mskd()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->CONFIG = SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void flp_singl_bits()
{
    SERIAL2->CONFIG ^= SERIAL_CONFIG_POLARITY;
    SERIAL2->CONFIG ^= SERIAL_CONFIG_POLARITY;
    SERIAL2->CONFIG ^= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void flp_singl_mskd()
{
    SERIAL2->CONFIG ^= SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->CONFIG ^= SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->CONFIG ^= SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void ins_singl_mskd()
{
    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_DATALEN_MSK,
             SERIAL_CONFIG_DATALEN_32_BITS);
    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_DATALEN_MSK,
             SERIAL_CONFIG_DATALEN_32_BITS);
}



__attribute__((noinline)) void set_multi_bits()
{
    SERIAL2->CONFIG |= SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_MODE;
    SERIAL2->CONFIG |= SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_MODE;
}



__attribute__((noinline)) void ins_multi_mskd()
{
    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_DATALEN_MSK     | SERIAL_CONFIG_RXPORT_MSK,
             SERIAL_CONFIG_DATALEN_16_BITS | (3 << SERIAL_CONFIG_RXPORT_POS));
    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_DATALEN_MSK     | SERIAL_CONFIG_RXPORT_MSK,
             SERIAL_CONFIG_DATALEN_16_BITS | (3 << SERIAL_CONFIG_RXPORT_POS));
}



__attribute__((noinline)) void equ_multi_bits()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY;
    SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_multi_mskd()
{
    SERIAL2->CONFIG =   SERIAL_CONFIG_PARITY_EVEN
                      | (6 << SERIAL_CONFIG_RXPORT_POS);
    SERIAL2->CONFIG =   SERIAL_CONFIG_PARITY_EVEN
                      | (6 << SERIAL_CONFIG_RXPORT_POS);
}



__attribute__((noinline)) void equ_bits_mskd()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS;
    SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS;
}



__attribute__((noinline)) void equ_mskd_bits()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_DATALEN_32_BITS | SERIAL_CONFIG_POLARITY;
    SERIAL2->CONFIG = SERIAL_CONFIG_DATALEN_32_BITS | SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void equ_bits_var()
{
    uint32_t    config = SERIAL_CONFIG_POLARITY;

    SERIAL2->CONFIG = config;

    config = SERIAL_CONFIG_MODE;

    SERIAL2->CONFIG = config;
}



__attribute__((noinline)) void equ_mskd_var()
{
    uint32_t    config = SERIAL_CONFIG_DATALEN_16_BITS;

    SERIAL2->CONFIG = config;

    config = 3 << SERIAL_CONFIG_RXPORT_POS;

    SERIAL2->CONFIG = config;
}



__attribute__((noinline)) void cmp_zero()
{
    SERIAL2->CONFIG = 0;
    SERIAL2->CONFIG = 0;

    if (SERIAL2->CONFIG == 0)
        TIMER1->PRESCALE = 43 << TIMER_PRESCALE_PRESCALER_POS;
    else
        TIMER1->PRESCALE = 17 << TIMER_PRESCALE_PRESCALER_POS;

    if (SERIAL2->CONFIG != 0)
        SERIAL2->CONFIG = SERIAL_CONFIG_DATALEN_32_BITS;
    else
        SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN         ;
}



__attribute__((noinline)) void cmp_bits()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_POLARITY;

    if (SERIAL2->CONFIG == SERIAL_CONFIG_POLARITY)
        TIMER1->PRESCALE = 11 << TIMER_PRESCALE_PRESCALER_POS;
    else
        TIMER1->PRESCALE = 67 << TIMER_PRESCALE_PRESCALER_POS;

    if (SERIAL2->CONFIG != SERIAL_CONFIG_POLARITY)
        SERIAL2->CONFIG  = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->CONFIG  = SERIAL_CONFIG_ENDIAN      ;
}



__attribute__((noinline)) void cmp_mskd()
{
    SERIAL2->CONFIG = 29 << SERIAL_CONFIG_TXPORT_POS;

    if (   (SERIAL2->CONFIG & SERIAL_CONFIG_TXPORT_MSK)
        == (17 << SERIAL_CONFIG_TXPORT_POS) )
        CHG_BITS(TIMER1->PRESCALE                   ,
                 TIMER_PRESCALE_PRESCALER_MSK       ,
                 113 << TIMER_PRESCALE_PRESCALER_POS);
    else
        CHG_BITS(TIMER1->PRESCALE                   ,
                 TIMER_PRESCALE_PRESCALER_MSK       ,
                 173 << TIMER_PRESCALE_PRESCALER_POS);

    if (   (SERIAL2->CONFIG & SERIAL_CONFIG_TXPORT_MSK)
        != (17 << SERIAL_CONFIG_TXPORT_POS) )
        CHG_BITS(SERIAL2->CONFIG              ,
                 SERIAL_CONFIG_DATALEN_MSK    ,
                 SERIAL_CONFIG_DATALEN_32_BITS);
    else
        SERIAL2->CONFIG |= SERIAL_CONFIG_POLARITY;
}



__attribute__((noinline)) void cmp_reg()
{
    uint32_t word   = SERIAL_CONFIG_ENDIAN | SERIAL_CONFIG_DATALEN_16_BITS;

    SERIAL2->CONFIG = word;

    if (SERIAL2->CONFIG  == word)
        TIMER1->PRESCALE  = 223 << TIMER_PRESCALE_PRESCALER_POS;
    else
        TIMER1->PRESCALE  = 241 << TIMER_PRESCALE_PRESCALER_POS;

    if (SERIAL2->CONFIG  != word)
        SERIAL2->CONFIG = SERIAL_CONFIG_DATALEN_16_BITS;
    else
        SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN         ;
}



__attribute__((noinline)) void bits_val(
const uint32_t  config)
{
    SERIAL2->CONFIG |= config;
    SERIAL2->CONFIG |= config;
}



__attribute__((noinline)) void call_bits_val()
{
    uint32_t    config = SERIAL_CONFIG_POLARITY;

    bits_val(config);
    bits_val(SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void constexpr_bits_array()
{
    GPIO1->BYTES[3] = 0x6    ;
    GPIO1->SET      = 1 << 13;
}



__attribute__((noinline)) void runtime_bits_array()
{
    volatile unsigned   index = 3;

    GPIO1->BYTES[index] = 0x21  ;

    index = 7;

    GPIO1->SET = (1 << index);
}




__attribute__((noinline)) void bits_ref(
const uint32_t* const   config)
{
    SERIAL2->CONFIG |= *config;
    SERIAL2->CONFIG |= *config;
}



__attribute__((noinline)) void call_bits_ref()
{
    uint32_t    config1 = SERIAL_CONFIG_MODE,
                config2 = SERIAL_CONFIG_MODE;

    bits_ref(&config1);
    bits_ref(&config2);
}





__attribute__((noinline)) void mskd_val(
const uint32_t  mask,
const uint32_t  bits)
{
    SERIAL2->CONFIG = (SERIAL2->CONFIG & ~mask) | bits;
    SERIAL2->CONFIG = (SERIAL2->CONFIG & ~mask) | bits;
}



__attribute__((noinline)) void call_mskd_val()
{
    uint32_t    mask = SERIAL_CONFIG_DATALEN_MSK    ,
                bits = SERIAL_CONFIG_DATALEN_16_BITS;

    mskd_val(mask                     , bits                         );
    mskd_val(SERIAL_CONFIG_DATALEN_MSK, SERIAL_CONFIG_DATALEN_16_BITS);
}



__attribute__((noinline)) void mskd_ref(
const uint32_t* const   mask_bits)
{
    CHG_BITS(SERIAL2->CONFIG, mask_bits[0], mask_bits[1]);
    CHG_BITS(SERIAL2->CONFIG, mask_bits[0], mask_bits[1]);
}



__attribute__((noinline)) void call_mskd_ref()
{
    uint32_t    mask_bits_a[2]  = { SERIAL_CONFIG_DATALEN_MSK   ,
                                   SERIAL_CONFIG_DATALEN_16_BITS},
                mask_bits_b[2]  = { SERIAL_CONFIG_DATALEN_MSK   ,
                                   SERIAL_CONFIG_DATALEN_32_BITS};

    mskd_ref(mask_bits_a);
    mskd_ref(mask_bits_b);

    SERIAL2->CONFIG &= ~SERIAL_CONFIG_POLARITY; // clear for periph_reg_bits_val
}



__attribute__((noinline)) void periph_reg_bits_val(
         serial_t*  serial,
volatile uint32_t*  config,
const    uint32_t   bits  )
{
    SERIAL2->CONFIG |= SERIAL_CONFIG_POLARITY;
    serial ->CONFIG |= SERIAL_CONFIG_POLARITY;
    serial ->CONFIG |= bits                  ;
    *config         |= bits                  ;
}



__attribute__((noinline)) void call_periph_reg_bits_val()
{
    periph_reg_bits_val(SERIAL2, &(SERIAL2->CONFIG), SERIAL_CONFIG_POLARITY);
}



__attribute__((noinline)) void periph_reg_bits_ref(
         serial_t*          serial,
volatile uint32_t*          config,
const    uint32_t* const    bits      )
{
    SERIAL2->CONFIG |= SERIAL_CONFIG_POLARITY;
    serial ->CONFIG |= SERIAL_CONFIG_POLARITY;
    serial ->CONFIG |= *bits                 ;
    *config         |= *bits                 ;
}



__attribute__((noinline)) void call_periph_reg_bits_ref()
{
    uint32_t    polarity = SERIAL_CONFIG_POLARITY;

    periph_reg_bits_ref(SERIAL2, &(SERIAL2->CONFIG), &polarity);
}



__attribute__((noinline)) void periph_reg_mskd_val(
         serial_t*  serial,
volatile uint32_t*  config,
const    uint32_t    mask  ,
const    uint32_t    bits  )
{

    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_DATALEN_MSK,
             SERIAL_CONFIG_DATALEN_16_BITS);

    CHG_BITS(serial ->CONFIG, SERIAL_CONFIG_DATALEN_MSK, bits);
    CHG_BITS(serial ->CONFIG, mask                     , bits);
    CHG_BITS(*config        , mask                     , bits);
}



__attribute__((noinline)) void call_periph_reg_mskd_val()
{
    periph_reg_mskd_val(SERIAL2,
                       &(SERIAL2->CONFIG),
                       SERIAL_CONFIG_DATALEN_MSK,
                       SERIAL_CONFIG_DATALEN_16_BITS);
}



__attribute__((noinline)) void periph_reg_mskd_ref(
         serial_t*          serial,
volatile uint32_t*          config,
const    uint32_t*  const   mask_bits)
{

    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_DATALEN_MSK,
             SERIAL_CONFIG_DATALEN_32_BITS);

    CHG_BITS(serial ->CONFIG, SERIAL_CONFIG_DATALEN_MSK, mask_bits[1]);
    CHG_BITS(serial ->CONFIG, mask_bits[0]             , mask_bits[1]);
    CHG_BITS(*config        , mask_bits[0]             , mask_bits[1]);
}



__attribute__((noinline)) void call_periph_reg_mskd_ref()
{
    uint32_t    mask_bits[2] = { SERIAL_CONFIG_DATALEN_MSK,
                                 SERIAL_CONFIG_DATALEN_32_BITS
                               };

    periph_reg_mskd_ref(SERIAL2, &(SERIAL2->CONFIG), mask_bits);
}



__attribute__((noinline)) uint32_t return_bits()
{
    return SERIAL_CONFIG_ENDIAN;
}



__attribute__((noinline)) void call_return_bits()
{
    uint32_t    config_bits = return_bits();

    if (config_bits == SERIAL_CONFIG_ENDIAN)
        TIMER1->PRESCALE  = 83 << TIMER_PRESCALE_PRESCALER_POS;
    else
        TIMER1->PRESCALE  = 89 << TIMER_PRESCALE_PRESCALER_POS;
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
        TIMER1->PRESCALE  = 157 << TIMER_PRESCALE_PRESCALER_POS;
    else
        TIMER1->PRESCALE  = 163 << TIMER_PRESCALE_PRESCALER_POS;
}



__attribute__((noinline)) volatile uint32_t* return_reg()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_POLARITY;

    return &SERIAL2->CONFIG;
}



__attribute__((noinline)) void call_return_reg()
{
    volatile uint32_t*  config = return_reg();

    if (*config == SERIAL_CONFIG_POLARITY)
        TIMER1->PRESCALE  = 53 << TIMER_PRESCALE_PRESCALER_POS;
    else
        TIMER1->PRESCALE  = 59 << TIMER_PRESCALE_PRESCALER_POS;
}



__attribute__((noinline)) serial_t* return_periph()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_POLARITY;

    return SERIAL2;
}



__attribute__((noinline)) void call_return_periph()
{
    serial_t*       serial = return_periph();

    if (serial->CONFIG == SERIAL_CONFIG_POLARITY)
        TIMER1->PRESCALE  = 199 << TIMER_PRESCALE_PRESCALER_POS;
    else
        TIMER1->PRESCALE  = 211 << TIMER_PRESCALE_PRESCALER_POS;
}



__attribute__((noinline)) void pos_val(
const uint8_t       pos)
{
    if (pos == SERIAL_CONFIG_ENDIAN_POS)
        GPIO1->BYTES[3] = 0x33;
    else if (pos == SERIAL_CONFIG_POLARITY_POS)
        GPIO1->BYTES[3] = 0x44;
    else
        GPIO1->BYTES[3] = 0x55;
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
        GPIO1->BYTES[3] = 0x66;
    else if (*pos == SERIAL_CONFIG_POLARITY_POS)
        GPIO1->BYTES[3] = 0x77;
    else
        GPIO1->BYTES[3] = 0x88;
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
    CHG_BITS(SERIAL2->CONFIG, mask, txport);
}



__attribute__((noinline)) void call_range_val(
unsigned    port)
{
    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_RXPORT_MSK,
             (port << SERIAL_CONFIG_RXPORT_POS) & SERIAL_CONFIG_TXPORT_MSK);

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
    CHG_BITS(SERIAL2->CONFIG, mask_txport[0], mask_txport[1]);
}



__attribute__((noinline)) void call_range_ref(
unsigned    port)
{

    uint32_t    msk_txport[2] = {           SERIAL_CONFIG_TXPORT_MSK ,
                                 (  port << SERIAL_CONFIG_TXPORT_POS)
                                  &         SERIAL_CONFIG_TXPORT_MSK };

    CHG_BITS(SERIAL2->CONFIG,
             SERIAL_CONFIG_RXPORT_MSK,
             (port << SERIAL_CONFIG_RXPORT_POS) & SERIAL_CONFIG_TXPORT_MSK);

    runtime_range_ref(msk_txport);
}



__attribute__((noinline)) void call_range_ref_port()
{
    call_range_ref(0xc);
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
                              SERIAL2->CONFIG  ,
                              TIMER1->PRESCALE ,
                              GPIO1  ->BYTES[3],
                              GPIO1  ->SET     );
}



__attribute__((noinline)) void check_array_range_pass(
const unsigned  port)
{
    if (port <= GPIO_MAX_PORT_NUM)
        GPIO1->BYTES[3] = 127;
    else
        GPIO1->BYTES[3] = 131;
}



__attribute__((noinline)) void check_array_range_fail(
const unsigned  port)
{
    if (port <= GPIO_MAX_PORT_NUM)
        GPIO1->BYTES[3] = 149;
    else
        GPIO1->BYTES[3] = 151;
}



__attribute__((noinline)) void check_bits_range_pass(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        GPIO1->BYTES[3] = 157;
    else
        GPIO1->BYTES[3] = 163;
}



__attribute__((noinline)) void check_bits_range_fail(
const unsigned  bit_num)
{
    if (bit_num <= sizeof(uint32_t) * 4 - 1)
        GPIO1->BYTES[3] = 167;
    else
        GPIO1->BYTES[3] = 173;
}



__attribute__((noinline)) void check_mskd_range_pass(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        GPIO1->BYTES[3] = 179;
    else
        GPIO1->BYTES[3] = 181;
}



__attribute__((noinline)) void check_mskd_range_fail(
unsigned port)
{
    if (port <= SERIAL_MAX_PORT_NUM)
        GPIO1->BYTES[3] = 191;
    else
        GPIO1->BYTES[3] = 193;
}



__attribute__((noinline)) void check_bits_extract()
{
    SERIAL2->CONFIG = SERIAL_CONFIG_POLARITY | SERIAL_CONFIG_ENDIAN;

    uint32_t    extracted = SERIAL_CONFIG_MODE;

    extracted = SERIAL2->CONFIG;

    if (extracted == (SERIAL_CONFIG_POLARITY | SERIAL_CONFIG_ENDIAN))
        GPIO1->BYTES[3] = 199;
    else
        GPIO1->BYTES[3] = 227;

    SERIAL2->CONFIG = SERIAL_CONFIG_MODE;
    extracted       = SERIAL2->CONFIG   ;

    if (extracted != SERIAL_CONFIG_MODE)
        SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN;
    else
        SERIAL2->CONFIG = SERIAL_CONFIG_DATALEN_32_BITS;
}



__attribute__((noinline)) void check_mskd_extract()
{
    SERIAL2->CONFIG = 23 << SERIAL_CONFIG_RXPORT_POS;

    uint32_t                            bits = 11 << SERIAL_CONFIG_RXPORT_POS,
             __attribute__((unused))    mask =       SERIAL_CONFIG_RXPORT_MSK;

    bits = SERIAL2->CONFIG & SERIAL_CONFIG_RXPORT_MSK;

    if (bits == (23 << SERIAL_CONFIG_RXPORT_POS))
        GPIO1->BYTES[3] = 229;
    else
        GPIO1->BYTES[3] = 233;

    SERIAL2->CONFIG = 7 << SERIAL_CONFIG_RXPORT_POS;

    bits = SERIAL2->CONFIG & SERIAL_CONFIG_RXPORT_MSK;

    if (bits != (7 << SERIAL_CONFIG_RXPORT_POS))
        SERIAL2->CONFIG = SERIAL_CONFIG_PARITY_CRC;
    else
        SERIAL2->CONFIG = SERIAL_CONFIG_ENDIAN;
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
