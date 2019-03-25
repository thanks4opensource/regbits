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


#ifndef MCU_RAW_H
#define MCU_RAW_H

#include <stdint.h>



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

#define GPIO0           ((volatile uint32_t*)(GPIO0_BASE))
#define GPIO1           ((volatile uint32_t*)(GPIO1_BASE))

#define TIMER0          ((volatile uint32_t*)(TIMER0_BASE))
#define TIMER1          ((volatile uint32_t*)(TIMER1_BASE))
#define TIMER2          ((volatile uint32_t*)(TIMER2_BASE))
#define TIMER3          ((volatile uint32_t*)(TIMER3_BASE))

#define SERIAL0         ((volatile uint32_t*)(SERIAL0_BASE))
#define SERIAL1         ((volatile uint32_t*)(SERIAL1_BASE))
#define SERIAL2         ((volatile uint32_t*)(SERIAL2_BASE))

#define GPIO_BYTES_OFFSET           0
#define GPIO_WORDS_OFFSET           8
#define GPIO_SET_OFFSET            40
#define GPIO_CLR_OFFSET            41

#define TIMER_CONTROL_OFFSET        0
#define TIMER_PRESCALE_OFFSET       1
#define TIMER_AUTORELOAD_OFFSET     2
#define TIMER_INTERRUPTS_OFFSET     3
#define TIMER_STATUS_OFFSET         4
#define TIMER_COUNTER_OFFSET        5

#define SERIAL_CONTROL_OFFSET       0
#define SERIAL_CONFIG_OFFSET        1
#define SERIAL_INTERRUPTS_OFFSET    2
#define SERIAL_STATUS_OFFSET        3
#define SERIAL_RXBUFFER_OFFSET      4
#define SERIAL_TXBUFFER_OFFSET      5

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
#define GPIO_POS_0      0
#define GPIO_POS_1      1
#define GPIO_POS_2      2
#define GPIO_POS_3      3
#define GPIO_POS_4      4
#define GPIO_POS_5      5
#define GPIO_POS_6      6
#define GPIO_POS_7      7
#define GPIO_POS_8      8
#define GPIO_POS_9      9
#define GPIO_POS_10     10
#define GPIO_POS_11     11
#define GPIO_POS_12     12
#define GPIO_POS_13     13
#define GPIO_POS_14     14
#define GPIO_POS_15     15
#define GPIO_POS_16     16
#define GPIO_POS_17     17
#define GPIO_POS_18     18
#define GPIO_POS_19     19
#define GPIO_POS_20     20
#define GPIO_POS_21     21
#define GPIO_POS_22     22
#define GPIO_POS_23     23
#define GPIO_POS_24     24
#define GPIO_POS_25     25
#define GPIO_POS_26     26
#define GPIO_POS_27     27
#define GPIO_POS_28     28
#define GPIO_POS_29     29
#define GPIO_POS_30     30
#define GPIO_POS_31     31
#define GPIO_MSK_0      (1 << GPIO_POS_0)
#define GPIO_0          (GPIO_MSK_0     )
#define GPIO_MSK_1      (1 << GPIO_POS_1)
#define GPIO_1          (GPIO_MSK_1     )
#define GPIO_MSK_2      (1 << GPIO_POS_2)
#define GPIO_2          (GPIO_MSK_2     )
#define GPIO_MSK_3      (1 << GPIO_POS_3)
#define GPIO_3          (GPIO_MSK_3     )
#define GPIO_MSK_4      (1 << GPIO_POS_4)
#define GPIO_4          (GPIO_MSK_4     )
#define GPIO_MSK_5      (1 << GPIO_POS_5)
#define GPIO_5          (GPIO_MSK_5     )
#define GPIO_MSK_6      (1 << GPIO_POS_6)
#define GPIO_6          (GPIO_MSK_6     )
#define GPIO_MSK_7      (1 << GPIO_POS_7)
#define GPIO_7          (GPIO_MSK_7     )
#define GPIO_MSK_8      (1 << GPIO_POS_8)
#define GPIO_8          (GPIO_MSK_8     )
#define GPIO_MSK_9      (1 << GPIO_POS_9)
#define GPIO_9          (GPIO_MSK_9     )
#define GPIO_MSK_10     (1 << GPIO_POS_10)
#define GPIO_10         (GPIO_MSK_10    )
#define GPIO_MSK_11     (1 << GPIO_POS_11)
#define GPIO_11         (GPIO_MSK_11    )
#define GPIO_MSK_12     (1 << GPIO_POS_12)
#define GPIO_12         (GPIO_MSK_12    )
#define GPIO_MSK_13     (1 << GPIO_POS_13)
#define GPIO_13         (GPIO_MSK_13    )
#define GPIO_MSK_14     (1 << GPIO_POS_14)
#define GPIO_14         (GPIO_MSK_14    )
#define GPIO_MSK_15     (1 << GPIO_POS_15)
#define GPIO_15         (GPIO_MSK_15    )
#define GPIO_MSK_16     (1 << GPIO_POS_16)
#define GPIO_16         (GPIO_MSK_16    )
#define GPIO_MSK_17     (1 << GPIO_POS_17)
#define GPIO_17         (GPIO_MSK_17    )
#define GPIO_MSK_18     (1 << GPIO_POS_18)
#define GPIO_18         (GPIO_MSK_18    )
#define GPIO_MSK_19     (1 << GPIO_POS_19)
#define GPIO_19         (GPIO_MSK_19    )
#define GPIO_MSK_20     (1 << GPIO_POS_20)
#define GPIO_20         (GPIO_MSK_20    )
#define GPIO_MSK_21     (1 << GPIO_POS_21)
#define GPIO_21         (GPIO_MSK_21    )
#define GPIO_MSK_22     (1 << GPIO_POS_22)
#define GPIO_22         (GPIO_MSK_22    )
#define GPIO_MSK_23     (1 << GPIO_POS_23)
#define GPIO_23         (GPIO_MSK_23    )
#define GPIO_MSK_24     (1 << GPIO_POS_24)
#define GPIO_24         (GPIO_MSK_24    )
#define GPIO_MSK_25     (1 << GPIO_POS_25)
#define GPIO_25         (GPIO_MSK_25    )
#define GPIO_MSK_26     (1 << GPIO_POS_26)
#define GPIO_26         (GPIO_MSK_26    )
#define GPIO_MSK_27     (1 << GPIO_POS_27)
#define GPIO_27         (GPIO_MSK_27    )
#define GPIO_MSK_28     (1 << GPIO_POS_28)
#define GPIO_28         (GPIO_MSK_28    )
#define GPIO_MSK_29     (1 << GPIO_POS_29)
#define GPIO_29         (GPIO_MSK_29    )
#define GPIO_MSK_30     (1 << GPIO_POS_30)
#define GPIO_30         (GPIO_MSK_30    )
#define GPIO_MSK_31     (1 << GPIO_POS_31)
#define GPIO_31         (GPIO_MSK_31    )

