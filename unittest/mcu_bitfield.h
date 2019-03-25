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


#ifndef MCU_BITFIELD_H
#define MCU_BITFIELD_H

#include <stdint.h>

enum GPIO_PORT {
    PORT0,
    PORT1,
    PORT2,
    PORT3,
    PORT4,
    PORT5,
    PORT6,
    PORT7,
    PORT8,
    PORT9,
    PORT10,
    PORT11,
    PORT12,
    PORT13,
    PORT14,
    PORT15,
    PORT16,
    PORT17,
    PORT18,
    PORT19,
    PORT20,
    PORT21,
    PORT22,
    PORT23,
    PORT24,
    PORT25,
    PORT26,
    PORT27,
    PORT28,
    PORT29,
    PORT30,
    PORT31,
};

enum TIMER_CONTROL {
    TIMER_ENABLE,
    SINGLE_CYCLE,
    ARR_ENABLE,
    CLOCK_SOURCE,
    DIRECTION,
};

enum TIMER_INTERRUPTS_STATUS {
    TIMEOUT,
    UNDERFLOW,
};

enum SERIAL_CONTROL {
    SERIAL_ENABLE,
    RECV,
    XMIT,
};

enum SERIAL_CONFIG {
    MODE,
    DATALEN,
    PARITY,
    ENDIAN,
    POLARITY,
    RXPORT,
    TXPORT,
};

enum SERIAL_INTERRUPTS_STATUS {
    RXREADY,
    TXREADY,
    RXOVERFLOW,
    TXUNDERFLOW ,
};



typedef struct gpio {
    volatile uint8_t    bytes[23],
                        rsrv0[ 9];
    volatile uint32_t   words[23],
                        rsrv1[ 9];
    union SET_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned    port0  : 1,
                        port1  : 1,
                        port2  : 1,
                        port3  : 1,
                        port4  : 1,
                        port5  : 1,
                        port6  : 1,
                        port7  : 1,
                        port8  : 1,
                        port9  : 1,
                        port10  : 1,
                        port11  : 1,
                        port12  : 1,
                        port13  : 1,
                        port14  : 1,
                        port15  : 1,
                        port16  : 1,
                        port17  : 1,
                        port18  : 1,
                        port19  : 1,
                        port20  : 1,
                        port21  : 1,
                        port22  : 1,
                        port23  : 1,
                        port24  : 1,
                        port25  : 1,
                        port26  : 1,
                        port27  : 1,
                        port28  : 1,
                        port29  : 1,
                        port30  : 1,
                        port31  : 1;
        };
    } set;
    union CLR_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned    port0  : 1,
                        port1  : 1,
                        port2  : 1,
                        port3  : 1,
                        port4  : 1,
                        port5  : 1,
                        port6  : 1,
                        port7  : 1,
                        port8  : 1,
                        port9  : 1,
                        port10  : 1,
                        port11  : 1,
                        port12  : 1,
                        port13  : 1,
                        port14  : 1,
                        port15  : 1,
                        port16  : 1,
                        port17  : 1,
                        port18  : 1,
                        port19  : 1,
                        port20  : 1,
                        port21  : 1,
                        port22  : 1,
                        port23  : 1,
                        port24  : 1,
                        port25  : 1,
                        port26  : 1,
                        port27  : 1,
                        port28  : 1,
                        port29  : 1,
                        port30  : 1,
                        port31  : 1;
        };
    } clr;
} gpio_t;
#ifdef __GNUC__
_Static_assert(sizeof(gpio_t) == 168, "sizeof(gpio_t) != 168");
#endif

typedef struct timer {
    union TIMER_CONTROL_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned                    :  3,
                        enable          :  1,
                        single_cycle    :  1,
                        arr_enable      :  1,
                        clock_source    :  3,
                        direction       :  1,
                                        : 22;
        };
    } control;

    union PRESCALE_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned                    : 24,
                        prescaler       :  8;
        };
    } prescale;

    union AUTORELOAD_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned    autoreload  : 24,
                                    :  8;
        };
    } autoreload;

    union TIMER_INTERRUPTS_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned                :  8,
                        timeout     :  1,
                        underflow   :  1,
                                    : 20;
        };
    } interrupts;

    union TIMER_STATUS_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned                    : 16,
                        timeout         :  1,
                        underflow       :  1,
                                        : 14;
        };
    } status;

    union COUNTER_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned                    :  8,
                        count           : 24;
        };
    } counter;
} timer_t;
#ifdef __GNUC__
_Static_assert(sizeof(timer_t) == 24, "sizeof(timer_t) != 24");
#endif

typedef struct serial {
    union SERIAL_CONTROL_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned    enable          :  1,
                        recv            :  1,
                        xmit            :  1,
                                        : 29;
        };
    } control;

    union CONFIG_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned    mode            :  1,
                        datalen         :  2,
                        parity          :  2,
                        endian          :  1,
                        polarity        :  1,
                        rxport          :  5,
                        txport          :  5,
                                        : 15;
        };
    } config;

    union SERIAL_INTERRUPTS_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned                    : 13,
                        rxready         :  1,
                        txready         :  1,
                        rxoverflow      :  1,
                        txunderflow     :  1,
                                        : 15;
        };
    } interrupts;

    union SERIAL_STATUS_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned                    :  3,
                        rxready         :  1,
                        txready         :  1,
                        rxoverflow      :  1,
                        txunderflow     :  1,
                                        : 25;
        };
    } status;

    union RXBUFFER_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned    data            : 32;
        };
    } rxbuffer;

    union TXBUFFER_T {
        volatile uint32_t   word;
        volatile struct {
            unsigned    data            : 32;
        };
    } txbuffer;
} serial_t;
#ifdef __GNUC__
_Static_assert(sizeof(serial_t) == 24, "sizeof(serial_t) != 24");
#endif



