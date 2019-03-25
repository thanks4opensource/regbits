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



__attribute__((noinline)) void zero()
{
    serial2->config           = 0;
    timer1 ->prescale         = 0;
    gpio1  ->bytes.BYTES<3>() = 0;
    gpio1  ->set              = 0;
}




__attribute__((noinline)) void set_singl_bits()
{
    serial2->config |=  Serial::Config::POLARITY ;
    serial2->config.set(Serial::Config::POLARITY);
}



__attribute__((noinline)) void clr_singl_bits()
{
    serial2->config -=  Serial::Config::POLARITY ;
    serial2->config.clr(Serial::Config::POLARITY);
}



__attribute__((noinline)) void set_singl_mskd()
{
    serial2->config |=  Serial::Config::DATALEN_16_BITS ;
    serial2->config.set(Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void clr_singl_mskd()
{
    serial2->config -=  Serial::Config::DATALEN_16_BITS ;
    serial2->config.clr(Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void equ_singl_bits()
{
    serial2->config =   Serial::Config::POLARITY ;
    serial2->config.wrt(Serial::Config::POLARITY);
}



__attribute__((noinline)) void equ_singl_mskd()
{
    serial2->config =   Serial::Config::DATALEN_16_BITS ;
    serial2->config.wrt(Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void flp_singl_bits()
{
    serial2->config ^=  Serial::Config::POLARITY ;
    serial2->config.flp(Serial::Config::POLARITY);
    serial2->config ^=  Serial::Config::POLARITY ;
}



__attribute__((noinline)) void flp_singl_mskd()
{
    serial2->config ^=  Serial::Config::DATALEN_16_BITS ;
    serial2->config.flp(Serial::Config::DATALEN_16_BITS);
    serial2->config ^=  Serial::Config::DATALEN_16_BITS ;
}



__attribute__((noinline)) void ins_singl_mskd()
{
    serial2->config <<= Serial::Config::DATALEN_32_BITS ;
    serial2->config.ins(Serial::Config::DATALEN_32_BITS);
}



__attribute__((noinline)) void set_multi_bits()
{
    serial2->config |= Serial::Config::ENDIAN | Serial::Config::MODE;
    serial2->config |= Serial::Config::ENDIAN | Serial::Config::MODE;
}



__attribute__((noinline)) void ins_multi_mskd()
{
    serial2->config <<=   Serial::Config::DATALEN_16_BITS
                        | Serial::Config::RXPORT<3>()     ;
    serial2->config.ins(  Serial::Config::DATALEN_16_BITS
                        | Serial::Config::RXPORT<3>()    );

}



__attribute__((noinline)) void equ_multi_bits()
{
    serial2->config =   Serial::Config::ENDIAN | Serial::Config::POLARITY ;
    serial2->config.wrt(Serial::Config::ENDIAN | Serial::Config::POLARITY);
}



__attribute__((noinline)) void equ_multi_mskd()
{
    serial2->config =     Serial::Config::PARITY_EVEN
                      |   Serial::Config::RXPORT<6>()     ;
    serial2->config.wrt(  Serial::Config::PARITY_EVEN
                        | Serial::Config::RXPORT<6>()    );
}



__attribute__((noinline)) void equ_bits_mskd()
{
    serial2->config =     Serial::Config::ENDIAN
                        | Serial::Config::DATALEN_16_BITS ;
    serial2->config.wrt(  Serial::Config::ENDIAN
                        | Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void equ_mskd_bits()
{
    serial2->config =     Serial::Config::DATALEN_32_BITS
                        | Serial::Config::POLARITY        ;
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



__attribute__((noinline)) void cmp_zero()
{
    serial2->config =    0;
    serial2->config.zero();

    if (serial2->config == 0)
        timer1->prescale = Timer::Prescale::PRESCALER<43>();
    else
        timer1->prescale = Timer::Prescale::PRESCALER<17>();

    if (serial2->config != 0)
        serial2->config = Serial::Config::DATALEN_32_BITS;
    else
        serial2->config = Serial::Config::ENDIAN           ;
}


__attribute__((noinline)) void cmp_bits()
{
    serial2->config = Serial::Config::POLARITY ;

    if (serial2->config == Serial::Config::POLARITY)
        timer1->prescale = Timer::Prescale::PRESCALER<11>();
    else
        timer1->prescale = Timer::Prescale::PRESCALER<67>();

    if (serial2->config != Serial::Config::POLARITY)
        serial2->config  = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config  = Serial::Config::ENDIAN         ;
}



__attribute__((noinline)) void cmp_mskd()
{
    serial2->config = Serial::Config::TXPORT<29>();

    if (serial2->config   == Serial::Config::TXPORT<17>())
        timer1->prescale <<= Timer::Prescale::PRESCALER<113>();
    else
        timer1->prescale <<= Timer::Prescale::PRESCALER<173>();

    if (serial2->config  != Serial::Config::TXPORT<17>())
        serial2->config <<= Serial::Config::DATALEN_32_BITS;
    else
        serial2->config |= Serial::Config::POLARITY        ;
}



__attribute__((noinline)) void cmp_reg()
{
    uint32_t word = (  Serial::Config::ENDIAN
                     | Serial::Config::DATALEN_16_BITS).bits();

    serial2->config = word;

    if (serial2->config  == word)
        timer1->prescale  = Timer::Prescale::PRESCALER<223>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER<241>();

    if (serial2->config  != word)
        serial2->config = Serial::Config::DATALEN_16_BITS;
    else
        serial2->config = Serial::Config::ENDIAN         ;
}



__attribute__((noinline)) void bits_val(
const Serial::Config::bits_t        config)
{
    serial2->config |=  config;
    serial2->config.set(config);
}



__attribute__((noinline)) void call_bits_val()
{
    Serial::Config::bits_t  config = Serial::Config::POLARITY;

    bits_val(config);
    bits_val(+Serial::Config::POLARITY);
}



__attribute__((noinline)) void constexpr_bits_array()
{
    gpio1->bytes.BYTES<3>() = 0x6;
    gpio1->set              = Gpio::Set::SET<13>();
}



__attribute__((noinline)) void runtime_bits_array()
{
    volatile unsigned   index = 3;

    gpio1->bytes.bytes(index) = 0x21;

    index = 7;

    gpio1->set = Gpio::Set::set(index);
}



__attribute__((noinline)) void bits_ref(
const Serial::Config::bits_t        &config)
{
    serial2->config |=  config;
    serial2->config.set(config);
}



__attribute__((noinline)) void call_bits_ref()
{
    Serial::Config::bits_t  config = Serial::Config::MODE;

    bits_ref(config);
    bits_ref(+Serial::Config::MODE);
}



__attribute__((noinline)) void mskd_val(
const Serial::Config::mskd_t    config)
{
    serial2->config <<= config;
    serial2->config.ins(config);
}



__attribute__((noinline)) void call_mskd_val()
{
    Serial::Config::mskd_t  config = Serial::Config::DATALEN_16_BITS;

    mskd_val(         config                 );
    mskd_val(+Serial::Config::DATALEN_16_BITS);
}





__attribute__((noinline)) void mskd_ref(
const Serial::Config::mskd_t        &config)
{
    serial2->config <<= config;
    serial2->config.ins(config);
}



__attribute__((noinline)) void call_mskd_ref()
{
    Serial::Config::mskd_t  config = Serial::Config::DATALEN_16_BITS;

    mskd_ref(config);
    mskd_ref(+Serial::Config::DATALEN_32_BITS);

    serial2->config -= Serial::Config::POLARITY; // clear for periph_reg_bits_val
}



__attribute__((noinline)) void periph_reg_bits_val(
      Serial                    *serial  ,
Reg<uint32_t, Serial::Config>   &config  ,
const Serial::Config::bits_t     polarity)
{
    serial2->config |= Serial::Config::POLARITY;
    serial ->config |= Serial::Config::POLARITY;
    serial ->config |=                 polarity;
             config |=                 polarity;
}



__attribute__((noinline)) void call_periph_reg_bits_val()
{
    periph_reg_bits_val(serial2, serial2->config, +Serial::Config::POLARITY);
}



__attribute__((noinline)) void periph_reg_bits_ref(
      Serial                    *serial  ,
Reg<uint32_t, Serial::Config>   &config  ,
const Serial::Config::bits_t    &polarity)
{
    serial2->config |= Serial::Config::POLARITY;
    serial ->config |= Serial::Config::POLARITY;
    serial ->config |=                 polarity;
             config |=                 polarity;
}



__attribute__((noinline)) void call_periph_reg_bits_ref()
{
    periph_reg_bits_ref(serial2, serial2->config, +Serial::Config::POLARITY);
}



__attribute__((noinline)) void periph_reg_mskd_val(
      Serial                    *serial  ,
Reg<uint32_t, Serial::Config>   &config  ,
const Serial::Config::mskd_t         datalen)
{
    serial2->config <<= Serial::Config::DATALEN_16_BITS;
    serial ->config <<= Serial::Config::DATALEN_16_BITS;
    serial ->config <<=                 datalen;
             config <<=                 datalen;
}



__attribute__((noinline)) void call_periph_reg_mskd_val()
{
    periph_reg_mskd_val(serial2,
                       serial2->config,
                       +Serial::Config::DATALEN_16_BITS);
}



__attribute__((noinline)) void periph_reg_mskd_ref(
      Serial                    *serial  ,
Reg<uint32_t, Serial::Config>   &config  ,
const Serial::Config::mskd_t    &datalen)
{
    serial2->config <<= Serial::Config::DATALEN_32_BITS;
    serial ->config <<= Serial::Config::DATALEN_32_BITS;
    serial ->config <<=                 datalen;
             config <<=                 datalen;
}



__attribute__((noinline)) void call_periph_reg_mskd_ref()
{
    periph_reg_mskd_ref(serial2,
                       serial2->config,
                       +Serial::Config::DATALEN_32_BITS);
}



__attribute__((noinline)) Serial::Config::bits_t return_bits()
{
    return Serial::Config::ENDIAN;
}



__attribute__((noinline)) void call_return_bits()
{
    Serial::Config::bits_t  config_bits = return_bits();

    if (config_bits == Serial::Config::ENDIAN)
        timer1->prescale  = Timer::Prescale::PRESCALER<83>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER<89>();
}



__attribute__((noinline)) Serial::Config::mskd_t return_mskd()
{
    return +Serial::Config::PARITY_EVEN;
}



__attribute__((noinline)) void call_return_mskd()
{
    Serial::Config::mskd_t  config_mskd = return_mskd();

    if (config_mskd == Serial::Config::PARITY_EVEN)
        timer1->prescale  = Timer::Prescale::PRESCALER<157>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER<163>();
}



__attribute__((noinline)) Serial::config_t& return_reg()
{
    serial2->config = Serial::Config::POLARITY;

    return serial2->config;
}



__attribute__((noinline)) void call_return_reg()
{
    Serial::config_t        config = return_reg();

    if (config == Serial::Config::POLARITY)
        timer1->prescale  = Timer::Prescale::PRESCALER<53>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER<59>();
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
        timer1->prescale  = Timer::Prescale::PRESCALER<199>();
    else
        timer1->prescale  = Timer::Prescale::PRESCALER<211>();
}



__attribute__((noinline)) void pos_val(
const Serial::Config::pos_t     pos)
{
    if (pos == Serial::Config::ENDIAN_POS)
        gpio1->bytes.BYTES<3>() = 0x33;
    else if (pos == Serial::Config::POLARITY_POS)
        gpio1->bytes.BYTES<3>() = 0x44;
    else
        gpio1->bytes.BYTES<3>() = 0x55;
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
        gpio1->bytes.BYTES<3>() = 0x66;
    else if (pos == Serial::Config::POLARITY_POS)
        gpio1->bytes.BYTES<3>() = 0x77;
    else
        gpio1->bytes.BYTES<3>() = 0x88;
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
    serial2->config <<= txport;
}



__attribute__((noinline)) void call_range_val(
unsigned    port)
{
    serial2->config <<= Serial::Config::rxport(port) ;
    runtime_range_val(  Serial::Config::txport(port));
}



__attribute__((noinline)) void call_range_val_port()
{
    call_range_val(31);
}



__attribute__((noinline)) void runtime_range_ref(
const Serial::Config::mskd_t    txport)
{
    serial2->config <<= txport;
}



__attribute__((noinline)) void call_range_ref(
unsigned    port)
{
    serial2->config <<= Serial::Config::rxport(port) ;
    runtime_range_ref(  Serial::Config::txport(port));
}



__attribute__((noinline)) void call_range_ref_port()
{
    call_range_ref(0xc);
}



__attribute__((noinline)) void check_array_range_pass(
const unsigned  port)
{
    if (Gpio::Bytes::valid(port))
        gpio1->bytes.BYTES<3>() = 127;
    else
        gpio1->bytes.BYTES<3>() = 131;
}



__attribute__((noinline)) void check_array_range_fail(
const unsigned  port)
{
    if (Gpio::Bytes::valid(port))
        gpio1->bytes.BYTES<3>() = 149;
    else
        gpio1->bytes.BYTES<3>() = 151;
}



__attribute__((noinline)) void check_bits_range_pass(
const unsigned  bit_num)
{
    if (Gpio::Set::valid(bit_num))
        gpio1->bytes.BYTES<3>() = 157;
    else
        gpio1->bytes.BYTES<3>() = 163;
}



__attribute__((noinline)) void check_bits_range_fail(
const unsigned  bit_num)
{
    if (Gpio::Set::valid(bit_num))
        gpio1->bytes.BYTES<3>() = 167;
    else
        gpio1->bytes.BYTES<3>() = 173;
}



__attribute__((noinline)) void check_mskd_range_pass(
unsigned port)
{
    if (Serial::Config::valid_rxport(port))  // check valid_txport() below
        gpio1->bytes.BYTES<3>() = 179;
    else
        gpio1->bytes.BYTES<3>() = 181;
}



__attribute__((noinline)) void check_mskd_range_fail(
unsigned port)
{
    if (Serial::Config::valid_txport(port))  // check valid_rxport() aove
        gpio1->bytes.BYTES<3>() = 191;
    else
        gpio1->bytes.BYTES<3>() = 193;
}



__attribute__((noinline)) void check_bits_extract()
{
    serial2->config = Serial::Config::POLARITY | Serial::Config::ENDIAN;

    Serial::Config::bits_t  extracted = Serial::Config::MODE;

    serial2->config.get(extracted);

    if (extracted == (Serial::Config::POLARITY | Serial::Config::ENDIAN))
        gpio1->bytes.BYTES<3>() = 199;
    else
        gpio1->bytes.BYTES<3>() = 227;

    serial2->config   = Serial::Config::MODE;
    serial2->config >>= extracted           ;

    if (extracted != Serial::Config::MODE)
        serial2->config = Serial::Config::ENDIAN;
    else
        serial2->config = Serial::Config::DATALEN_32_BITS;
}



__attribute__((noinline)) void check_mskd_extract()
{
    serial2->config = Serial::Config::RXPORT<23>();

    Serial::Config::mskd_t  extracted = Serial::Config::RXPORT<11>();

    serial2->config.get(extracted);

    if (extracted == Serial::Config::RXPORT<23>())
        gpio1->bytes.BYTES<3>() = 229;
    else
        gpio1->bytes.BYTES<3>() = 233;

    serial2->config   = Serial::Config::RXPORT<7>();
    serial2->config >>= extracted;

    if (extracted != Serial::Config::RXPORT<7>())
        serial2->config = Serial::Config::PARITY_CRC;
    else
        serial2->config = Serial::Config::ENDIAN;
}






extern "C" void unittest_record_registers(unsigned,
                                          uint32_t,
                                          uint32_t,
                                          uint8_t ,
                                          uint32_t);

__attribute__((noinline)) void record_registers(
unsigned    test_num)
{
    unittest_record_registers(test_num,
                              serial2->config  .word    (),
                              timer1 ->prescale.word    (),
                              gpio1  ->bytes   .BYTES<3>(),
                              gpio1  ->set     .word    ());
}



extern "C" __attribute__((noinline)) void run()
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