#define TIMER_CONTROL_ENABLE_POS           4
#define TIMER_CONTROL_SINGLE_CYCLE_POS     5
#define TIMER_CONTROL_ARR_ENABLE_POS       6
#define TIMER_CONTROL_CLOCK_SOURCE_POS     7
#define TIMER_CONTROL_DIRECTION_POS       10
#define TIMER_CONTROL_ENABLE_MSK          (  1 << TIMER_CONTROL_ENABLE_POS       )
#define TIMER_CONTROL_SINGLE_CYCLE_MSK    (  1 << TIMER_CONTROL_SINGLE_CYCLE_POS)
#define TIMER_CONTROL_SINGLE_CYCLE        TIMER_CONTROL_SINGLE_CYCLE_MSK
#define TIMER_CONTROL_ARR_ENABLE_MSK      (  1 << TIMER_CONTROL_ARR_ENABLE_POS   )
#define TIMER_CONTROL_ARR_ENABLE          TIMER_CONTROL_ARR_ENABLE_MSK
#define TIMER_CONTROL_ENABLE              TIMER_CONTROL_ENABLE_MSK
#define TIMER_CONTROL_CLOCK_SOURCE_MSK    (0x7 << TIMER_CONTROL_CLOCK_SOURCE_POS)
#define TIMER_CONTROL_CLOCK_SOURCE_MAIN   (0x0 << TIMER_CONTROL_CLOCK_SOURCE_POS)
#define TIMER_CONTROL_CLOCK_SOURCE_PLL    (0x1 << TIMER_CONTROL_CLOCK_SOURCE_POS)
#define TIMER_CONTROL_CLOCK_SOURCE_EXTERN (0x2 << TIMER_CONTROL_CLOCK_SOURCE_POS)
#define TIMER_CONTROL_CLOCK_SOURCE_WWV    (0x3 << TIMER_CONTROL_CLOCK_SOURCE_POS)
#define TIMER_CONTROL_CLOCK_SOURCE_GPS    (0x4 << TIMER_CONTROL_CLOCK_SOURCE_POS)
#define TIMER_CONTROL_CLOCK_SOURCE_CESIUM (0x5 << TIMER_CONTROL_CLOCK_SOURCE_POS)
#define TIMER_CONTROL_DIRECTION_MSK       (  1 << TIMER_CONTROL_DIRECTION_POS)
#define TIMER_CONTROL_DIRECTION           TIMER_CONTROL_DIRECTION_MSK

