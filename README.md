regbits: C++ templates for type-safe bit manipulation
====================================================

**regbits** is a C++ template library for type-safe manipulation of bits in microcontroller peripheral registers. Compiled executable object code equals or outperforms traditional techniques in terms of size and speed, and complexity of header files describing peripheral/register layout is comparable.



Contents  <a name="contents"></a>
--------
* [License](#license)
* [What does regbits do?](#what_does_regbits_do)
* [What is regbits for?](#what_is_regbits_for)
* [How is regbits used?](#how_is_regbits_used)
* [How is regbits implemented?](#how_is_regbits_implemented?)
* [Comparison with other approaches](#comparison_with_other_approaches)
    * [Raw numeric values](#raw_numeric_values)
    * [Preprocessor symbolic peripheral addresses and register offsets](#preprocessor_symbolic_peripheral_addresses_and_register_offsets)
    * [Preprocessor symbolic bit definitions](#preprocessor_symbolic_bit_definitions)
    * [Static consts](#static_consts)
    * [C/C++ enums](#c_cxx_enums)
    * [C structs](#c_structs)
    * [C bitfields](#c_bitfields)
    * [Helper functions](#helper_functions)
    * [Higher-level wrappers](#Higher-level_wrappers)
* [Requirements, limitations, problems](#requirements_limitations_problems)
* [Unit test](#unit_test)
    * [Type-safe error detection](#type_safe_error_detection)
    * [Computational correctness](#computational_correctness)
    * [Performance claims](#performance_claims)
* [Future enhancements](#future_enhancements)


License  <a name="license"></a>
-------

regbits: C++ templates for type-safe bit manipulation

Copyright (C) 2019 Mark R. Rubin

This file is part of regbits.

The regbits program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

The regbits program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the [GNU General Public License](LICENSE.txt) along with the regbits program.  If not, see <https://www.gnu.org/licenses/gpl.html>


What does regbits do? <a name="what_does_regbits_do"></a>
-------------------------

Regbits enables easy to use, optimally efficient low-level access to [microcontroller registers](#microcontroller_registers).

Given appropriate header files, the following all compile to executable object code of equivalent size and speed (see [Performance claims](#performance_claims), below):

        // raw address and bits
        *(int*)(0x40008008) = 0xc0;

        // symbolic names for peripheral, register, and bits
        *(TIMER1 + TIMER_CTRL_OFFSET) = TIMER_ENABLE | TIMER_COUNT_UP;

        // C struct peripheral definition with symbolic bit names
        TIMER1->CTRL = TIMER_ENABLE | TIMER_COUNT_UP;

        // C++ regbits
        timer1->ctrl = TIMER_ENABLE | TIMER_COUNT_UP;

Things get more interesting when manipulating contiguous spans of several bits:

        // raw address and bits
        *(int*)(0x400c0004) = (*(int*)(0x400c0004) & ~0xf00) | 0x600;

        // symbolic names for peripheral, register, and bits
        *(TIMER3 + TIMER_CONFIG_OFFSET) = (*(TIMER3 + TIMER_CONFIG_OFFSET) & TIMER_CLOCK_DIV_MASK) | TIMER_CLOCK_DIV_8;

        // C struct peripheral definition with symbolic bit names and bit manipulation preprocessor macro
        INSERT_BITS(USART2->CONFIG, USART_BAUD_MASK, USART_BAUD_19200);

        // C++ regbits
        usart2->config /= USART_BAUD_19200;  // or usart2->config.ins(USART_BAUD_19200)

But more important than what regbits does is what it does NOT do. All of the following will compile without error but almost certainly cause serious, hard to debug problems when executed:

        // read the manual if you want to know what this is trying to do
        *(int*)(0x40100010) = 0x802;

        // they probably use the same bit positions for all peripherals
        *(SPI0 + SPI_CONFIG_OFFSET) = I2C_ENABLE | I2C_MASTER_MODE;

        // this might do something interesting
        ADC1->CTRL = USART_PARITY_EVEN | TIMER_ENABLE_INTERRUPT;
        
        // we'll catch any problems during debug and test
        init_usb_periph(USART3);

        // hope this works when used later on
        uint32_t timer_config_settings = SPI_LSB_FIRST | I2C_NACK_ENABLE;

Compared to regbits which won't allow any of the following to compile: <a name="regbits_compile_time_errors"></a>

        // ERROR: can't set SPI peripheral with I2C configuration constants
        spi0->ctrl = I2C_ENABLE;

        // ERROR: can't set register with another register's constant
        i2c1->interrupts = I2C_MODE_FAST;

        // ERROR: can't call function with wrong kind of peripheral
        init_usb(USART3);
        
        // ERROR: can't mix different peripherals' constants
        uint32_t timer_config_settings = (TIMER_COUNT_DOWN | USART_BAUD_9600).bits();

These are contrived, exaggerated examples. However, the point remains that this kind of error is easy to make, hard to detect by source code inspection, and possibly even harder to find during runtime testing and debugging. A one-letter typo can easily hide in thousands of lines of code:

        I2C3->CTRL = I2C_TIMEOUT_ON | I2S_ENABLE | I2C_MASTER_MODE;



What is regbits for? <a name="what_is_regbits_for"></a>
--------------------

Microcontrollers (MCUs / "Systems On A Chip" / SOCs) typically include *peripherals*: Hardware functionality such as input/output ports, timers, serial communications, analog-to-digital and digital-to-analog conversion, etc.

<a name="microcontroller_registers"></a>
These peripherals typically contain multiple *registers*: Sets of memory locations (usually contiguous) which when written to and read from control the peripheral and access its data. Additionally, the MCU itself -- clock speed, interrupts, I/O configuration -- is configured via similar sets of registers.

Single and sets of multiple (usually contiguous) bits within each register typically control or access specific capabilities of the peripheral or MCU. A register for a serial communications peripheral might be structured:

          31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
        |   |   |   |   |   |   |   | P |   |   |       PORT        |   | TR| RR|  CLK  |   |   | TI| RI|   |   |   |   SPEED   | M | E |

        bit(s)  label   functionality   
          0       E     Enable peripheral
          1       M     Mode (0==transmit, 1==receive)
         2-4    SPEED   Speed (0==slowest, 7==fastest)
          8      RI     Enable receive interrupt
          9      TI     Enable transmit interrupt
        12-13    CLK    Clock source (0==peripherals, 1==main, 2==external)
         14      RR     Receive data available
         15      TR     Transmit ready
        17-21   PORT    I/O port
         24      P      Polarity (0=positive, 1=negative)

Although the examples in this `README.md` and the [`unittest`](unittest) code are for 32-bit architectures, all are equally applicable to 64-bit and other word widths. And although designed for register access, regbits and similar methods are not limited to such usage.


#### Hardware/software limitations

All or almost all contemporary MCU hardware permits accessing memory by words (32/64/etc bits), bytes (8 bits), shorts (typically 16 bits) and other fixed, multiples-of-8, bit widths (32 bits on 64-bit architecture, etc).

Software frequently needs to access register bits (single or multiple) as separate, isolated atomic units, changing only those bits without affecting others in the same register.  Hardware does not support this, and with the exception of C bitfields ([see below](#c_bitfields)), neither do the C and C++ languages. Regbits and other software techniques (see [below](#comparison_with_other_approaches)) address these limitations.


#### Register memory accesses <a name="register_memory_access"></a>

Although registers are accessed as memory locations, they may or may not behave as such. C and C++ declarations should always include the `volatile` keyword because register bits may change independent of the CPU activity and the C/C++ execution model. There can be further differences; see [Future enhancements](#future_enhancements), below.



How is regbits used? <a name="how_is_regbits_used"></a>
--------------------

Given a microcontroller definition file based on the regbits C++ class templates (see [below](#how_is_regbits_implemented?)), the set of operators and functions defined in [`regbits.hxx`](regbits.hxx) can be used in client code.

The examples below are based on the sample definition file included in this repository's unit test directory, [`mcu_regbits.hxx`](unittest/mcu_regbits.hxx) (see [Unit test](#unit_test), below). This file contains a small set of example peripheral and register definitions describing a fictitious MCU and some of its peripherals.

The examples show correct regbits usage. The type-safe design of regbits will intentionally produce compile failures in case of mismatches between regbits objects, as per [above](#regbits_compile_time_errors). Also see ["Type-safe error detection"](#type_safe_error_detection) in the unittest documentation, below.


Many of the examples (and the [unit test suite](unittest)) show regbits' operator and function/method syntaxes, both of which produce the same results and can be used interchangeably.

#### Word, single bit, and multiple bit span assignment

        // assign single bit to register
        serial2->config =   Serial::Config::POLARITY ;
        serial2->config.wrt(Serial::Config::POLARITY);

        // assign multiple single bits to register
        serial2->config =   Serial::Config::ENDIAN | Serial::Config::POLARITY ;
        serial2->config.wrt(Serial::Config::ENDIAN | Serial::Config::POLARITY);

        // assign contiguous span of bits to register
        serial2->config =   Serial::Config::DATALEN_16_BITS ;  // datalen 8, 16, or 32 encoded in 2 bits
        serial2->config.wrt(Serial::Config::DATALEN_16_BITS);

        // assign multiple contiguous span of bits to register
        serial2->config =   Serial::Config::DATALEN_16_BITS | Serial::Config::PARITY_EVEN ;  // parity EVEN, ODD, CRC encoded in 2 bits
        serial2->config.wrt(Serial::Config::DATALEN_16_BITS | Serial::Config::PARITY_EVEN);

        // assign mix of single and contiguous span of bits
        serial2->config =   Serial::Config::DATALEN_16_BITS | Serial::Config::MODE ;  // mode is single bit
        serial2->config.wrt(Serial::Config::DATALEN_16_BITS | Serial::Config::MODE);

        // single bit and bit span order unimportant
        serial2->config = Serial::Config::MODE | Serial::Config::DATALEN_16_BITS ;


#### Set, clear, flip bits

        // set single/multiple bits/spans and mixtures thereof
        serial2->config |=  Serial::Config::POLARITY;
        serial2->config.set(Serial::Config::POLARITY        | Serial::Config::ENDIAN     );
        serial2->config |=  Serial::Config::DATALEN_16_BITS | Serial::Config::PARITY_EVEN ;
        serial2->config.set(Serial::Config::POLARITY        | Serial::Config::ENDIAN     );


        // clr single/multiple bits/spans and mixtures thereof
        serial2->config -=  Serial::Config::POLARITY;
        serial2->config.clr(Serial::Config::POLARITY        | Serial::Config::ENDIAN     );
        serial2->config -=  Serial::Config::DATALEN_16_BITS | Serial::Config::PARITY_EVEN ;
        serial2->config.clr(Serial::Config::POLARITY        | Serial::Config::ENDIAN     );


        // flip single/multiple bits/spans and mixtures thereof
        serial2->config ^=  Serial::Config::POLARITY;
        serial2->config.flp(Serial::Config::POLARITY        | Serial::Config::ENDIAN     );
        serial2->config ^=  Serial::Config::DATALEN_16_BITS | Serial::Config::PARITY_EVEN ;
        serial2->config.flp(Serial::Config::POLARITY        | Serial::Config::ENDIAN     );
        
#### Insert bits (set without changing others)

(see [Insert operator syntax](#insert_operator_syntax), below)

        // insert multiple single bits into register
        serial2->config /=  Serial::Config::ENDIAN | Serial::Config::POLARITY ;
        serial2->config.ins(Serial::Config::ENDIAN | Serial::Config::POLARITY);

        // insert contiguous span of bits to register
        serial2->config /=  Serial::Config::DATALEN_16_BITS ;
        serial2->config.ins(Serial::Config::DATALEN_16_BITS);

        // insert multiple contiguous span of bits into register
        serial2->config /=  Serial::Config::DATALEN_16_BITS | Serial::Config::PARITY_EVEN ;
        serial2->config.ins(Serial::Config::DATALEN_16_BITS | Serial::Config::PARITY_EVEN);

        // insert mix of single and contiguous span of bits
        serial2->config /=  Serial::Config::DATALEN_16_BITS | Serial::Config::MODE ;
        serial2->config.ins(Serial::Config::DATALEN_16_BITS | Serial::Config::MODE);

        // single bit and bit span order unimportant (reversed from above)
        serial2->config /=  Serial::Config::MODE | Serial::Config::DATALEN_16_BITS ;
        serial2->config.ins(Serial::Config::MODE | Serial::Config::DATALEN_16_BITS);


#### Test register bits

        // Test zero or arbitrary value
        if (serial2->config        == 0         ) // ...
        if (serial2->config        == 0x12345678) // ...

        // Test if bits are set in register
        if (serial2->config == Serial::Config::ENDIAN) // ...
        if (serial2->config != Serial::Config::ENDIAN |  | Serial::Config::POLARITY)  // ...

        // Test span of bits (ignoring others in register)
        if (serial2->config == Serial::Config::DATALEN_16_BITS) // ...
        if (serial2->config != Serial::Config::DATALEN_16_BITS | Serial::Config::POLARITY) // ...

        // Test all bits in register (exactly equal, no other bits set)
        if (serial2->config ==   Serial::Config::ENDIAN.bits()) // ...
        if (serial2->config != ((Serial::Config::ENDIAN.bits() | Serial::Config::DATALEN_16_BITS).bits()) // ...


#### Extract single and multiple bit spans from a register

        // extract all bits from register
        Serial::Config::bits_t  config_bits = serial2->config;
        // test all bits exactly equal to single bits or combinations of  single bits
        if (config_bits ==  Serial::Config::ENDIAN) // ...
        if (config_bits == (Serial::Config::ENDIAN | Serial::Config::POLARITY)) // ...

        // extract all bits from register
        Serial::Config::mskd_t  config_mskd = Serial::Config::DATALEN_16_BITS;  // or any other DATALEN_XX_BITS constant, only internal .mask() value used
                                config_mskd = serial2->config                ;
        // test bits with span (or multiple spans and/or single bits)
        if (config_mskd ==  Serial::Config::DATALEN_32_BITS) // ...
        // order important, otherwise loses .mask()
        if (config_mskd == (Serial::Config::DATALEN_32_BITS | Serial::Config::ENDIAN)) // ...
        // works, but only considers bits that are set in ENDIAN|DATALEN_32_BITS
        if (config_mskd == (Serial::Config::ENDIAN | Serial::Config::DATALEN_32_BITS)) // ...


#### Atomic (single) read of hardware register

See discussion [below](#future_enhancements) about self-modifying registers.

        // hardware register might change between accesses
        if (   serial2->config == Serial::Config::ENDIAN
            || serial2->config >= Serial::Config::DATALEN_16_BITS) // ...

        // single atomic read
        Copy<uint32_t, Serial::Config>  config(serial2->config);
        if (   config == Serial::Config::ENDIAN
            || config >= Serial::Config::DATALEN_16_BITS) // ...

#### Working with multiple bit spans containing arbitrary values <a name="mskd_arbitrary_values"></a>

(see rationale for syntax [below](#ugly_indexing_syntax))

        timer1->prescale = Timer::Prescale::PRESCALER_HIGH<17>();
        if (timer1->prescale != Timer::Prescale::PRESCALER_HIGH<17>()) // ...

#### Shifted values <a name="shifted_values"></a>

Regbits canonically works with multiple bit spans in their hardware-defined position within the register, avoiding unnecessary shift operations. (See [C bitfields](#c_bitfields), below.) Cases exist, however, where shifting is required:

          31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
        |   |   |   |   |   |   |   |   |   |   |             DATA              |   |   |   |   |   |   |   |   |   |  |   |   |STATUS |
                
        Copy<uint32_t, Usart::Rxdata> copy(usart3->rxdata);
        if (copy == Usart::Rxdata::STATUS_DATA_RCVD)
            return copy.shifted(Usart::Rxdata::DATA_SHIFTED);  // 0..255




How is regbits implemented? <a name="how_is_regbits_implemented?"></a>
---------------------------

The C++ class templates defining regbits are contained in the file [`regbits.hxx`](regbits.hxx). This file is intended for inclusion in an MCU peripheral/register/bits definition file such as the [`mcu_regbits.hxx`](unittest/mcu_regbits.hxx) example in the [`unittest`](unittest) subdirectory (see [Unit test](#unit_test), below).

Following are some commented excerpts from `mcu_regbits.hxx` illustrating use of the templates:

Include the regbits.hxx templates:

        #include <regbits.hxx>

Typically MCU regbits definition should go in their own namespace -- a manufacturer or chip name such as `stm32f767xx` or `lpc824` would replace the example's generic "mcu" namespace name:

        namespace mcu {

Start definition of a peripheral:

        struct Serial {

Start definition of a register in the peripheral.:

            struct Config {

MCU regbits definitions implement type-safety by instantiating several classes templated on each specific register. Other instantiated template classes' methods will only accept objects template-instantiated on the same register.

`pos_t` is a type-safe wrapper for unsigned integers. It ensures that the values can only be used with the classes/register they are intended for

                using  pos_t = Pos<uint32_t, Config>;

Define bit positions of individual bits and spans of bits within the register ...

Note that these, and all other definitions, are `static constexpr`. Combined with the regbits `constexpr` constructors in the `regbits.hxx` class templates (and when compiled with appropriate optimization flags) they become compile-time only constants -- no runtime storage is allocated for them.

Note also that these values are externally visible in case client code has use for them.

Bit positions:

                static constexpr pos_t  MODE_POS     = pos_t( 0),
                                        DATALEN_POS  = pos_t( 1),
                                        PARITY_POS   = pos_t( 3),
                                        ENDIAN_POS   = pos_t( 5),
                                        POLARITY_POS = pos_t( 6),
                                        RXPORT_POS   = pos_t( 7),
                                        TXPORT_POS   = pos_t(12);

Define bitmasks describing the size of multi-bit spans:

                static const uint32_t   DATALEN_MASK = 0x03,
                                        PARITY_MASK  = 0x03,
                                        RXPORT_MASK  = 0x1f,
                                        TXPORT_MASK  = 0x1f;

Instantiation of the regbits templated classes. `Bits` is used for single bits (although when object instances are combined with others via the "`|`" operator they  can contain multiple single bits). `Mskd` is used for spans of multiple bits. `Shft` is used to normalize (right shift to LSB) masked values.

                using bits_t = Bits<uint32_t, Config>;
                using mskd_t = Mskd<uint32_t, Config>;
                using shft_t = Shft<uint32_t, Config>;

The fact that Mskd objects hold both a bitmask and an bit value allows it to be used as a standalone object that supports bit span insertion into a register. Expressions using regbits insertion operators/methods  objects such as:

        serial2->config /= Serial::Config::DATALEN_16_BITS

compile to executable object code identical that generated when not using regbits:

        serial2_register = (serial2_register & ~datalen_mask) | datalen_bits;

<a name="regbits_bits_t_and_mskd_t"></a>
Continuing with the example definition file, define constants for single bits:

        static constexpr bits_t MODE     = bits_t(1, MODE_POS    ),
                                ENDIAN   = bits_t(1, ENDIAN_POS  ),
                                POLARITY = bits_t(1, POLARITY_POS);

Defining constants for multiple bit spans:

        static constexpr mskd_t
                DATALEN_8_BITS  = mskd_t(DATALEN_MASK, 0, DATALEN_POS),
                DATALEN_16_BITS = mskd_t(DATALEN_MASK, 1, DATALEN_POS),
                DATALEN_32_BITS = mskd_t(DATALEN_MASK, 2, DATALEN_POS),
                PARITY_ODD      = mskd_t(PARITY_MASK,  0, PARITY_POS ),
                PARITY_EVEN     = mskd_t(PARITY_MASK,  1, PARITY_POS ),
                PARITY_CRC      = mskd_t(PARITY_MASK,  2, PARITY_POS );

Defining multiple bit spans with arbitrary values, limit checking, and bit shifting (see [Shifted values](#shifted_values), above, and [Templates for numerically-defined constants](#templates_numeric_constants), below).

        REGBITS_MSKD_RANGE("Serial::Config",
                           RXPORT,
                           rxport,
                           RXPORT_MASK,
                           RXPORT_POS,
                           MAX_PORT_NUM);

End the register definition, define a type name for possible external use, and allocate storage for the register. This where the peripheral struct gets a finite size (and layout) to match the actual hardware peripheral when a pointer to its address is declared.

            };    // struct Config
            using config_t = Reg<uint32_t, Config>;
            config_t    config;

More register definitions:

            struct Interrupts {
            // ...

End peripheral definition and check that size is correct:

        };    // struct Serial
        static_assert(sizeof(Serial) == 24, "sizeof(Serial)");

Define pointers to actual hardware peripherals:

        static const uint32_t   PERIPH_BASE     = 0x40000000;

        static const uint32_t   SERIAL_BASE     = PERIPH_BASE + 0x00a00000;

        static const uint32_t   SERIAL0_BASE    = SERIAL_BASE + 0x00000000,
                                SERIAL1_BASE    = SERIAL_BASE + 0x00001000,
                                SERIAL1_BASE    = SERIAL_BASE + 0x00002000;

        static Serial* const    serial0 = reinterpret_cast<Serial*>(SERIAL0_BASE);
        static Serial* const    serial1 = reinterpret_cast<Serial*>(SERIAL1_BASE);
        static Serial* const    serial2 = reinterpret_cast<Serial*>(SERIAL2_BASE);



Comparison with other approaches <a name="comparison_with_other_approaches"></a>
--------------------------------

(This material is included as background for the design of regbits. Experienced microcontroller programmers will be very familiar with the approaches and should skip ahead to the [Requirements, limitations, problems](#requirements_limitations_problems) section, below.)


Two different sets of information need to be provided to client code:

1. Registers order/layout within peripherals
2. Bits within the registers

Some current approaches for addressing both of these requirements are described (somewhat intermixed) in the following sections.


#### Raw numeric register addresses and bits <a name="raw_numeric_values"></a>

source (.c) file:

        *(int*)(0x400080a2) = 0xc0;

This is sadomasochism -- sadism inflicted on anyone else who has to work with the code, and masochism on the part of the original developer who needs to maintain or debug it in the future.

##### pros:
* no definition file needed

##### cons:
* completely opaque; inherently undocumented
* requires constant reference to external manuals
* error prone, typos almost impossible to detect


#### Preprocessor symbolic peripheral addresses and register offsets <a name="preprocessor_symbolic_peripheral_addresses_and_register_offsets"></a>

##### source (.c) file:

        *(TIMER1 + TIMER_CTRL_OFFSET) = //...

##### definition (.h) file:

        #define TIMER_BASE              ((PERIPH_BASE) + 0x00200000)

        #define TIMER0_BASE             ((TIMER_BASE)  + 0x00000000)
        #define TIMER1_BASE             ((TIMER_BASE)  + 0x00001000)
        #define TIMER2_BASE             ((TIMER_BASE)  + 0x00002000)

        #define TIMER0                  ((volatile uint32_t*)(TIMER0_BASE))
        #define TIMER1                  ((volatile uint32_t*)(TIMER1_BASE))
        #define TIMER2                  ((volatile uint32_t*)(TIMER2_BASE))

        #define TIMER_CONTROL_OFFSET    0
        #define TIMER_PRESCALE_OFFSET   1
        #define TIMER_AUTORELOAD_OFFSET 2

##### pros:

* more readable / self-documenting

##### cons:

* verbose and error-prone
* not type-safe, no error detection



#### Preprocessor symbolic bit definitions <a name="preprocessor_symbolic_bit_definitions"></a>

###### source (.c) file:

        // set_bits
        /*...*/ = TIMER_CONTROL_ENABLE | TIMER_CONTROL_CLOCK_SOURCE_PLL;

        // clear bits
        /*...*/ &= ~(TIMER_CONTROL_ENABLE | TIMER_CONTROL_DIRECTION);

        // insert field
        /*...*/ = (/*...*/ & ~TIMER_CONTROL_CLOCK_SOURCE_MSK) | TIMER_CONTROL_CLOCK_SOURCE_PLL;

###### definition (.h) file:

        #define TIMER_CONTROL_ENABLE_POS          4
        #define TIMER_CONTROL_SINGLE_CYCLE_POS    5
        #define TIMER_CONTROL_ARR_ENABLE_POS      6
        #define TIMER_CONTROL_CLOCK_SOURCE_POS    7
        #define TIMER_CONTROL_DIRECTION_POS       10

        #define TIMER_CONTROL_ENABLE_MSK          (1 << TIMER_CONTROL_ENABLE_POS)
        #define TIMER_CONTROL_SINGLE_CYCLE_MSK    (1<< TIMER_CONTROL_SINGLE_CYCLE_POS)
        #define TIMER_CONTROL_SINGLE_CYCLE        TIMER_CONTROL_SINGLE_CYCLE_MSK
        #define TIMER_CONTROL_ARR_ENABLE_MSK      (1 << TIMER_CONTROL_ARR_ENABLE_POS)
        #define TIMER_CONTROL_ARR_ENABLE          TIMER_CONTROL_ARR_ENABLE_MSK
        #define TIMER_CONTROL_ENABLE              TIMER_CONTROL_ENABLE_MSK
        #define TIMER_CONTROL_CLOCK_SOURCE_MSK    (0x7 << TIMER_CONTROL_CLOCK_SOURCE_POS)
        #define TIMER_CONTROL_CLOCK_SOURCE_MAIN   (0x0 << TIMER_CONTROL_CLOCK_SOURCE_POS)
        #define TIMER_CONTROL_CLOCK_SOURCE_PLL    (0x1 << TIMER_CONTROL_CLOCK_SOURCE_POS)
        #define TIMER_CONTROL_CLOCK_SOURCE_EXTERN (0x2 << TIMER_CONTROL_CLOCK_SOURCE_POS)
        #define TIMER_CONTROL_DIRECTION_MSK       (1 << TIMER_CONTROL_DIRECTION_POS)
        #define TIMER_CONTROL_DIRECTION           TIMER_CONTROL_DIRECTION_MSK

        #define TIMER_MAX_PRESCALER_VAL           0xff
        #define TIMER_PRESCALE_PRESCALER_POS      24
        #define TIMER_PRESCALE_PRESCALER_MSK      (0xff << TIMER_PRESCALE_PRESCALER_POS)

        #define TIMER_MAX_AUTORELOAD_VAL          0x00ffffff
        #define TIMER_AUTORELOAD_AUTORELOAD_POS   0
        #define TIMER_AUTORELOAD_AUTORELOAD_MSK   (0xffffff << TIMER_AUTORELOAD_AUTORELOAD_POS)

###### pros:
* self-documenting

###### cons:
* global scope
* verbose (due to need to prefix/disambiguate many similar names)
* not type-safe
* no error checking
* not visible in debuggers (exception: gcc "`-g3`" flag)


#### Static consts <a name="static_consts"></a>

##### source (.c) file:

(same as [Preprocessor symbolic peripheral addresses and register offsets](#preprocessor_symbolic_peripheral_addresses_and_register_offsets) and  [Preprocessor symbolic bit definitions](#preprocessor_symbolic_bit_definitions), above.)

##### definition (.h) file:

        static const uint8_t    TIMER_CONTROL_ENABLE_POS       =  4,
                                TIMER_CONTROL_SINGLE_CYCLE_POS =  5,
                                TIMER_CONTROL_ARR_ENABLE_POS   =  6,
                                TIMER_CONTROL_CLOCK_SOURCE_POS =  7,
                                TIMER_CONTROL_DIRECTION_POS    = 10;

        static const uint32_t   TIMER_CONTROL_ENABLE_MSK          = (1 << TIMER_CONTROL_ENABLE_POS)              ,
                                TIMER_CONTROL_SINGLE_CYCLE_MSK    = (1<< TIMER_CONTROL_SINGLE_CYCLE_POS)         ,
                                TIMER_CONTROL_SINGLE_CYCLE        = TIMER_CONTROL_SINGLE_CYCLE_MSK               ,
                                TIMER_CONTROL_ARR_ENABLE_MSK      = (1 << TIMER_CONTROL_ARR_ENABLE_POS)          ,
                                TIMER_CONTROL_ARR_ENABLE          = TIMER_CONTROL_ARR_ENABLE_MSK                 ,
                                TIMER_CONTROL_ENABLE              = TIMER_CONTROL_ENABLE_MSK                     ,
                                TIMER_CONTROL_CLOCK_SOURCE_MSK    = (0x7 << TIMER_CONTROL_CLOCK_SOURCE_POS)      ,
                                TIMER_CONTROL_CLOCK_SOURCE_MAIN   = (0x0 << TIMER_CONTROL_CLOCK_SOURCE_POS)      ,
                                TIMER_CONTROL_CLOCK_SOURCE_PLL    = (0x1 << TIMER_CONTROL_CLOCK_SOURCE_POS)      ,
                                TIMER_CONTROL_CLOCK_SOURCE_EXTERN = (0x2 << TIMER_CONTROL_CLOCK_SOURCE_POS)      ,
                                TIMER_CONTROL_DIRECTION_MSK       = (1 << TIMER_CONTROL_DIRECTION_POS)           ,
                                TIMER_CONTROL_DIRECTION           = TIMER_CONTROL_DIRECTION_MSK                  ,
                                                                  = TIMER_MAX_PRESCALER_VAL= 0xff                ,
                                TIMER_PRESCALE_PRESCALER_POS      = 24                                           ,
                                TIMER_PRESCALE_PRESCALER_MSK      = (0xff << TIMER_PRESCALE_PRESCALER_POS)       ,
                                                                  =                                              ,
                                TIMER_MAX_AUTORELOAD_VAL          = 0x00ffffff                                   ,
                                TIMER_AUTORELOAD_AUTORELOAD_POS   = 0                                            ,
                                TIMER_AUTORELOAD_AUTORELOAD_MSK   = (0xffffff << TIMER_AUTORELOAD_AUTORELOAD_POS);

and if used for raw numeric register addresses and bits ([above[(raw_numeric_values)):

        static const uint32_t   TIMER_BASE  = PERIPH_BASE + 0x00c00000;

        static const uint32_t   TIMER0_BASE = TIMER_BASE  + 0x00000000,
                                TIMER1_BASE = TIMER_BASE  + 0x00001000,
                                TIMER2_BASE = TIMER_BASE  + 0x00002000;

        static volatile uint32_t* const   TIMER0 = (volatile uint32_t*)TIMER0_BASE;
        static volatile uint32_t* const   TIMER1 = (volatile uint32_t*)TIMER1_BASE;
        static volatile uint32_t* const   TIMER2 = (volatile uint32_t*)TIMER2_BASE;

        static const uint32_t   TIMER_CONTROL_OFFSET    = 0,
                                TIMER_PRESCALE_OFFSET   = 1,
                                TIMER_AUTORELOAD_OFFSET = 2;

##### pros:
* self-documenting
* type-safe
* can be namespace-scoped (C++, short, non-prefixed names)

##### cons:
* (in C) global scope, verbose (due to need to prefix/disambiguate many similar names)
* no error checking
* memory space for variables (potentially thousands) in executable binary if appropriate compiler flags not used


#### C/C++ enums <a name="c_cxx_enums"></a>

##### source (.c) file:

(same as [Preprocessor symbolic peripheral addresses, register offsets](#preprocessor_symbolic_peripheral_addresses_and_register_offsets) and  [Preprocessor symbolic bit definitions](#preprocessor_symbolic_bit_definitions), and [Static consts](#static_consts) above.)

##### definition (.h) file (C code):

        enum TIMER_CONTROL_POS {
            TIMER_CONTROL_ENABLE_POS       =   4,
            TIMER_CONTROL_SINGLE_CYCLE_POS =   5,
            TIMER_CONTROL_ARR_ENABLE_POS   =   6,
            TIMER_CONTROL_CLOCK_SOURCE_POS =   7,
            TIMER_CONTROL_DIRECTION_POS    =  10,
        };

        enum TIMER_CONTROL_BITS {
            TIMER_CONTROL_ENABLE_MSK          = (1 << TIMER_CONTROL_ENABLE_POS),
            TIMER_CONTROL_SINGLE_CYCLE_MSK    = (1<< TIMER_CONTROL_SINGLE_CYCLE_POS),
            TIMER_CONTROL_SINGLE_CYCLE        = TIMER_CONTROL_SINGLE_CYCLE_MSK,
            TIMER_CONTROL_ARR_ENABLE_MSK      = (1 << TIMER_CONTROL_ARR_ENABLE_POS),
            TIMER_CONTROL_ARR_ENABLE          = TIMER_CONTROL_ARR_ENABLE_MSK,
            TIMER_CONTROL_ENABLE              = TIMER_CONTROL_ENABLE_MSK,
            TIMER_CONTROL_CLOCK_SOURCE_MSK    = (0x7 << TIMER_CONTROL_CLOCK_SOURCE_POS),
            TIMER_CONTROL_CLOCK_SOURCE_MAIN   = (0x0 << TIMER_CONTROL_CLOCK_SOURCE_POS),
            TIMER_CONTROL_CLOCK_SOURCE_PLL    = (0x1 << TIMER_CONTROL_CLOCK_SOURCE_POS),
            TIMER_CONTROL_CLOCK_SOURCE_EXTERN = (0x2 << TIMER_CONTROL_CLOCK_SOURCE_POS),
            TIMER_CONTROL_DIRECTION_MSK       = (1 << TIMER_CONTROL_DIRECTION_POS),
            TIMER_CONTROL_DIRECTION           = TIMER_CONTROL_DIRECTION_MSK,
        };

        enum TIMER_PRESCALE_BITS {
            TIMER_MAX_PRESCALER_VAL      = 0xff,
            TIMER_PRESCALE_PRESCALER_POS = 16,
            TIMER_PRESCALE_PRESCALER_MSK = 0xff << TIMER_PRESCALE_PRESCALER_POS,
        };

        enum TIMER_AUTORELOAD_BTIS {
            TIMER_MAX_AUTORELOAD_VAL        = 0x00ffffff,
            TIMER_AUTORELOAD_AUTORELOAD     = 0,
            TIMER_AUTORELOAD_AUTORELOAD_MSK = 0xffffff<< << TIMER_AUTORELOAD_AUTORELOAD_POS,
        };


##### definition (.h) file (C++ code):

        enum class TIMER_CONTROL {
            ENABLE       =  4,
            SINGLE_CYCLE =  5,
            ARR_ENABLE   =  6,
            CLOCK_SOURCE =  7,
            DIRECTION    = 10,
        };

        enum class TIMER_CONTROL_BITS {
            ENABLE_MSK          = (1 << static_cast<uint32_t>(TIMER_CONTROL::ENABLE)),
            ENABLE              = ENABLE_MSK,
            SINGLE_CYCLE_MSK    = (1<< static_cast<uint32_t>(TIMER_CONTROL::SINGLE_CYCLE)),
            SINGLE_CYCLE        = SINGLE_CYCLE_MSK,
            ARR_ENABLE_MSK      = (1 << static_cast<uint32_t>(TIMER_CONTROL::ARR_ENABLE)),
            ARR_ENABLE          = ARR_ENABLE_MSK,
            CLOCK_SOURCE_MSK    = (0x7 << static_cast<uint32_t>(TIMER_CONTROL::CLOCK_SOURCE)),
            CLOCK_SOURCE_MAIN   = (0x0 << static_cast<uint32_t>(TIMER_CONTROL::CLOCK_SOURCE)),
            CLOCK_SOURCE_PLL    = (0x1 << static_cast<uint32_t>(TIMER_CONTROL::CLOCK_SOURCE)),
            CLOCK_SOURCE_EXTERN = (0x2 << static_cast<uint32_t>(TIMER_CONTROL::CLOCK_SOURCE)),
            DIRECTION_MSK       = (1 << static_cast<uint32_t>(TIMER_CONTROL::DIRECTION)),
            DIRECTION            = DIRECTION_MSK,
        };


        enum class TIMER_PRESCALE_BITS {
            MAX_PRESCALER_VAL  = 0xff,
            PRESCALER_POS      = 16,
            PRESCALER_MSK      = (0xff << static_cast<uint32_t>(PRESCALER_POS),
        };

        enum class TIMER_AUTORELOAD_BTIS {
            AUTORELOAD_VAL  =  0x00ffffff,
            AUTORELOAD_POS  =  0,
            AUTORELOAD_MSK  = (0xffffff  << static_cast<uint32_t>(AUTORELOAD_POS),
        };


##### pros:
* self-documenting
* short class-scoped names (C++)
* type-safe (C++) (but not really due to need to cast before use)

##### cons:
* requires casting before use (C++)
* requires C++11 or higher (C++)
* global scope, verbose (due to need to prefix/disambiguate many similar names) (C)
* not type-safe (`C`)
* no error checking (`C`)


#### C structs <a name="c_structs"></a>

(The most commonly used technique.)

##### source (.c) file:

        // set value
        TIMER1->CTRL = value;

        // set bits without affecting others
        GPIO1->SET |= value;

        // clear bits without affecting others
        SYS->INTERRUPTS &= ~value;

        // insert bits without affecting others
        USART1->SPEED = (USART1->SPEED & mask) | value;

(values via numeric values, #defines, static consts, enums, etc)


##### definition (.h) file: <a name="c_structs_definition_file"></a>

        typedef struct serial {
                volatile uint32_t       CONTROL  ;
                volatile uint32_t       CONFIG   ;
                volatile uint32_t       INTERRUPT;
                volatile uint32_t       STATUS   ;
                volatile uint32_t       RXBUFFER ;
                volatile uint32_t       TXBUFFER ;
        } serial_t;

        #ifdef USE_PREPROCESSOR_ADDRESSES
        #define SERIAL_BASE     ((PERIPH_BASE) + 0x00a00000)

        #define SERIAL0_BASE    ((SERIAL_BASE) + 0x00000000)
        #define SERIAL1_BASE    ((SERIAL_BASE) + 0x00001000)
        #define SERIAL2_BASE    ((SERIAL_BASE) + 0x00002000)

        #define SERIAL0         ((serial_t*)(SERIAL0_BASE))
        #define SERIAL1         ((serial_t*)(SERIAL1_BASE))
        #define SERIAL2         ((serial_t*)(SERIAL2_BASE))
        #endif

        #ifdef USE_STATIC_CONST_ADDRESSES
        static const uint32_t   SERIAL_BASE     = PERIPH_BASE + 0x00a00000;

        static const uint32_t   SERIAL0_BASE    = SERIAL_BASE + 0x00000000,
                                SERIAL1_BASE    = SERIAL_BASE + 0x00001000,
                                SERIAL1_BASE    = SERIAL_BASE + 0x00002000;

        
        static serial_t* const  SERIAL0         = (serial_t*)SERIAL0_BASE;
        static serial_t* const  SERIAL1         = (serial_t*)SERIAL1_BASE;
        static serial_t* const  SERIAL2         = (serial_t*)SERIAL2_BASE;
        #endif

        // constants via #defines, static consts, enums, etc)
        // ...

##### pros:
* self-documenting
* type-safe peripheral and register definitions

##### cons:
* bit values not type-safe
* struct name frequently omitted (superceded by typedef) thus not allowing forward declaration


#### C bitfields <a name="c_bitfields"></a>

C bitfields would seem to solve all requirements for independent/atomic/isolated register bit access:

##### source (.c) file:

        // set single bit
        SERIAL2->config.polarity = 1;
        
        // clear single bit
        SERIAL2->config.polarity = 0;

        // set span of bits
        SERIAL2->config.datalen = SERIAL_CONFIG_DATALEN_8_BITS;

        // clear span of bits
        SERIAL2->config.datalen = 0;

##### definition (.h) file:

        typedef struct serial {
            volatile struct {
                unsigned    enable :  1,
                            recv   :  1,
                            xmit   :  1,
                                   : 29;
                };
            } control;

            volatile struct {
                unsigned    mode     :  1,
                            datalen  :  2,
                            parity   :  2,
                            endian   :  1,
                            polarity :  1,
                            rxport   :  5,
                            txport   :  5,
                                     : 15;
            } config;
        } serial_t;

        // (addresses of peripheral instances as per [C structs](#c_structs_definition_file), above)

        // (values for multi-bit fields via numeric values, #defines, static consts, enums, etc)

Unfortunately, there are several problems with this feature of C/C++. First, testing bitfield values generates more executable/object code than other approaches by necessitating large amounts of bit masking and shifting:

        // other approaches
        SERIAL2->parity = ODD_PARITY;
        if (SERIAL2->parity == ODD_PARITY) // ...

        //  bitfield
        register = 0;
        SERIAL2->config.parity = ODD_PARITY;
        if (SERIAL2->config.parity == ODD_PARITY) // ...

        // equivalent code to that generated by bitfield approach
        SERIAL2->config = ODD_PARITY << PARITY_POSITION;
        if (((SERIAL2->config & 0x18) >> 3) == ODD_PARITY) // ...

(In the other approaches `ODD_PARITY` has been pre-shifted to its correct bit position.)

But a much worse inefficiency, both in source code verbosity and more importantly executable/object code size and speed, occurs when multiple individual bit fields need to be set/cleared/modified:

        // other approaches
        SERIAL2->parity = ODD_PARITY | BIG_ENDIAN;

        // bitfields
        SERIAL2->config.parity = ODD_PARITY;
        SERIAL2->config.endian = 1;

        // equivalent bitfield code -- two writes to register instead of one
        SERIAL2->config = (SERIAL2->config & ~PARITY_MASK) | (ODD_PARITY << PARITY_POSITION);
        SERIAL2->config = (SERIAL2->config & ~ENDIAN_MASK) | (1          << ENDIAN_POSITION);

Some of this inefficiency can be avoided by creating a union between the C bitfields and a variable of the architecture's native word size:

        union CONFIG_T {
            volatile uint32_t    word;
            volatile struct {
                unsigned    mode     :  1,
                            datalen  :  2,
                            parity   :  2,
                            endian   :  1,
                            polarity :  1,
                            rxport   :  5,
                            txport   :  5,
                                     : 15;
            };
        } config;

In this way at least the entire register can be cleared in one operation. But setting or clearing multiple fields at once requires including `#define` or `static const` definitions as per the other approaches. This effectively doubles the size and complexity of the definition file and the effort to create it, and introduces the risk of mismatched definitions, etc.

Finally, there does exist the possibility that a very "smart" compiler could detect the multiple settings and coalesce them into a single or at least smaller set of operations.

##### pros:
* self-documenting
* type-safe, intuitive access to register bits/fields

##### cons:
* inefficient
* may require duplicate, possibly mismatched definitions
* multi-bit values not type-safe


#### Helper functions <a name="helper_functions"></a>

Helper functions can simplify usage of many of the above approaches, particularly for inserting single bits and multiple fields (not needed for C bitfields).

Functions may be implemented as parameterized preprocessor macros:

        #define GET_BITS(REG, MASK) ((REG) & (MASK))

        #define SET_BITS(REG, BITS) ((REG) |= (BITS))

        #define CLR_BITS(REG, BITS) ((REG) &= ~(BITS))

        #define FLIP_BITS(REG, BITS) (REG) ^= (BITS)

        #define INSERT_BITS(REG, MASK, BITS) ((REG) = ((REG & ~(MASK)) | (BITS)))

or as C inline functions:

        inline uint32_t GET_BITS(
        volatile uint32_t   &reg,
        const    uint32_t    mask)
        {
            return reg & mask;
        };

        inline void SET_BITS(
        volatile uint32_t   &reg,
        const    uint32_t    bits)
        {
            reg |= bits;
        };


        inline void CLR_BITS(
        volatile uint32_t   &reg,
        const    uint32_t    bits)
        {
            reg &= ~bits;
        };

        inline void FLP_BITS(
        volatile uint32_t    &reg,
        const    uint32_t     bits)
        {
            reg |= bits;
        };

        inline void INS_BITS(
        volatile uint32_t   &reg,
        const    uint32_t    mask,
        const    uint32_t    bits)
        {
            reg = (reg & ~mask) | bits;
        };

or as C++ inline function templates:

        template <typename UINT_T> inline UINT_T GET_BITS(
        volatile UINT_T   &reg,
        const    UINT_T    mask)
        {
            return reg & mask;
        };

        template <typename UINT_T> inline void SET_BITS(
        volatile UINT_T   &reg,
        const    UINT_T    bits)
        {
            reg |= bits;
        };


        template <typename UINT_T> inline void CLR_BITS(
        volatile UINT_T   &reg,
        const    UINT_T    bits)
        {
            reg &= ~bits;
        };

        template <typename UINT_T> inline void FLP_BITS(
        volatile UINT_T    &reg,
        const    UINT_T     bits)
        {
            reg |= bits;
        };

        template <typename UINT_T> inline void INS_BITS(
        volatile UINT_T   &reg,
        const    UINT_T    mask,
        const    UINT_T    bits)
        {
            reg = (reg & ~mask) | bits;
        };

##### pros:
* reduces source code verbosity
* simplifies accesses
* reduces liklihood of errors
* C++ version type-safe

##### cons:
* C version not type-safe


#### Higher-level wrappers <a name="Higher-level_wrappers"></a>

Regbits and the existing approaches described above are intended for low-level, "bare metal" ("bare silicon"?) programming. There also exist higher-level libraries which attempt to make programming microcontrollers easier, simpler, and more generic and portable,

Some examples include:

* Arduino (<https://www.arduino.cc/>)
* openocd (<http://openocd.org/>)
* STM HAL
* NXP LPCXpresso and MCUXpresso

It is this author's opinion that such libraries rarely achieve their goals. They introduce entirely new/large/complex APIs on top of the native MCU's and do not remove the need to fully understand the underlying hardware. They are also inefficient, introducing additional levels of function calls and frequently a requirement to allocate (statically, on the stack, or in dynamic memory) large data structures to be passed to the library's functions. They often do not support much if any compile time type-safety, instead replacing it with runtime checks which subsequently requires solving the difficult problem of how to handle fatal coding errors in (possibly safety-critical) embedded applications.



Regbits requirements, limitations, problems <a name="requirements_limitations_problems"></a>
-----------------------------------

#### Compiler optimization

Regbits requires a C++11 or later compiler. It should run correctly at any optimization level; however gcc optimization `-O1` or higher is needed as otherwise storage is allocated for the peripheral/register constant objects. (There are likely individual optimization flags which would allow `-O0` without the excess allocations.)


#### Parameter passing

Regbits is specifically designed for passing its (usually constant) objects to functions by value, not by reference. The objects are either one (regbits::Bits) or two (regbits::Mskd) native words in size, and at least on ARM architectures they should be passed in registers. If optimization is not enabled, gcc passes them on the stack.

Note that with at least with:

        (GNU Tools for Arm Embedded Processors 8-2018-q4-major) 8.2.1 20181213 (release) [gcc-8-branch revision 267074]

`-mabi=apcs-gnu` or `-mabi=atpcs` must be specified in order to force passing regbits objects in registers. Code will compile and run without these flags, however it will not be as small/fast/efficient as possible (and possibly less efficient in that case than other approaches, such as C structs).


#### Forcing use of constants

Further, gcc/g++ will sometimes require a static constexpr regbits object to be instantiated in memory instead of being treated as a compile-time-only constant. This requires a (small amount) of unnecessary storage, and unless defined manually causes an undefined variable error at runtime.

To work around the problem, regbits implements a unary `operator+()` for its objects. Client code should use this as needed, typically only when passing objects as parameters to functions:

        // do this:
        func(+Serial::Config::DATALEN_16_BITS);

        // ... instead of this:
        func(Serial::Config::DATALEN_16_BITS);

There is no runtime cost for using the operator; in fact the opposite (it forces the object to be passed in registers instead of the stack). Suggestions for a better solution are hereby solicited.


#### Insert operator syntax <a name="insert_operator_syntax"></a>

Choice of syntax for regbits's insert operator is difficult and debatable.

To match what the operator actually does, the following ("invert mask, `AND` with register, then `OR` in bits.) would be intuitive:

        serial2->config ~&|= Serial::Config::DATALEN_16_BITS

This is of course impossible in C/C++. Perhaps better (but even further removed from permissible C/C++ syntax) would be:

        serial2->config @= Serial::Config::DATALEN_16_BITS

An earlier release of regbits used:

        serial2->config <<= Serial::Config::DATALEN_16_BITS

which somewhat matched the C++ Standard Libary's `ostream<<` operator. That particular syntax is unworkable due to C/C++ operator precedence rules which work perfectly for `ostream`s:

        // plain
        std::cout << a << b << c << std::endl;

        // equivalent explicitly parenthesized
        ((((std::cout << a) << b) << c) << std::endl);

but very poorly for regbits' insert:

        // parentheses required:
        serial2->config << (Serial::Config::DATALEN_16_BITS | Serial);

because without parentheses:

        serial2->config << Serial::Config::DATALEN_16_BITS | Serial;

would following equivalent would be compiled:

        (serial2->config << Serial::Config::DATALEN_16_BITS) | Serial;

Regbit's insert operator intentionally returns void (*not* `regbits::Reg&`) because otherwise the above would result in two operations to the hardware register, which would be inefficient and possible problematic (see [below](#future_enhancements) regarding non-memory-like semantics of microcontroller registers).

This release of regbits -- for lack of a better alternative --  uses "`/=`":

        serial2->config /= Serial::Config::DATALEN_16_BITS;

Not ideal, but possibly the best of the various poor options. An (unconvincing) argument can be made that the operator "divides" the register before subsequently inserting the `mskd_t` object's value. 

Admittedly, there is possible confusion between:

        serial2->config /= Serial::Config::DATALEN_16_BITS;
        serial2->config |= Serial::Config::DATALEN_16_BITS;

both of which are valid, useful, but different operators. The fact that the glyphs are sufficiently distinct in most software-coding fonts partly alleviates the problem. And finally, to close out this overly-long section:

        serial2->config %= Serial::Config::DATALEN_16_BITS;

was considered too ugly and confusing. Alternate suggestions (if any exist) welcome, and please feel free to use the equivalent, verbose regbits `ins` method:

        serial2->config.ins(Serial::Config::DATALEN_16_BITS);



#### Templates for numerically-defined constants <a name="templates_numeric_constants"></a>

Constants defining regbits Bits and Mskd objects are intended to generally be declared with semantically-meaningful names, as per [above](#regbits_bits_t_and_mskd_t).

This scheme is workable (though tedious) up through, for example, defining 32 individual bits in a 32-bit register:

        static constexpr pos_t  PORT_0_POS  = pos_t( 0),
                                PORT_1_POS  = pos_t( 1),
                                PORT_2_POS  = pos_t( 2),
                                PORT_3_POS  = pos_t( 3),
                                PORT_4_POS  = pos_t( 4),
                                PORT_5_POS  = pos_t( 5),
                                PORT_6_POS  = pos_t( 6),
                                PORT_7_POS  = pos_t( 7),
                                PORT_8_POS  = pos_t( 8),
                                PORT_9_POS  = pos_t( 9),
                                PORT_10_POS = pos_t(10),
                                PORT_11_POS = pos_t(11),
                                PORT_12_POS = pos_t(12),
                                PORT_13_POS = pos_t(13),
                                PORT_14_POS = pos_t(14),
                                PORT_15_POS = pos_t(15),
                                PORT_16_POS = pos_t(16),
                                PORT_17_POS = pos_t(17),
                                PORT_18_POS = pos_t(18),
                                PORT_19_POS = pos_t(19),
                                PORT_20_POS = pos_t(20),
                                PORT_21_POS = pos_t(21),
                                PORT_22_POS = pos_t(22),
                                PORT_23_POS = pos_t(23),
                                PORT_24_POS = pos_t(24),
                                PORT_25_POS = pos_t(25),
                                PORT_26_POS = pos_t(26),
                                PORT_27_POS = pos_t(27),
                                PORT_28_POS = pos_t(28),
                                PORT_29_POS = pos_t(29),
                                PORT_30_POS = pos_t(30),
                                PORT_31_POS = pos_t(31);

        static constexpr bits_t PORT_0  = bits_t(1, PORT_0_POS ),
                                PORT_1  = bits_t(1, PORT_1_POS ),
                                PORT_2  = bits_t(1, PORT_2_POS ),
                                PORT_3  = bits_t(1, PORT_3_POS ),
                                PORT_4  = bits_t(1, PORT_4_POS ),
                                PORT_5  = bits_t(1, PORT_5_POS ),
                                PORT_6  = bits_t(1, PORT_6_POS ),
                                PORT_7  = bits_t(1, PORT_7_POS ),
                                PORT_8  = bits_t(1, PORT_8_POS ),
                                PORT_9  = bits_t(1, PORT_9_POS ),
                                PORT_10 = bits_t(1, PORT_10_POS),
                                PORT_11 = bits_t(1, PORT_11_POS),
                                PORT_12 = bits_t(1, PORT_12_POS),
                                PORT_13 = bits_t(1, PORT_13_POS),
                                PORT_14 = bits_t(1, PORT_14_POS),
                                PORT_15 = bits_t(1, PORT_15_POS),
                                PORT_16 = bits_t(1, PORT_16_POS),
                                PORT_17 = bits_t(1, PORT_17_POS),
                                PORT_18 = bits_t(1, PORT_18_POS),
                                PORT_19 = bits_t(1, PORT_19_POS),
                                PORT_20 = bits_t(1, PORT_20_POS),
                                PORT_21 = bits_t(1, PORT_21_POS),
                                PORT_22 = bits_t(1, PORT_22_POS),
                                PORT_23 = bits_t(1, PORT_23_POS),
                                PORT_24 = bits_t(1, PORT_24_POS),
                                PORT_25 = bits_t(1, PORT_25_POS),
                                PORT_26 = bits_t(1, PORT_26_POS),
                                PORT_27 = bits_t(1, PORT_27_POS),
                                PORT_28 = bits_t(1, PORT_28_POS),
                                PORT_29 = bits_t(1, PORT_29_POS),
                                PORT_30 = bits_t(1, PORT_30_POS),
                                PORT_31 = bits_t(1, PORT_31_POS);

It becomes completely untenable with larger potential numbers of constants:

        static constexpr pos_t      AUTORELOADER_POS = pos_t(0);

        static const uint32_t       AUTORELOAD_MASK   = 0x00ffffff;

        static constexpr mskd_t     AUTORELOAD_0(AUTORELOAD_MASK, 0, AUTORELOADER_POS),
                                    AUTORELOAD_1(AUTORELOAD_MASK, 1, AUTORELOADER_POS),
                                    AUTORELOAD_2(AUTORELOAD_MASK, 2, AUTORELOADER_POS),
                                    // 16777212 more ...
                                    AUTORELOAD_ffffff(AUTORELOAD_MASK, 0xffffff, AUTORELOADER_POS);

Regardless this problem, the symbolic names provide little additional value compared to some means of specifying the objects by numeric value (as long as type-safety and range checking is maintained):

        // fictitious example, for illustration only
        timer2->autoreload = Timer::Autoreload::mskd_t(9347);

To work around the problem, regbits supports the following function template. Because it is verbose and may need to be used many times in an mcu/peripheral/register definition file, a parameterized preprocessor macro is provided:

        #define REGBITS_MSKD_RANGE(CLASS, CONSTEXPR_FUNC, RUNTIME_FUNC, VALID_FUNC, MASK, POS, LIMIT) \

The macro first defines a `shft_t` constant (see [Shifted values](#shifted_values), above):

        static constexpr shft_t          CONSTEXPR_NAME##_SHFT       \
                                    = shft_t(CONSTEXPR_NAME##_MASK,  \
                                             CONSTEXPR_NAME##_POS ); \


It then defines a function template for compile time generation of a static `mskd_t` object with the appropriate `.mask()` and `.bits()` values:

        template<unsigned BITS> static constexpr mskd_t CONSTEXPR_FUNC() { \
            static_assert(BITS <= LIMIT, \
                          CLASS "::" #CONSTEXPR_FUNC "<BITS> out of range"); \
            return mskd_t(MASK, BITS, POS); \
        } \
        // macro continues, discussed below

<a name="ugly_indexing_syntax"></a>
Client code uses this to instantiate desired constant objects as follows:

        Timer::Autoreload::AUTORELOAD<9347>();

Yes, the syntax is ugly, but because C++ can currently only `static_assert` on template parameters it is the only way the range checking can be implemented. (Note: There may be other workarounds but the ones this author has seen far exceed his tolerance for template metaprogramming cleverness and obfuscation. Please support proposals such as [this one](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1045r0.html) to fix the problem in future C++ standards.)

The above function template takes care of the problem with constexpr objects, which is the main thrust of regbits. However, there may be valid use cases for generating regbits Bits and Mskd objects at runtime using variable data.

The `REGBITS_MSKD_RANGE` macro continues, defining two runtime, non-templated, functions. The first is:

        static const mskd_t RUNTIME_FUNC( \
        const unsigned    bits) \
        { \
            return mskd_t(MASK << POS.pos(), bits << POS.pos()); \
        } \

This generates a Mskd object with the specified bits, using the mask defined in the macro invocation. It intentionally does no range checking, for two reasons. First, regbits is intended to be maximally efficient at runtime (the whole rationale for type-safety and range checking at compile time).

Second, regbits is intended to be used in a "bare metal" ("silicon") runtime environment, generally without C++ exceptions (or virtual methods or even dynamic memory). Given that there is no possibility of throwing an exception for out-of-range values, it is felt that the alternative -- silently clamping the value to be within range -- is a poor design decision which would typically push the inevitable code failure further down the execution path where it would be harder to find. (This is even considering the fact that the out-of-range value will very probably overwrite other, possibly crucial, bits in the register.) "Fail early, fail fast."

Range checking is still desirable, so it is provided by the third and final preprocessor-macro-defined function:

        static bool VALID_FUNC( \
        const unsigned  bits) \
        { \
            return bits <= LIMIT; \
        }

In this way it is up to the client code (i.e. programmer) to decide if and when to include runtime range checking.


#### gcc/g++ compiler bug

Unfortunately, the [Unit test suite](#unit_test), below, reveals what is almost certainly a bug in the following release of ARM gcc/g++:

        (GNU Tools for Arm Embedded Processors 8-2018-q4-major) 8.2.1 20181213 (release) [gcc-8-branch revision 267074]

The unit test suite, as well as the author's production code, places aliases for global objects in one or more configuration (`.hxx`) files. This is tested in the unit test suite's [`regbits.cxx`](unittest/regbits.cxx) via:

        namespace app_config {
        static const Serial::Config::pos_t
        SERIAL_CONFIG_POS = Serial::Config::POLARITY_POS;

        static const Serial::Config::bits_t
        SERIAL_CONFIG_BITS = Serial::Config::POLARITY;

        static const Serial::Config::mskd_t
        SERIAL_CONFIG_MSKD = Serial::Config::DATALEN_16_BITS;

        #ifdef GCC_ARM_BUG
        #include <stddef.h>
        static volatile uint32_t&          GPIO_WORD
                                        = *(  reinterpret_cast<uint32_t*>(gpio1)
                                            + (offsetof(mcu::Gpio, words) >> 2 )
                                            + 3                                   );
        #else
        static volatile uint32_t&        GPIO_WORD = gpio1->words.WORDS<3>();
        #endif

        static const Timer::Prescale::shft_t
        TIMER_PRESCALER_SHIFT = Timer::Prescale::PRESCALER_HIGH_SHFT;

        static Serial* const    SERIAL = serial2;
        }

The `#else` branch of the preprocessor conditional (which is *not* compiled by default) produces erroneous code.

This has been confirmed by running the unittests under GNU/Linux:

        g++ (SUSE Linux) 4.8.5
        Copyright (C) 2015 Free Software Foundation, Inc.

where the `#else` code produces slightly inefficient code (see [Performance claims](#performance_claims) regarding executable object code speed and size, below) that nevertheless produces the correct results. Additionally, `gdb` has been used to step through the two versions of the code (resulting from use of one or the other of the `unit32_t&` `#ifdef`s) which confirmed the correct behaviors.

When compiled and run on an ARM MCU with above gcc-arm compiler, the `#ifdef GCC_ARM_BUG` implementation functions correctly. This has been confirmed by:

1. Comparing the disassembled object code to that from the [`struct.c`](unittest/struct.c) C structures implementation (the code is identical)

2.  Comparing the `gdb` results from the unittests (see [Running the unittests](#running_unittests), below)

3. Stepping through the binary's execution using `gdb`, as per the following commented output:

Set breakpoint and run (`continue` instead of `run` required in embedded GDN):

        (gdb) break assign_array_global
        Breakpoint 1 at 0x10000684: file ../../../../regbits.cxx, line 1123.
        (gdb) continue
        Continuing.
        Breakpoint 1, assign_array_global () at ../../../../regbits.cxx:1123
        1123        app_config::GPIO_WORD = 189;

Hit breakpoint, disassemble code:

        (gdb) disassemble
        Dump of assembler code for function assign_array_global():
        => 0x10000684 <+0>:     ldr     r3, [pc, #8]    ; (0x10000690 <assign_array_global()+12>)
           0x10000686 <+2>:     ldr     r3, [r3, #0]
           0x10000688 <+4>:     movs    r2, #189        ; 0xbd
           0x1000068a <+6>:     str     r2, [r3, #0]
           0x1000068c <+8>:     bx      lr
           0x1000068e <+10>:    nop                     ; (mov r8, r8)
           0x10000690 <+12>:    asrs    r4, r3, #23
           0x10000692 <+14>:    asrs    r0, r0, #32
        End of assembler dump.

Note `gdb` is confused by the 32-bit data word at the end of the function. The two `asrs` instructions are actually an address to be loaded as per the instruction at address `0x10000684`:

        (gdb) x/1wx 0x10000690
        0x10000690 <assign_array_global()+12>:  0x100015dc

Step through function:

        (gdb) set disassemble-next-line on
        (gdb) x/1wx 0x100015dc
        0x100015dc <_ZN10app_configL9GPIO_WORDE>:       0x00000000
        (gdb) p/x $pc
        $1 = 0x10000684
        (gdb) display/x $r3
        1: /x $r3 = 0x0
        (gdb) display/x $r2
        2: /x $r2 = 0x58
        (gdb) display
        1: /x $r3 = 0x0
        2: /x $r2 = 0x58
        (gdb) nexti
        0x10000686      1123        app_config::GPIO_WORD = 189;
           0x10000684 <assign_array_global()+0>:        02 4b   ldr     r3, [pc, #8]    ; (0x10000690 <assign_array_global()+12>)
        => 0x10000686 <assign_array_global()+2>:        1b 68   ldr     r3, [r3, #0]
           0x10000688 <assign_array_global()+4>:        bd 22   movs    r2, #189        ; 0xbd
           0x1000068a <assign_array_global()+6>:        1a 60   str     r2, [r3, #0]
           0x1000068c <assign_array_global()+8>:        70 47   bx      lr
           0x1000068e <assign_array_global()+10>:       c0 46   nop                     ; (mov r8, r8)
           0x10000690 <assign_array_global()+12>:       dc 15   asrs    r4, r3, #23
           0x10000692 <assign_array_global()+14>:       00 10   asrs    r0, r0, #32
        1: /x $r3 = 0x100015dc
        2: /x $r2 = 0x58

The address has been loaded into ARM core register `r3`. Continue:

        (gdb) nexti
        0x10000688      1123        app_config::GPIO_WORD = 189;
           0x10000684 <assign_array_global()+0>:        02 4b   ldr     r3, [pc, #8]    ; (0x10000690 <assign_array_global()+12>)
           0x10000686 <assign_array_global()+2>:        1b 68   ldr     r3, [r3, #0]
        => 0x10000688 <assign_array_global()+4>:        bd 22   movs    r2, #189        ; 0xbd
           0x1000068a <assign_array_global()+6>:        1a 60   str     r2, [r3, #0]
           0x1000068c <assign_array_global()+8>:        70 47   bx      lr
           0x1000068e <assign_array_global()+10>:       c0 46   nop                     ; (mov r8, r8)
           0x10000690 <assign_array_global()+12>:       dc 15   asrs    r4, r3, #23
           0x10000692 <assign_array_global()+14>:       00 10   asrs    r0, r0, #32
        1: /x $r3 = 0x0
        2: /x $r2 = 0x58

This above is where the error occurs. The value at `0x100015dc` should be the address of the `gpio1->words.WORDS<3>()` array member. Instead, the compiler has not initialized it correctly -- in fact, in this ELF executable it is in the uninitialized `.bss` segment).

Continuing, the code incorrectly sets address zero to to the desired value of `189`, with potentially disastrous results:

        (gdb) nexti
        0x1000068a      1123        app_config::GPIO_WORD = 189;
           0x10000684 <assign_array_global()+0>:        02 4b   ldr     r3, [pc, #8]    ; (0x10000690 <assign_array_global()+12>)
           0x10000686 <assign_array_global()+2>:        1b 68   ldr     r3, [r3, #0]
           0x10000688 <assign_array_global()+4>:        bd 22   movs    r2, #189        ; 0xbd
        => 0x1000068a <assign_array_global()+6>:        1a 60   str     r2, [r3, #0]
           0x1000068c <assign_array_global()+8>:        70 47   bx      lr
           0x1000068e <assign_array_global()+10>:       c0 46   nop                     ; (mov r8, r8)
           0x10000690 <assign_array_global()+12>:       dc 15   asrs    r4, r3, #23
           0x10000692 <assign_array_global()+14>:       00 10   asrs    r0, r0, #32
        1: /x $r3 = 0x0
        2: /x $r2 = 0xbd
        (gdb) x/1wx 0
        0x0:    0x10002000
        (gdb) nexti
        0x1000068c      1123        app_config::GPIO_WORD = 189;
           0x10000684 <assign_array_global()+0>:        02 4b   ldr     r3, [pc, #8]    ; (0x10000690 <assign_array_global()+12>)
           0x10000686 <assign_array_global()+2>:        1b 68   ldr     r3, [r3, #0]
           0x10000688 <assign_array_global()+4>:        bd 22   movs    r2, #189        ; 0xbd
           0x1000068a <assign_array_global()+6>:        1a 60   str     r2, [r3, #0]
        => 0x1000068c <assign_array_global()+8>:        70 47   bx      lr
           0x1000068e <assign_array_global()+10>:       c0 46   nop                     ; (mov r8, r8)
           0x10000690 <assign_array_global()+12>:       dc 15   asrs    r4, r3, #23
           0x10000692 <assign_array_global()+14>:       00 10   asrs    r0, r0, #32
        1: /x $r3 = 0x0
        2: /x $r2 = 0xbd
        (gdb) x/1wx 0
        0x0:    0x000000bd

In this case (fortunately) the program doesn't crash because the LPC824 ARM Cortex-M0+ MCU it is running on has 32K of flash memory (unwritable except via special techniques) starting at address 0.

To conclude, the following is the same code running on GNU/Linux x86-64 with gcc/g++ 4.8.5 showing the correct address being loaded and stored to:

        (gdb) b assign_array_global
        Breakpoint 1 at 0x400f4b: file ../regbits.cxx, line 1125.
        (gdb) run
        ...
        Breakpoint 1, assign_array_global () at ../regbits.cxx:1125
        1125        app_config::GPIO_WORD = 189;
        Missing separate debuginfos, use: zypper install libgcc_s1-debuginfo-5.3.1+r233831-6.1.x86_64 libstdc++6-debuginfo-5.3.1+r233831-6.1.x86_64
        (gdb) disassemble 
        Dump of assembler code for function assign_array_global():
        => 0x0000000000400f4b <+0>:     mov    0x20314e(%rip),%rax        # 0x6040a0 <_ZN10app_configL9GPIO_WORDE>
           0x0000000000400f52 <+7>:     movl   $0xbd,(%rax)
           0x0000000000400f58 <+13>:    retq   
        End of assembler dump.
        (gdb) p/x $rip
        $1 = 0x400f4b
        (gdb) p/x $rax
        $2 = 0x0
        (gdb) p/x $rip + 0x20314e + 7
        $5 = 0x6040a0
        (gdb) x/1wg 0x6040a0
        0x6040a0 <_ZN10app_configL9GPIO_WORDE>: 0x000000000070012c
        (gdb) set disassemble-next-line on
        (gdb) nexti
        0x0000000000400f52      1125        app_config::GPIO_WORD = 189;
           0x0000000000400f4b <assign_array_global()+0>:        48 8b 05 4e 31 20 00    mov    0x20314e(%rip),%rax        # 0x6040a0 <_ZN10app_configL9GPIO_WORDE>
        => 0x0000000000400f52 <assign_array_global()+7>:        c7 00 bd 00 00 00       movl   $0xbd,(%rax)
           0x0000000000400f58 <assign_array_global()+13>:       c3      retq   
        (gdb) p/x $rip
        $6 = 0x400f52
        (gdb) p/x $rax
        $7 = 0x70012c
        (gdb) x/1xw 0x70012c
        0x70012c:       0x00000000
        (gdb) nexti
        0x0000000000400f58      1125        app_config::GPIO_WORD = 189;
           0x0000000000400f4b <assign_array_global()+0>:        48 8b 05 4e 31 20 00    mov    0x20314e(%rip),%rax        # 0x6040a0 <_ZN10app_configL9GPIO_WORDE>
           0x0000000000400f52 <assign_array_global()+7>:        c7 00 bd 00 00 00       movl   $0xbd,(%rax)
        => 0x0000000000400f58 <assign_array_global()+13>:       c3      retq   
        (gdb) x/1xw 0x70012c
        0x70012c:       0x000000bd

Comments and/or suggestions welcome, particularly if they identify errors in the unittest codebase which may have triggered this problem.



Unit test <a name="unit_test"></a>
---------

A unit test suite is provided [here](unittest). The suite is designed to test three aspects of regbits:

1. [Type-safe error detection](#type_safe_error_detection)
2. [Computational correctness](#computational_correctness)
3. [Performance claims](#performance_claims) (executable object code speed and size)


### Type-safe error detection <a name="type_safe_error_detection"></a>

Type-safe (and other) error detection is tested in the `linux` and `arm` subdirectories under the [`bad`](unittest/bad) directory.

"cd" to either of the subdirectories and run "make". The `Makefile` will attempt to build ("g++ -c") each of the `*.cxx` tests and confirm that, as intended, they fail to compile. For completeness, running "make GOOD=-DGOOD" will confirm that code without errors *does* compile (this detects potential bugs such as a missing include file producing an error that masks the intended regbits type-safety error).


### Computational correctness <a name="computational_correctness"></a>

Four different implementations of the tests are included. Each consists of a header definition file (peripheral and register definitions for a fictitious MCU), and a test suite source file. Each implementation should perform the same computations and produce the same results. 

* regbits: [`mcu_regbits.hxx`](unittest/mcu_regbits.hxx),  [`regbits.cxx`](unittest/regbits.cxx)
* struct (C structs): [`mcu_struct.h`](unittest/mcu_struct.h),  [`struct.c`](unittest/struct.c)
* raw (raw C pointers and offsets): [`mcu_raw.h`](unittest/mcu_raw.h),  [`raw.c`](unittest/raw.c)
* bitfield (C bitfields): [`mcu_bitfield.h`](unittest/mcu_bitfield.h),  [`bitfield.c`](unittest/bitfield.c)

Executable binaries to exercise these four versions can be built in the following directories. All four tests are run and their results compared; if any differ it is known that a problem exists.


#### Linux

Regbits is intended for use in standalone MCU applications. However, nothing precludes its use in other environments (and in fact it may be useful for writing device drivers, in OS kernels, etc).

The [linux](unittest/linux) version of the unittest suite is included for ease of testing under the Linux operating system without the need for embedded development testbed. It reports relative sizes of the four implementations' object code,execution speed in terms of the Linux `clock_gettime()` system call, and sizes of the individual tests. The sizes may be useful for comparing the implementations despite the radical differences between the native Linux and the (ARM) embedded compilers, and the latter (speed) for comparison despite the non-deterministic nature of timing when running under a multitasking OS.

To run the Linux unittest, type "make" in that directory. This will build and run executables for the four versions, and collate the results (see [below](#running_unittests)). The [`Makefile`](unittest/linux/Makefile) has many configuration variables that can be overridden on the `make` commandline.


#### Embedded testbed

Two sample embedded testbeds are included, one for an ARM Cortex-M0+ MCU [`lpc824`](unittest/arm/cortex_m0plus/nxp/lpc824) and one for an ARM Cortex-M3 MCU [`stm32f103xb`](unittest/arm/cortex_m3/stm/stm32f103xb). Each is of course completely specific to one particular MCU, but can be used as a template for others.

Running the unittest is broken into two steps. Typing "make" will build the four implementations' binaries, including disassembled object code (see [below](#disassembled_object_code)) and information about the resultant object code size.

The [`Makefile.arm`](unittest/arm/Makefile.arm) has many configuration variables (including ARM-specific ones) that can be overridden on the `make` commandline. Additionally, an environment variable, `GCC_ARM_ROOT`, must be set to point to the compiler's installed location.

Actually running the executables on the target embedded system is broken out as the second step, invoked by typing "make gdb", to allow the first to run without requiring attached development hardware.


#### Disassembled object code <a name="disassembled_object_code"></a>

The Makefiles (specifically the embedded Makefile, [`Makefile.arm`](unittest/arm/Makefile.arm), but also the Linux [`Makefile`](unittest/linux/Makefile)) disassemble the four implementation executables into files such as the LPC824 versions,  [`regbits.elf.dmp`](unittest/arm/cortex_m0plus/nxp/lpc824/regbits.elf.dmp), [`struct.elf.dmp`](unittest/arm/cortex_m0plus/nxp/lpc824/struct.elf.dmp), [`raw.elf.dmp`](unittest/arm/cortex_m0plus/nxp/lpc824/raw.elf.dmp), and  [`bitfield.elf.dmp`](unittest/arm/cortex_m0plus/nxp/lpc824/bitfield.elf.dmp). (The ones included in this repository were compiled "`-O3`".) These listings are intended for manual inspection to confirm that each is producing object code that will produce the same results. Suggestion: Use a good visual "diff" tool like `meld` or `kompare` to view the files side-by-side.

#### Running the unittests <a name="running_unittests"></a>

As per above, run the unittests by typing "make" in the [linux](unittest/linux) directory, or "make" followed by "make gdb" in the [embedded](unittest/arm/cortex_m0plus/nxp/lpc824) directory.

The unittests are specifically written to be run under `gdb` in order to remove any requirements for I/O in the executables, as that would influence both speed and size performance. The unittest code calls `do_test()` in each version's `main()` (see linux [`main.c`](unittest/linux/main.c) and embedded [`main.c`](unittest/arm/main.c)) to initialize pseudo-/test-registers, run a single test, and store the result.

The provided GDB scripts (linux [unittest.gdb](unittest/linux/unittest.gdb) and embedded [unittest.gdb](unittest/arm/unittest.gdb)) run the executables under `gdb`, hit a breakpoint at the end of execution, dump the test results to a file, and exit. Note that the embedded version requires an environment variable, `GDB_OPENOCD`, naming a program (typically a UNIX shell script) which runs `gdb` with appropriate connection to the target embedded system. That program (not included as it is completely development environment specific) also need to pass its commandline arguments to `gdb` as this is how the `unittest.gdb` script is loaded.

The "make" (or "make gdb") command will run the [unittest.py](unittest/unittest.py) script to collate the output files from `gdb`. If no differences between the four implementations are found it will only output information comparing their code sizes and execution speeds. Any differences will be listed with the name of the test that failed, and data from each test's saved (pseudo/test) registers. The [unittest.py](unittest/unittest.py) script also reports the code size of each of the individual unit test functions.


### Performance claims <a name="performance_claims"></a>

The four versions of the unit tests (regbits, C structs, raw C pointers and offsets, and C bitfields) were written in an attempt to make the comparisons "fair". For example, in the C struct implementation ([`struct.c`](unittest/struct.c)) it would be "natural" to pass arguments by reference separately:

        __attribute__((noinline)) void mskd_ref(
        const uint32_t    *mask,
        const uint32_t    *bits)
        {
            CHG_BITS(SERIAL2->CONFIG, mask, bits);
            CHG_BITS(SERIAL2->CONFIG, mask, bits);
        }

        __attribute__((noinline)) void call_mskd_ref()
        {
            uint32_t    mask   = SERIAL_CONFIG_DATALEN_MSK,
                        bits_a = SERIAL_CONFIG_DATALEN_16_BITS,
                        bits_b = SERIAL_CONFIG_DATALEN_32_BITS;

            mskd_ref(mask, bits_a);
            mskd_ref(mask, bits_b);

            SERIAL2->CONFIG &= ~SERIAL_CONFIG_POLARITY; // clear for periph_reg_bits_val
        }

However, since regbits passes a single object by reference:

        __attribute__((noinline)) void mskd_ref(
        const Serial::Config::mskd_t        &config)
        {
            serial2->config /=  config;
            serial2->config.ins(config);
        }

        __attribute__((noinline)) void call_mskd_ref()
        {
            Serial::Config::mskd_t    config = Serial::Config::DATALEN_16_BITS;

            mskd_ref(config);
            mskd_ref(+Serial::Config::DATALEN_32_BITS);

            serial2->config -= Serial::Config::POLARITY; // clear for periph_reg_bits_val
        }

The `struct` version was written to match that as closely as possible:

        __attribute__((noinline)) void mskd_ref(
        const uint32_t* const    mask_bits)
        {
            CHG_BITS(SERIAL2->CONFIG, mask_bits[0], mask_bits[1]);
            CHG_BITS(SERIAL2->CONFIG, mask_bits[0], mask_bits[1]);
        }



        __attribute__((noinline)) void call_mskd_ref()
        {
            uint32_t    mask_bits_a[2] = {SERIAL_CONFIG_DATALEN_MSK    ,
                                          SERIAL_CONFIG_DATALEN_16_BITS},
                        mask_bits_b[2] = {SERIAL_CONFIG_DATALEN_MSK    ,
                                          SERIAL_CONFIG_DATALEN_32_BITS};

            mskd_ref(mask_bits_a);
            mskd_ref(mask_bits_b);

            SERIAL2->CONFIG &= ~SERIAL_CONFIG_POLARITY; // clear for periph_reg_bits_val
        }


### Results

Using:

        (GNU Tools for Arm Embedded Processors 8-2018-q4-major) 8.2.1 20181213 (release) [gcc-8-branch revision 267074]

with the the options listed below, running on an NXP LCP824 ARM Cortex-M0+ and STM STM32F103XB ARM Cortex-M3 MCUs, produced the following results. Note that both were run at their default clock speeds (12 and 8 MHz respectively); however, as execution time was measured via the ARM `SysTick` counter which runs at main clock speed, the times should be independent of clock speed as long as there are no wait states for memory accesses (which should be the case as all tests were code and data in on-chip RAM).

        cortex-m0plus apcs-gnu -O2 -g3 -DGCC_ARM_BUG c++11
        bitfield.out            (too large to fit in 8K LPC824 RAM)
        raw.out                 size: 5276      time: 11086
        regbits.out             size: 5224      time: 11064
        struct.out              size: 5276      time: 11132

        cortex-m0plus apcs-gnu -O2 -g3 -DGCC_ARM_BUG c++11
        bitfield.out            (too large to fit in 8K LPC824 RAM)
        raw.out                 size: 5420      time: 11038
        regbits.out             size: 5348      time: 10972
        struct.out              size: 5416      time: 11084

        cortex-m0plus apcs-gnu -O3 -g3 -DGCC_ARM_BUG c++11
        bitfield.out            (too large to fit in 8K LPC824 RAM)
        raw.out                 size: 5488      time: 10954
        regbits.out             size: 5424      time: 10906
        struct.out              size: 5484      time: 11000

        cortex-m3 apcs-gnu -O1 -g3 -DGCC_ARM_BUG c++11
        bitfield.out            size: 6884      time: 14367
        raw.out                 size: 5092      time: 12249
        regbits.out             size: 5036      time: 12084
        struct.out              size: 5100      time: 12319

        cortex-m3 apcs-gnu -O2 -g3 -DGCC_ARM_BUG c++11
        bitfield.out            size: 6860      time: 13887
        raw.out                 size: 5312      time: 11983
        regbits.out             size: 5180      time: 11693
        struct.out              size: 5328      time: 12051

        cortex-m3 apcs-gnu -O3 -g3 -DGCC_ARM_BUG c++11
        bitfield.out            size: 7128      time: 13433
        raw.out                 size: 5356      time: 11859
        regbits.out             size: 5240      time: 11601
        struct.out              size: 5364      time: 11927

Note these overall rankings do not prove that each individual test performs in the same best-to-worst order. Also note that the constant-between-versions overhead of saving data during execution likely causes underestimation of the actual differences in speed.

To understand the exact differences, the individual `*.elf.dmp` files should be examined. However, as almost all ARM Thumb instructions execute in one cycle, comparing the relative sizes of the four implementation's individual tests is alternately a good indicator of their relative speeds. To that end, the [unittest.py](unittest/unittest.py) reports those sizes. An example output follows; the `*` indicates that the version's size is the smallest for that particular test.

        compile: cortex-m3 apcs-gnu -O2 -g3 -DGCC_ARM_BUG c++11
           regbits    struct       raw  bitfield
              24 *      24 *      24 *              .rodata
              12 *      12 *      12 *      12 *    assign_array_global
              12 *      12 *      12 *      24      assign_register_global
              24 *      24 *      24 *      40      bits_extract_eq
              24 *      24 *      24 *      40      bits_extract_ne
              16 *      16 *      16 *      92      bits_ref
              16 *      16 *      16 *      88      bits_val
              20 *      20 *      20 *      28      call_bits_ref_const
              20 *      20 *      20 *      28      call_bits_ref_global
              20 *      20 *      20 *      28      call_bits_ref_var
               8 *      20         8 *       8 *    call_bits_val_const
               8 *       8 *       8 *       8 *    call_bits_val_global
               8 *      20         8 *       8 *    call_bits_val_var
              32 *      32 *      32 *      44      call_copy_bits_ref
              16 *      16 *      16 *      28      call_copy_bits_val
              24 *      28        28        28      call_mskd_ref_const
              24 *      32        32        24 *    call_mskd_ref_global
              28        32        32        24 *    call_mskd_ref_var
               8 *      24        24        24      call_mskd_val_const
               8 *       8 *       8 *       8 *    call_mskd_val_global
               8 *      24        24        24      call_mskd_val_var
              12 *      12 *      12 *      12 *    call_periph_bits
              28 *      28 *      28 *      28 *    call_periph_bits_ref
              12 *      12 *      12 *      12 *    call_periph_bits_val
              12 *      12 *      12 *      12 *    call_periph_mskd
              16 *      40        40        28      call_periph_mskd_ref
              16        16        16        12 *    call_periph_mskd_val
              28 *      32        32        28 *    call_pos_ref
              20 *      24        24        20 *    call_pos_ref_global
              20 *      20 *      20 *      20 *    call_pos_val
               8 *       8 *       8 *       8 *    call_pos_val_global
              12 *      32        32        20      call_range_ref
               8 *       8 *       8 *       8 *    call_range_ref_port
              12        16        16         8 *    call_range_val
               8 *       8 *       8 *       8 *    call_range_val_port
              28 *      28 *      28 *      28 *    call_reg_bits_ref
              12 *      12 *      12 *      12 *    call_reg_bits_val
              16 *      40        40        28      call_reg_mskd_ref
              16        16        16        12 *    call_reg_mskd_val
              32 *      32 *      32 *      48      call_return_bits
              56 *      56 *      56 *      68      call_return_mskd
              32 *      32 *      32 *      36      call_return_periph
              32 *      32 *      32 *      40      call_return_reg
              32        32        32        20 *    call_shifted_const_ref
              12        12        12         8 *    call_shifted_const_val
              28        32        32        20 *    call_shifted_global_ref
              12        12        12         8 *    call_shifted_global_val
              32        32        32        20 *    call_shifted_var_ref
              12        12        12         8 *    call_shifted_var_val
              20 *      20 *      20 *      20 *    check_array_range_fail
              20 *      20 *      20 *      20 *    check_array_range_pass
              20 *      20 *      20 *      20 *    check_bits_range_fail
              20 *      20 *      20 *      20 *    check_bits_range_pass
              20 *      20 *      20 *      20 *    check_mskd_range_fail
              20 *      20 *      20 *      20 *    check_mskd_range_pass
              16 *      16 *      16 *      16 *    clr_singl_bits_method
              16 *      16 *      16 *      16 *    clr_singl_bits_operator
              16 *      16 *      16 *      28      clr_singl_mskd_method
              16 *      16 *      16 *      28      clr_singl_mskd_operator
              36 *      36 *      36 *      44      cmp_equ_bits
              48 *      48 *      48 *      52      cmp_equ_mskd
              36 *      36 *      36 *     120      cmp_equ_reg
              40 *      40 *      40 *      48      cmp_equ_zero
              24 *      24 *      24 *      52      cmp_neq_bits
              44 *      44 *      44 *      52      cmp_neq_mskd
              24 *      24 *      24 *     112      cmp_neq_reg
              28 *      28 *      28 *      36      cmp_neq_zero
              20 *      20 *      24        32      constexpr_bits_array
              24 *      24 *      24 *      52      copy_bits_equ
              24 *      24 *      24 *      40      copy_bits_neq
              20 *      20 *      20 *      40      copy_bits_ref
              20 *      20 *      20 *      36      copy_bits_val
              36 *      36 *      36 *      56      copy_mskd_equ
              36 *      36 *      36 *      56      copy_mskd_geq
              40 *      40 *      40 *      56      copy_mskd_gtr
              36 *      36 *      36 *      56      copy_mskd_leq
              40 *      40 *      40 *      56      copy_mskd_lss
              36 *      36 *      36 *      56      copy_mskd_neq
              36 *      36 *      36 *      56      copy_shifted
              12 *      12 *      12 *      32      equ_bits_mskd_method
              12 *      12 *      12 *      32      equ_bits_mskd_operator
              16 *      16 *      16 *      32      equ_bits_var
              12 *      12 *      12 *      32      equ_mskd_bits_method
              12 *      12 *      12 *      32      equ_mskd_bits_operator
              20 *      20 *      20 *      40      equ_mskd_var
              12 *      12 *      12 *      28      equ_multi_bits_method
              12 *      12 *      12 *      28      equ_multi_bits_operator
              16 *      16 *      16 *      32      equ_multi_mskd_method
              16 *      16 *      16 *      32      equ_multi_mskd_operator
              12 *      12 *      12 *      20      equ_singl_bits_method
              12 *      12 *      12 *      20      equ_singl_bits_operator
              12 *      12 *      12 *      24      equ_singl_mskd_method
              12 *      12 *      12 *      24      equ_singl_mskd_operator
              16 *      16 *      16 *      28      flp_singl_bits_method
              16 *      16 *      16 *      28      flp_singl_bits_operator
              16 *      16 *      16 *      28      flp_singl_mskd_method
              16 *      16 *      16 *      28      flp_singl_mskd_operator
              20 *      20 *      20 *      20 *    ins_mskd_global
              24 *      24 *      24 *      28      ins_multi_mskd_method
              24 *      24 *      24 *      28      ins_multi_mskd_operator
              20 *      20 *      20 *      20 *    ins_singl_mskd_method
              20 *      20 *      20 *      20 *    ins_singl_mskd_operator
              24 *      28        28        44      mskd_extract_eq
              32 *      36        36        72      mskd_extract_geq
              36 *      40        40        56      mskd_extract_gtr
              32 *      36        36        72      mskd_extract_leq
              36 *      40        40        56      mskd_extract_lss
              24 *      28        28        48      mskd_extract_ne
              28 *      28 *      28 *     170      mskd_ref
              20 *      20 *      20 *     166      mskd_val
              12 *      12 *      12 *      12 *    periph_bits
              12 *      12 *      12 *      16      periph_bits_ref
               8 *       8 *       8 *      16      periph_bits_val
              16        16        16        12 *    periph_mskd
              12 *      20        20        16      periph_mskd_ref
              12 *      12 *      12 *      16      periph_mskd_val
              12 *      12 *      12 *      24      pos_cmp_eq
              12 *      12 *      12 *      24      pos_cmp_ne
              32 *      32 *      32 *      32 *    pos_ref
              32 *      32 *      32 *      32 *    pos_val
              28 *      28 *      28 *      32      prescaler_high
              28 *      28 *      28 *      32      prescaler_low
              12 *      12 *      12 *      16      reg_bits_ref
               8 *       8 *       8 *      16      reg_bits_val
              56 *      56 *      56 *      80      reg_mskd_geq
              40 *      40 *      40 *      56      reg_mskd_gtr
              56 *      56 *      56 *      80      reg_mskd_leq
              40 *      40 *      40 *      56      reg_mskd_lss
              12 *      20        20        16      reg_mskd_ref
              12 *      12 *      12 *      16      reg_mskd_val
               4 *       4 *       4 *       4 *    return_bits
              12 *      12 *      12 *      12 *    return_mskd
              12 *      12 *      20        24      return_periph
              20        20        12 *      28      return_reg
            1232      1176 *    1176 *    1176 *    run
              44 *      44 *      48        60      runtime_bits_array
              20 *      28        28        20 *    runtime_range_ref
              20        20        20        16 *    runtime_range_val
              16 *      16 *      16 *      16 *    set_bits_global
              16 *      16 *      16 *      24      set_multi_bits_method
              16 *      16 *      16 *      24      set_multi_bits_operator
              16 *      16 *      16 *      16 *    set_singl_bits_method
              16 *      16 *      16 *      16 *    set_singl_bits_operator
              16 *      16 *      16 *      28      set_singl_mskd_method
              16 *      16 *      16 *      28      set_singl_mskd_operator
              28 *      28 *      28 *      32      shifted_global
              36 *      36 *      36 *      44      shifted_ref
              32 *      32 *      32 *      40      shifted_val
              12 *      12 *      12 *      12 *    zero_array
              12 *      12 *      12 *      12 *    zero_reg

Note that in almost all cases the regbits version is as small or smaller than the three C versions. The exceptions in which the C bitfield version is smallest are somewhat misleading. Most of those cases are passing values from a one function to another, and in most, the increased size of the bitfield "callee" function is larger than the decreased "caller" size. Additionally, the semantics of the bitfield version -- where separate parameters specifying which bitfield is to be operated on -- are so different from the regbits/struct/raw versions, which pass bits and bit masks, as to make comparisons somewhat meaningless. (The bitfield version was written and tested for completeness' sake.)

Cases where regbits was larger/slower than the C structs or raw C pointers/offsets implementations are tabulated as follows. The disassembled object code was closely reviewed, and some observations from that process are included below.

        compile: cortex-m0plus apcs-gnu -O1 -g3 -DGCC_ARM_BUG c++11
           regbits    struct       raw  bitfield
              20        14        14        10 *    call_shifted_global_val

*regbits compiles to a global object; struct and raw compile to compile-time constants*

              26        24 *      24 *      26      check_array_range_pass

*regbits has `nop` for function address alignment*

              44        40 *      48        56      runtime_bits_array

*regbits has extra offset calculation, reason unknown*



        compile: cortex-m0plus apcs-gnu -O2 -g3 -DGCC_ARM_BUG c++11
           regbits    struct       raw  bitfield
              44        40 *      48        52      runtime_bits_array

*as above*

        compile: cortex-m0plus apcs-gnu -O3 -g3 -DGCC_ARM_BUG c++17
           regbits    struct       raw  bitfield
              12         8 *       8 *       8 *    call_bits_val_global
              12         8 *       8 *       8 *    call_mskd_val_global
              16        12 *      12 *      12 *    call_pos_val
              12         8 *       8 *       8 *    call_pos_val_global
              12         8 *       8 *      12      call_range_val_port

*struct and raw compile single-purpose variants of callee functions, similar to C++ partial template specializations, that contain immediate values so that they don't have to be passed as parameters. unknown why regbits/C++ does not*

              44        40 *      48        52      runtime_bits_array

*as per same in -O1 and -O2 above*



        compile: cortex-m3 apcs-gnu -O1 -g3 -DGCC_ARM_BUG c++11
           regbits    struct       raw  bitfield
              36        32 *      32 *      36      call_return_periph
              36        32 *      32 *      44      call_return_reg

*struct and raw use 16-bit* `cmp` *instruction, regbits uses 32-bit* `tst.w` *and contains* `nop` *for function alignment*

              24        16        16        12 *    call_shifted_global_val

*as per Cortex-M0+, regbits compiles to a global object; struct and raw compile to compile-time constants*

        compile: cortex-m3 apcs-gnu -O2 -g3 -DGCC_ARM_BUG c++11
           regbits    struct       raw  bitfield
               (none)

        compile: cortex-m3 apcs-gnu -O3 -g3 -DGCC_ARM_BUG c++11
           regbits    struct       raw  bitfield
               8         4 *       4 *       4 *    call_mskd_val_global
              16        12 *      12 *      12 *    call_pos_val
              12         8 *       8 *       8 *    call_range_val
               8         4 *       4 *       8      call_range_val_port

*function specialization, as per Cortex-M0+ above*



Future enhancements <a name="future_enhancements"></a>
-------------------

Microcontroller registers, as described [above](#register_memory_access), are accessed as if they were memory locations, but need not behave like normal RAM/ROM/FLASH/etc memory.

Registers, or individual bits within them, can implement the following behaviors (among others):

                initial                 final
        mode    value    read   write   value

                  0       0       0       0
        normal    0       0       1       1
                  1       1       0       0
                  1       1       1       1

                  0       0       0       0
        read      0       0       1       0
        only      1       1       0       1
                  1       1       1       1

                  0       0       0       0
        set       0       0       1       1
        only      1       1       0       1
                  1       1       1       1

                  0       0       0       0
        write     0       0       1       0
        clear     1       1       0       1
                  1       1       1       0

                  0       0       0       0
        read      0       0       1       0
        clear     1       1       0       0
                  1       1       1       0

All of these behaviors are useful. For example, "read clear" is often used for interrupt registers, enabling software to query the status of an interrupt and clear it in one operation. (This does, however, make debugging difficult as querying the register in a debugger destroys its value, and subsequent reads by software will behave differently than they would otherwise. For this reason this author calls them "Schrodinger's Cat" registers.)

As another example, "set only" registers or bits are often used for setting state. They allow setting one or more bits as desired, without affecting other bits in the register. This eliminates the need for regbit's `|=` operator:

        serial2->config |= Serial::Config::ENABLE;

or the other approach's equivalent:

        SERIAL2->CONFIG |= SERIAL_CONFIG_ENABLE;

allowing the simpler and more efficient:

        serial2->config = Serial::Config::ENABLE;

        SERIAL2->CONFIG = SERIAL_CONFIG_ENABLE;

Regbits could be enhanced to allow defining the various register/bit behaviors, and use this information to chose, in a type-aware manner, the appropriate technique for accessing registers/bits, and/or disallow (compile-time error) incorrect usage such as writing to a read-only register/bit.