#ifndef PERIPH_BASE
#error Must define PERIPH_BASE via -DPERIPH_BASE=xxxx on commandline
#endif

#define GPIO_BASE       ((PERIPH_BASE) + 0x00000000)
#define TIMER_BASE      ((PERIPH_BASE) + 0x00000200)
#define SERIAL_BASE     ((PERIPH_BASE) + 0x00000280)

#define GPIO0_BASE      ((GPIO_BASE)   + 0x00000000)
#define GPIO1_BASE      ((GPIO_BASE)   + 0x00000100)

#define TIMER0_BASE     ((TIMER_BASE)  + 0x00000000)
#define TIMER1_BASE     ((TIMER_BASE)  + 0x00000020)
#define TIMER2_BASE     ((TIMER_BASE)  + 0x00000040)
#define TIMER3_BASE     ((TIMER_BASE)  + 0x00000060)

#define SERIAL0_BASE    ((SERIAL_BASE) + 0x00000000)
#define SERIAL1_BASE    ((SERIAL_BASE) + 0x00000020)
#define SERIAL2_BASE    ((SERIAL_BASE) + 0x00000040)

static gpio_t* const    GPIO0  = (gpio_t*)(GPIO0_BASE);
static gpio_t* const    GPIO1  = (gpio_t*)(GPIO1_BASE);

static timer_t* const   TIMER0 = (timer_t*)(TIMER0_BASE);
static timer_t* const   TIMER1 = (timer_t*)(TIMER1_BASE);
static timer_t* const   TIMER2 = (timer_t*)(TIMER2_BASE);
static timer_t* const   TIMER3 = (timer_t*)(TIMER3_BASE);

static serial_t* const  SERIAL0 = (serial_t*)(SERIAL0_BASE);
static serial_t* const  SERIAL1 = (serial_t*)(SERIAL1_BASE);
static serial_t* const  SERIAL2 = (serial_t*)(SERIAL2_BASE);


#define GPIO_MAX_PORT_NUM 22
#define GPIO_NDX_0      0
#define GPIO_NDX_1      1
#define GPIO_NDX_2      2
#define GPIO_NDX_3      3
#define GPIO_NDX_4      4
#define GPIO_NDX_5      5
#define GPIO_NDX_6      6
#define GPIO_NDX_7      7
#define GPIO_NDX_8      8
#define GPIO_NDX_9      9
#define GPIO_NDX_10     10
#define GPIO_NDX_11     11
#define GPIO_NDX_12     12
#define GPIO_NDX_13     13
#define GPIO_NDX_14     14
#define GPIO_NDX_15     15
#define GPIO_NDX_16     16
#define GPIO_NDX_17     17
#define GPIO_NDX_18     18
#define GPIO_NDX_19     19
#define GPIO_NDX_20     20
#define GPIO_NDX_21     21
#define GPIO_NDX_22     22
#define GPIO_NDX_23     23
#define GPIO_NDX_24     24
#define GPIO_NDX_25     25
#define GPIO_NDX_26     26
#define GPIO_NDX_27     27
#define GPIO_NDX_28     28
#define GPIO_NDX_29     29
#define GPIO_NDX_30     30
#define GPIO_NDX_31     31

#define TIMER_CONTROL_SINGLE_CYCLE          1
#define TIMER_CONTROL_ENABLE                1
#define TIMER_CONTROL_CLOCK_SOURCE_MAIN     0x0
#define TIMER_CONTROL_CLOCK_SOURCE_PLL      0x1
#define TIMER_CONTROL_CLOCK_SOURCE_EXTERN   0x2
#define TIMER_CONTROL_CLOCK_SOURCE_WWV      0x3
#define TIMER_CONTROL_CLOCK_SOURCE_GPS      0x4
#define TIMER_CONTROL_CLOCK_SOURCE_CESIUM   0x5
#define TIMER_CONTROL_DIRECTION             1

#define TIMER_MAX_PRESCALER_VAL             0xff

#define TIMER_MAX_AUTORELOAD_VAL            0x00ffffff


#define TIMER_INTERRUPTS_TIMEOUT            1
#define TIMER_INTERRUPTS_UNDERFLOW          1

#define TIMER_STATUS_TIMEOUT                1
#define TIMER_STATUS_UNDERFLOW              1


#define SERIAL_MAX_PORT_NUM                 31

#define SERIAL_CONTROL_ENABLE               1
#define SERIAL_CONTROL_RECV                 1
#define SERIAL_CONTROL_XMIT                 1

#define SERIAL_CONFIG_MODE                  1
#define SERIAL_CONFIG_DATALEN_8_BITS        0x0
#define SERIAL_CONFIG_DATALEN_16_BITS       0x1
#define SERIAL_CONFIG_DATALEN_32_BITS       0x2
#define SERIAL_CONFIG_PARITY_ODD            0x0
#define SERIAL_CONFIG_PARITY_EVEN           0x1
#define SERIAL_CONFIG_PARITY_CRC            0x2
#define SERIAL_CONFIG_ENDIAN                1
#define SERIAL_CONFIG_POLARITY              1

#define SERIAL_INTERRUPTS_RXREADY           1
#define SERIAL_INTERRUPTS_TXREADY           1
#define SERIAL_INTERRUPTS_RXOVERFLOW        1
#define SERIAL_INTERRUPTS_TXUNDERFLOW       1

#define SERIAL_STATUS_RXREADY               1
#define SERIAL_STATUS_TXREADY               1
#define SERIAL_STATUS_RXOVERFLOW            1
#define SERIAL_STATUS_TXUNDERFLOW           1

#endif // #ifdef MCU_BITFIELD_H