#define TIMER_MAX_PRESCALER_VAL         0xff
#define TIMER_PRESCALE_PRESCALER_POS     24
#define TIMER_PRESCALE_PRESCALER_MSK    (0xff << TIMER_PRESCALE_PRESCALER_POS)

#define TIMER_MAX_AUTORELOAD_VAL            0x00ffffff
#define TIMER_AUTORELOAD_AUTORELOAD_POS       0
#define TIMER_AUTORELOAD_AUTORELOAD_MSK     (0xffffff << TIMER_AUTORELOAD_AUTORELOAD_POS)


#define TIMER_INTERRUPTS_TIMEOUT_POS         8
#define TIMER_INTERRUPTS_UNDERFLOW_POS       9
#define TIMER_INTERRUPTS_TIMEOUT_MSK         (1 << TIMER_INTERRUPTS_TIMEOUT_POS)
#define TIMER_INTERRUPTS_TIMEOUT             TIMER_INTERRUPTS_TIMEOUT_MSK
#define TIMER_INTERRUPTS_UNDERFLOW_MSK      (1 << TIMER_INTERRUPTS_UNDERFLOW_POS)
#define TIMER_INTERRUPTS_UNDERFLOW           TIMER_INTERRUPTS_UNDERFLOW_MSK

#define TIMER_STATUS_TIMEOUT_POS            16
#define TIMER_STATUS_UNDERFLOW_POS          17
#define TIMER_STATUS_TIMEOUT_MSK            (1 << TIMER_STATUS_TIMEOUT_POS)
#define TIMER_STATUS_TIMEOUT                TIMER_STATUS_TIMEOUT_MSK
#define TIMER_STATUS_UNDERFLOW_MSK          (1 << TIMER_STATUS_UNDERFLOW_POS)
#define TIMER_STATUS_UNDERFLOW              TIMER_STATUS_UNDERFLOW_MSK

#define TIMER_COUNTER_COUNT_POS      8
#define TIMER_COUNTER_COUNT_MSK     (0xffffff << TIMER_COUNTER_COUNT_POS)


#define SERIAL_MAX_PORT_NUM              31

#define SERIAL_CONTROL_ENABLE_POS         0
#define SERIAL_CONTROL_RECV_POS           1
#define SERIAL_CONTROL_XMIT_POS           2
#define SERIAL_CONTROL_ENABLE_MSK        (  1  << SERIAL_CONTROL_ENABLE_POS)
#define SERIAL_CONTROL_ENABLE           SERIAL_CONTROL_ENABLE_MSK
#define SERIAL_CONTROL_RECV_MSK          (  1  << SERIAL_CONTROL_RECV_POS)
#define SERIAL_CONTROL_RECV         SERIAL_CONTROL_RECV_MSK
#define SERIAL_CONTROL_XMIT_MSK          (  1  << SERIAL_CONTROL_XMIT_POS)
#define SERIAL_CONTROL_XMIT         SERIAL_CONTROL_XMIT_MSK

#define SERIAL_CONFIG_MODE_POS            0
#define SERIAL_CONFIG_DATALEN_POS         1
#define SERIAL_CONFIG_PARITY_POS          3
#define SERIAL_CONFIG_ENDIAN_POS          5
#define SERIAL_CONFIG_POLARITY_POS        6
#define SERIAL_CONFIG_RXPORT_POS          7
#define SERIAL_CONFIG_TXPORT_POS         12
#define SERIAL_CONFIG_MODE_MSK           (  1  << SERIAL_CONFIG_MODE_POS)
#define SERIAL_CONFIG_MODE              SERIAL_CONFIG_MODE_MSK
#define SERIAL_CONFIG_DATALEN_MSK        (0x3  << SERIAL_CONFIG_DATALEN_POS)
#define SERIAL_CONFIG_DATALEN_8_BITS     (0x0  << SERIAL_CONFIG_DATALEN_POS)
#define SERIAL_CONFIG_DATALEN_16_BITS    (0x1  << SERIAL_CONFIG_DATALEN_POS)
#define SERIAL_CONFIG_DATALEN_32_BITS    (0x2  << SERIAL_CONFIG_DATALEN_POS)
#define SERIAL_CONFIG_PARITY_MSK         (0x3  << SERIAL_CONFIG_PARITY_POS)
#define SERIAL_CONFIG_PARITY_ODD         (0x0  << SERIAL_CONFIG_PARITY_POS)
#define SERIAL_CONFIG_PARITY_EVEN        (0x1  << SERIAL_CONFIG_PARITY_POS)
#define SERIAL_CONFIG_PARITY_CRC         (0x2  << SERIAL_CONFIG_PARITY_POS)
#define SERIAL_CONFIG_ENDIAN_MSK         (  1  << SERIAL_CONFIG_ENDIAN_POS)
#define SERIAL_CONFIG_ENDIAN            SERIAL_CONFIG_ENDIAN_MSK
#define SERIAL_CONFIG_POLARITY_MSK       (  1  << SERIAL_CONFIG_POLARITY_POS)
#define SERIAL_CONFIG_POLARITY          SERIAL_CONFIG_POLARITY_MSK
#define SERIAL_CONFIG_RXPORT_MSK         (0x1f << SERIAL_CONFIG_RXPORT_POS)
#define SERIAL_CONFIG_TXPORT_MSK         (0x1f << SERIAL_CONFIG_TXPORT_POS)


#define SERIAL_INTERRUPTS_RXREADY_POS       13
#define SERIAL_INTERRUPTS_TXREADY_POS       14
#define SERIAL_INTERRUPTS_RXOVERFLOW_POS    15
#define SERIAL_INTERRUPTS_TXUNDERFLOW_POS   16
#define SERIAL_INTERRUPTS_RXREADY_MSK       ((1 << SERIAL_INTERRUPTS_RXREADY_POS)
#define SERIAL_INTERRUPTS_RXREADY           SERIAL_INTERRUPTS_RXREADY_MSK
#define SERIAL_INTERRUPTS_TXREADY_MSK       ((1 << SERIAL_INTERRUPTS_TXREADY_POS)
#define SERIAL_INTERRUPTS_TXREADY           SERIAL_INTERRUPTS_TXREADY_MSK
#define SERIAL_INTERRUPTS_RXOVERFLOW_MSK ((1 << SERIAL_INTERRUPTS_RXOVERFLOW_POS)
#define SERIAL_INTERRUPTS_RXOVERFLOW        SERIAL_INTERRUPTS_RXOVERFLOW_MSK
#define SERIAL_INTERRUPTS_TXUNDERFLOW_MSK   ((1 << SERIAL_INTERRUPTS_TXUNDERFLOW_POS)
#define SERIAL_INTERRUPTS_TXUNDERFLOW       SERIAL_INTERRUPTS_TXUNDERFLOW_MSK

#define SERIAL_STATUS_RXREADY_POS        3
#define SERIAL_STATUS_TXREADY_POS        4
#define SERIAL_STATUS_RXOVERFLOW_POS     5
#define SERIAL_STATUS_TXUNDERFLOW_POS    6
#define SERIAL_STATUS_RXREADY_MSK       (1 << SERIAL_STATUS_RXREADY_POS)
#define SERIAL_STATUS_RXREADY           SERIAL_STATUS_RXREADY_MSK
#define SERIAL_STATUS_TXREADY_MSK       (1 << SERIAL_STATUS_TXREADY_POS)
#define SERIAL_STATUS_TXREADY           SERIAL_STATUS_TXREADY_MSK
#define SERIAL_STATUS_RXOVERFLOW_MSK    (1 << SERIAL_STATUS_RXOVERFLOW_POS)
#define SERIAL_STATUS_RXOVERFLOW        SERIAL_STATUS_RXOVERFLOW_MSK
#define SERIAL_STATUS_TXUNDERFLOW_MSK   (1 << SERIAL_STATUS_TXUNDERFLOW_POS)
#define SERIAL_STATUS_TXUNDERFLOW       SERIAL_STATUS_TXUNDERFLOW_MSK

#define SERIAL_RXBUFFER_DATA_POS     0
#define SERIAL_RXBUFFER_DATA_MSK    (0xffffffff << SERIAL_RXBUFFER_DATA_POS)

#define SERIAL_TXBUFFER_DATA_POS     0
#define SERIAL_TXBUFFER_DATA_MSK    (0xffffffff << SERIAL_TXBUFFER_DATA_POS)

#endif // #ifdef MCU_RAW_H
