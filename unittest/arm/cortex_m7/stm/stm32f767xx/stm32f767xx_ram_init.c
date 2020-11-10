// regbits: C++ templates for type-safe bit manipulation
// Copyright (C) 2019,2020 Mark R. Rubin
//
// This file is part of regbits.
//
// The regbits program is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// The regbits program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// (LICENSE.txt) along with the regbits program. If not, see
// <https://www.gnu.org/licenses/gpl.html>


#include <stdint.h>

#include <stm32f767xx.h>


#if 0   // now in Makefile
#define ALL_HANDLERS_DEFAULT
#define WEAK_FUNCTIONS
#endif


void    init(void);
#ifdef ALL_HANDLERS_DEFAULT
void    Default_Handler             (void);
#else
/* ARM interrupt handlers */
void
NMI_IRQ_Handler               (void), /* -14                                   */
HardFault_IRQ_Handler         (void), /* -13 (not in stm32f767xx.h             */
MemManage_IRQ_Handler         (void), /* -12                                   */
BusFault_IRQ_Handler          (void), /* -11                                   */
UsageFault_IRQ_Handler        (void), /* -10                                   */
Reserved1_IRQ_Handler         (void), /*  -9                                   */
Reserved2_IRQ_Handler         (void), /*  -8                                   */
Reserved3_IRQ_Handler         (void), /*  -7                                   */
Reserved4_IRQ_Handler         (void), /*  -6                                   */
SVCall_IRQ_Handler            (void), /*  -5                                   */
Debug_IRQ_Handler             (void), /*  -4                                   */
Reserved5_IRQ_Handler         (void), /*  -3                                   */
PendSV_IRQ_Handler            (void), /*  -2                                   */
SysTick_IRQ_Handler           (void), /*  -1                                   */
/* STM32F767xx-specific interrupt handlers */
WWDG_IRQ_Handler              (void), /*    0  Window WatchDog                 */
PVD_IRQ_Handler               (void), /*    1  PVD through EXTI Line detection */
TAMP_STAMP_IRQ_Handler        (void), /*    2  Tamper and TimeStamp interrupts through the EXTI */
RTC_WKUP_IRQ_Handler          (void), /*    3  RTC Wakeup interrupt through the EXTI */
FLASH_IRQ_Handler             (void), /*    4  FLASH global                    */
RCC_IRQ_Handler               (void), /*    5  RCC global                      */
EXTI0_IRQ_Handler             (void), /*    6  EXTI Line0                      */
EXTI1_IRQ_Handler             (void), /*    7  EXTI Line1                      */
EXTI2_IRQ_Handler             (void), /*    8  EXTI Line2                      */
EXTI3_IRQ_Handler             (void), /*    9  EXTI Line3                      */
EXTI4_IRQ_Handler             (void), /*   10  EXTI Line4                      */
DMA1_Stream0_IRQ_Handler      (void), /*   11  DMA1 Stream 0 global            */
DMA1_Stream1_IRQ_Handler      (void), /*   12  DMA1 Stream 1 global            */
DMA1_Stream2_IRQ_Handler      (void), /*   13  DMA1 Stream 2 global            */
DMA1_Stream3_IRQ_Handler      (void), /*   14  DMA1 Stream 3 global            */
DMA1_Stream4_IRQ_Handler      (void), /*   15  DMA1 Stream 4 global            */
DMA1_Stream5_IRQ_Handler      (void), /*   16  DMA1 Stream 5 global            */
DMA1_Stream6_IRQ_Handler      (void), /*   17  DMA1 Stream 6 global            */
ADC_IRQ_Handler               (void), /*   18  ADC1 ADC2 and ADC3 global       */
CAN1_TX_IRQ_Handler           (void), /*   19  CAN1 TX                         */
CAN1_RX0_IRQ_Handler          (void), /*   20  CAN1 RX0                        */
CAN1_RX1_IRQ_Handler          (void), /*   21  CAN1 RX1                        */
CAN1_SCE_IRQ_Handler          (void), /*   22  CAN1 SCE                        */
EXTI9_5_IRQ_Handler           (void), /*   23  External Line[9:5]              */
TIM1_BRK_TIM9_IRQ_Handler     (void), /*   24  TIM1 Break interrupt and TIM9 global */
TIM1_UP_TIM10_IRQ_Handler     (void), /*   25  TIM1 Update Interrupt and TIM10 global */
TIM1_TRG_COM_TIM11_IRQ_Handler(void), /*   26  TIM1 Trigger and Commutation Interrupt and TIM11 global */
TIM1_CC_IRQ_Handler           (void), /*   27  TIM1 Capture Compare            */
TIM2_IRQ_Handler              (void), /*   28  TIM2 global                     */
TIM3_IRQ_Handler              (void), /*   29  TIM3 global                     */
TIM4_IRQ_Handler              (void), /*   30  TIM4 global                     */
I2C1_EV_IRQ_Handler           (void), /*   31  I2C1 Event                      */
I2C1_ER_IRQ_Handler           (void), /*   32  I2C1 Error                      */
I2C2_EV_IRQ_Handler           (void), /*   33  I2C2 Event                      */
I2C2_ER_IRQ_Handler           (void), /*   34  I2C2 Error                      */
SPI1_IRQ_Handler              (void), /*   35  SPI1 global                     */
SPI2_IRQ_Handler              (void), /*   36  SPI2 global                     */
USART1_IRQ_Handler            (void), /*   37  USART1 global                   */
USART2_IRQ_Handler            (void), /*   38  USART2 global                       */
USART3_IRQ_Handler            (void), /*   39  USART3 global                       */
EXTI15_10_IRQ_Handler         (void), /*   40  External Line[15:10]            */
RTC_Alarm_IRQ_Handler         (void), /*   41  RTC Alarm (A and B) through EXTI Line */
OTG_FS_WKUP_IRQ_Handler       (void), /*   42  USB OTG FS Wakeup through EXTI line */
TIM8_BRK_TIM12_IRQ_Handler    (void), /*   43    TIM8 Break Interrupt and TIM12 global */
TIM8_UP_TIM13_IRQ_Handler     (void), /*   44  TIM8 Update Interrupt and TIM13 global */
TIM8_TRG_COM_TIM14_IRQ_Handler(void), /*   45    TIM8 Trigger and Commutation Interrupt and TIM14 global */
TIM8_CC_IRQ_Handler           (void), /*   46  TIM8 Capture Compare            */
DMA1_Stream7_IRQ_Handler      (void), /*   47  DMA1 Stream7                    */
FMC_IRQ_Handler               (void), /*   48  FMC global                      */
SDMMC1_IRQ_Handler            (void), /*   49  SDMMC1 global                       */
TIM5_IRQ_Handler              (void), /*   50  TIM5 global                     */
SPI3_IRQ_Handler              (void), /*   51  SPI3 global                     */
UART4_IRQ_Handler             (void), /*   52  UART4 global                    */
UART5_IRQ_Handler             (void), /*   53  UART5 global                    */
TIM6_DAC_IRQ_Handler          (void), /*   54  TIM6 global and DAC1&2 underrun error */
TIM7_IRQ_Handler              (void), /*   55  TIM7 global                     */
DMA2_Stream0_IRQ_Handler      (void), /*   56  DMA2 Stream 0 global            */
DMA2_Stream1_IRQ_Handler      (void), /*   57  DMA2 Stream 1 global            */
DMA2_Stream2_IRQ_Handler      (void), /*   58  DMA2 Stream 2 global            */
DMA2_Stream3_IRQ_Handler      (void), /*   59  DMA2 Stream 3 global            */
DMA2_Stream4_IRQ_Handler      (void), /*   60  DMA2 Stream 4 global            */
ETH_IRQ_Handler               (void), /*   61  Ethernet global                 */
ETH_WKUP_IRQ_Handler          (void), /*   62  Ethernet Wakeup through EXTI line*/
CAN2_TX_IRQ_Handler           (void), /*   63  CAN2 TX                         */
CAN2_RX0_IRQ_Handler          (void), /*   64  CAN2 RX0                        */
CAN2_RX1_IRQ_Handler          (void), /*   65  CAN2 RX1                        */
CAN2_SCE_IRQ_Handler          (void), /*   66  CAN2 SCE                        */
OTG_FS_IRQ_Handler            (void), /*   67  USB OTG FS global               */
DMA2_Stream5_IRQ_Handler      (void), /*   68  DMA2 Stream 5 global            */
DMA2_Stream6_IRQ_Handler      (void), /*   69  DMA2 Stream 6 global            */
DMA2_Stream7_IRQ_Handler      (void), /*   70  DMA2 Stream 7 global            */
USART6_IRQ_Handler            (void), /*   71  USART6 global                   */
I2C3_EV_IRQ_Handler           (void), /*   72  I2C3 event                      */
I2C3_ER_IRQ_Handler           (void), /*   73  I2C3 error                      */
OTG_HS_EP1_OUT_IRQ_Handler    (void), /*   74  USB OTG HS End Point 1 Out global*/
OTG_HS_EP1_IN_IRQ_Handler     (void), /*   75  USB OTG HS End Point 1 In global*/
OTG_HS_WKUP_IRQ_Handler       (void), /*   76  USB OTG HS Wakeup through EXTI  */
OTG_HS_IRQ_Handler            (void), /*   77  USB OTG HS global               */
DCMI_IRQ_Handler              (void), /*   78  DCMI global                     */
RNG_IRQ_Handler               (void), /*   80  RNG global                      */
FPU_IRQ_Handler               (void), /*   81  FPU global                      */
UART7_IRQ_Handler             (void), /*   82  UART7 global                    */
UART8_IRQ_Handler             (void), /*   83  UART8 global                    */
SPI4_IRQ_Handler              (void), /*   84  SPI4 global                     */
SPI5_IRQ_Handler              (void), /*   85  SPI5 global                     */
SPI6_IRQ_Handler              (void), /*   86  SPI6 global                     */
SAI1_IRQ_Handler              (void), /*   87  SAI1 global                     */
LTDC_IRQ_Handler              (void), /*   88  LTDC global                     */
LTDC_ER_IRQ_Handler           (void), /*   89  LTDC Error global               */
DMA2D_IRQ_Handler             (void), /*   90  DMA2D global                    */
SAI2_IRQ_Handler              (void), /*   91  SAI2 global                     */
QUADSPI_IRQ_Handler           (void), /*   92  Quad SPI global                 */
LPTIM1_IRQ_Handler            (void), /*   93  LP TIM1                         */
CEC_IRQ_Handler               (void), /*   94  HDMI-CEC global                 */
I2C4_EV_IRQ_Handler           (void), /*   95  I2C4 Event                      */
I2C4_ER_IRQ_Handler           (void), /*   96  I2C4 Error                      */
SPDIF_RX_IRQ_Handler          (void), /*   97  SPDIF-RX global                 */
DFSDM1_FLT0_IRQ_Handler       (void), /*   99  DFSDM1 Filter 0 global          */
DFSDM1_FLT1_IRQ_Handler       (void), /*  100  DFSDM1 Filter 1 global          */
DFSDM1_FLT2_IRQ_Handler       (void), /*  101  DFSDM1 Filter 2 global          */
DFSDM1_FLT3_IRQ_Handler       (void), /*  102  DFSDM1 Filter 3 global          */
SDMMC2_IRQ_Handler            (void), /*  103  SDMMC2 global                   */
CAN3_TX_IRQ_Handler           (void), /*  104  CAN3 TX                         */
CAN3_RX0_IRQ_Handler          (void), /*  105  CAN3 RX0                        */
CAN3_RX1_IRQ_Handler          (void), /*  106  CAN3 RX1                        */
CAN3_SCE_IRQ_Handler          (void), /*  107  CAN3 SCE                        */
JPEG_IRQ_Handler              (void), /*  108  JPEG global                     */
MDIOS_IRQ_Handler             (void); /*  109  MDIO Slave global               */
#endif  // #ifdef ALL_HANDLERS_DEFAULT


int     main(void);

// The following are 'declared' in the linker script
extern uint8_t  BSS_START;
extern uint8_t  BSS_END;
extern uint8_t  TOP_OF_STACK;



// the section "vectors" is placed at the beginning of ram
// by the linker script
void *INTERRUPT_VECTORS[] __attribute__((section(".vectors"))) = {
    (void *)&TOP_OF_STACK,  /* Top of stack, base + 96K = 0x20018000*/
    init,                   /* Reset Handler */
#ifdef ALL_HANDLERS_DEFAULT
/* ARM interrupt handlers */
    Default_Handler,    /* NMI                              -14               */
    Default_Handler,    /* Hard Fault (not in stm32f767xx)  -13               */
    Default_Handler,    /* MemManage                        -12               */
    Default_Handler,    /* BusFault                         -11               */
    Default_Handler,    /* UsageFault                       -10               */
    Default_Handler,    /* Reserved                          -9               */
    Default_Handler,    /* Reserved                          -8               */
    Default_Handler,    /* Reserved                          -7               */
    Default_Handler,    /* Reserved                          -6               */
    Default_Handler,    /* SVCall                            -5               */
    Default_Handler,    /* Debug                             -4               */
    Default_Handler,    /* Reserved                          -3               */
    Default_Handler,    /* PendSV                            -2               */
    Default_Handler,    /* SysTick                           -1               */
/* STM32F767xx-specific interrupt handlers */
    DefaultHandler,     /* WWDG_IRQ_Handler                   0               */
    DefaultHandler,     /* PVD_IRQ_Handler                    1               */
    DefaultHandler,     /* TAMP_STAMP_IRQ_Handler             2               */
    DefaultHandler,     /* RTC_WKUP_IRQ_Handler               3               */
    DefaultHandler,     /* FLASH_IRQ_Handler                  4               */
    DefaultHandler,     /* RCC_IRQ_Handler                    5               */
    DefaultHandler,     /* EXTI0_IRQ_Handler                  6               */
    DefaultHandler,     /* EXTI1_IRQ_Handler                  7               */
    DefaultHandler,     /* EXTI2_IRQ_Handler                  8               */
    DefaultHandler,     /* EXTI3_IRQ_Handler                  9               */
    DefaultHandler,     /* EXTI4_IRQ_Handler                 10               */
    DefaultHandler,     /* DMA1_Stream0_IRQ_Handler          11               */
    DefaultHandler,     /* DMA1_Stream1_IRQ_Handler          12               */
    DefaultHandler,     /* DMA1_Stream2_IRQ_Handler          13               */
    DefaultHandler,     /* DMA1_Stream3_IRQ_Handler          14               */
    DefaultHandler,     /* DMA1_Stream4_IRQ_Handler          15               */
    DefaultHandler,     /* DMA1_Stream5_IRQ_Handler          16               */
    DefaultHandler,     /* DMA1_Stream6_IRQ_Handler          17               */
    DefaultHandler,     /* ADC_IRQ_Handler                   18               */
    DefaultHandler,     /* CAN1_TX_IRQ_Handler               19               */
    DefaultHandler,     /* CAN1_RX0_IRQ_Handler              20               */
    DefaultHandler,     /* CAN1_RX1_IRQ_Handler              21               */
    DefaultHandler,     /* CAN1_SCE_IRQ_Handler              22               */
    DefaultHandler,     /* EXTI9_5_IRQ_Handler               23               */
    DefaultHandler,     /* TIM1_BRK_TIM9_IRQ_Handler         24               */
    DefaultHandler,     /* TIM1_UP_TIM10_IRQ_Handler         25               */
    DefaultHandler,     /* TIM1_TRG_COM_TIM11_IRQ_Handler    26               */
    DefaultHandler,     /* TIM1_CC_IRQ_Handler               27               */
    DefaultHandler,     /* TIM2_IRQ_Handler                  28               */
    DefaultHandler,     /* TIM3_IRQ_Handler                  29               */
    DefaultHandler,     /* TIM4_IRQ_Handler                  30               */
    DefaultHandler,     /* I2C1_EV_IRQ_Handler               31               */
    DefaultHandler,     /* I2C1_ER_IRQ_Handler               32               */
    DefaultHandler,     /* I2C2_EV_IRQ_Handler               33               */
    DefaultHandler,     /* I2C2_ER_IRQ_Handler               34               */
    DefaultHandler,     /* SPI1_IRQ_Handler                  35               */
    DefaultHandler,     /* SPI2_IRQ_Handler                  36               */
    DefaultHandler,     /* USART1_IRQ_Handler                37               */
    DefaultHandler,     /* USART2_IRQ_Handler                38               */
    DefaultHandler,     /* USART3_IRQ_Handler                39               */
    DefaultHandler,     /* EXTI15_10_IRQ_Handler             40               */
    DefaultHandler,     /* RTC_Alarm_IRQ_Handler             41               */
    DefaultHandler,     /* OTG_FS_WKUP_IRQ_Handler           42               */
    DefaultHandler,     /* TIM8_BRK_TIM12_IRQ_Handler        43               */
    DefaultHandler,     /* TIM8_UP_TIM13_IRQ_Handler         44               */
    DefaultHandler,     /* TIM8_TRG_COM_TIM14_IRQ_Handler    45               */
    DefaultHandler,     /* TIM8_CC_IRQ_Handler               46               */
    DefaultHandler,     /* DMA1_Stream7_IRQ_Handler          47               */
    DefaultHandler,     /* FMC_IRQ_Handler                   48               */
    DefaultHandler,     /* SDMMC1_IRQ_Handler                49               */
    DefaultHandler,     /* TIM5_IRQ_Handler                  50               */
    DefaultHandler,     /* SPI3_IRQ_Handler                  51               */
    DefaultHandler,     /* UART4_IRQ_Handler                 52               */
    DefaultHandler,     /* UART5_IRQ_Handler                 53               */
    DefaultHandler,     /* TIM6_DAC_IRQ_Handler              54               */
    DefaultHandler,     /* TIM7_IRQ_Handler                  55               */
    DefaultHandler,     /* DMA2_Stream0_IRQ_Handler          56               */
    DefaultHandler,     /* DMA2_Stream1_IRQ_Handler          57               */
    DefaultHandler,     /* DMA2_Stream2_IRQ_Handler          58               */
    DefaultHandler,     /* DMA2_Stream3_IRQ_Handler          59               */
    DefaultHandler,     /* DMA2_Stream4_IRQ_Handler          60               */
    DefaultHandler,     /* ETH_IRQ_Handler                   61               */
    DefaultHandler,     /* ETH_WKUP_IRQ_Handler              62               */
    DefaultHandler,     /* CAN2_TX_IRQ_Handler               63               */
    DefaultHandler,     /* CAN2_RX0_IRQ_Handler              64               */
    DefaultHandler,     /* CAN2_RX1_IRQ_Handler              65               */
    DefaultHandler,     /* CAN2_SCE_IRQ_Handler              66               */
    DefaultHandler,     /* OTG_FS_IRQ_Handler                67               */
    DefaultHandler,     /* DMA2_Stream5_IRQ_Handler          68               */
    DefaultHandler,     /* DMA2_Stream6_IRQ_Handler          69               */
    DefaultHandler,     /* DMA2_Stream7_IRQ_Handler          70               */
    DefaultHandler,     /* USART6_IRQ_Handler                71               */
    DefaultHandler,     /* I2C3_EV_IRQ_Handler               72               */
    DefaultHandler,     /* I2C3_ER_IRQ_Handler               73               */
    DefaultHandler,     /* OTG_HS_EP1_OUT_IRQ_Handler        74               */
    DefaultHandler,     /* OTG_HS_EP1_IN_IRQ_Handler         75               */
    DefaultHandler,     /* OTG_HS_WKUP_IRQ_Handler           76               */
    DefaultHandler,     /* OTG_HS_IRQ_Handler                77               */
    DefaultHandler,     /* DCMI_IRQ_Handler                  78               */
    DefaultHandler,     /* RNG_IRQ_Handler                   80               */
    DefaultHandler,     /* FPU_IRQ_Handler                   81               */
    DefaultHandler,     /* UART7_IRQ_Handler                 82               */
    DefaultHandler,     /* UART8_IRQ_Handler                 83               */
    DefaultHandler,     /* SPI4_IRQ_Handler                  84               */
    DefaultHandler,     /* SPI5_IRQ_Handler                  85               */
    DefaultHandler,     /* SPI6_IRQ_Handler                  86               */
    DefaultHandler,     /* SAI1_IRQ_Handler                  87               */
    DefaultHandler,     /* LTDC_IRQ_Handler                  88               */
    DefaultHandler,     /* LTDC_ER_IRQ_Handler               89               */
    DefaultHandler,     /* DMA2D_IRQ_Handler                 90               */
    DefaultHandler,     /* SAI2_IRQ_Handler                  91               */
    DefaultHandler,     /* QUADSPI_IRQ_Handler               92               */
    DefaultHandler,     /* LPTIM1_IRQ_Handler                93               */
    DefaultHandler,     /* CEC_IRQ_Handler                   94               */
    DefaultHandler,     /* I2C4_EV_IRQ_Handler               95               */
    DefaultHandler,     /* I2C4_ER_IRQ_Handler               96               */
    DefaultHandler,     /* SPDIF_RX_IRQ_Handler              97               */
    DefaultHandler,     /* DFSDM1_FLT0_IRQ_Handler           99               */
    DefaultHandler,     /* DFSDM1_FLT1_IRQ_Handler          100               */
    DefaultHandler,     /* DFSDM1_FLT2_IRQ_Handler          101               */
    DefaultHandler,     /* DFSDM1_FLT3_IRQ_Handler          102               */
    DefaultHandler,     /* SDMMC2_IRQ_Handler               103               */
    DefaultHandler,     /* CAN3_TX_IRQ_Handler              104               */
    DefaultHandler,     /* CAN3_RX0_IRQ_Handler             105               */
    DefaultHandler,     /* CAN3_RX1_IRQ_Handler             106               */
    DefaultHandler,     /* CAN3_SCE_IRQ_Handler             107               */
    DefaultHandler,     /* JPEG_IRQ_Handler                 108               */
    DefaultHandler,     /* MDIOS_IRQ_Handler                109               */
#else
/* ARM interrupt handlers */
    NMI_IRQ_Handler,                /* -14  NMI                     */
    HardFault_IRQ_Handler,          /* -13  Hard                    */
    MemManage_IRQ_Handler,          /* -12  MemManage               */
    BusFault_IRQ_Handler,           /* -11  BusFault                */
    UsageFault_IRQ_Handler,         /* -10  UsageFault              */
    Reserved1_IRQ_Handler,          /*  -9  Reserved                */
    Reserved2_IRQ_Handler,          /*  -8  Reserved                */
    Reserved3_IRQ_Handler,          /*  -7  Reserved                */
    Reserved4_IRQ_Handler,          /*  -6  Reserved                */
    SVCall_IRQ_Handler,             /*  -5  SVCall                  */
    Debug_IRQ_Handler,              /*  -4  Debug                   */
    Reserved5_IRQ_Handler,          /*  -3  Reserved                */
    PendSV_IRQ_Handler,             /*  -2  PendSV                  */
    SysTick_IRQ_Handler,            /*  -1  SysTick                 */
/* STM32F767xx-specific interrupt handlers */
    WWDG_IRQ_Handler,                   /*   0  */
    PVD_IRQ_Handler,                    /*   1  */
    TAMP_STAMP_IRQ_Handler,             /*   2  */
    RTC_WKUP_IRQ_Handler,               /*   3  */
    FLASH_IRQ_Handler,                  /*   4  */
    RCC_IRQ_Handler,                    /*   5  */
    EXTI0_IRQ_Handler,                  /*   6  */
    EXTI1_IRQ_Handler,                  /*   7  */
    EXTI2_IRQ_Handler,                  /*   8  */
    EXTI3_IRQ_Handler,                  /*   9  */
    EXTI4_IRQ_Handler,                  /*  10  */
    DMA1_Stream0_IRQ_Handler,           /*  11  */
    DMA1_Stream1_IRQ_Handler,           /*  12  */
    DMA1_Stream2_IRQ_Handler,           /*  13  */
    DMA1_Stream3_IRQ_Handler,           /*  14  */
    DMA1_Stream4_IRQ_Handler,           /*  15  */
    DMA1_Stream5_IRQ_Handler,           /*  16  */
    DMA1_Stream6_IRQ_Handler,           /*  17  */
    ADC_IRQ_Handler,                    /*  18  */
    CAN1_TX_IRQ_Handler,                /*  19  */
    CAN1_RX0_IRQ_Handler,               /*  20  */
    CAN1_RX1_IRQ_Handler,               /*  21  */
    CAN1_SCE_IRQ_Handler,               /*  22  */
    EXTI9_5_IRQ_Handler,                /*  23  */
    TIM1_BRK_TIM9_IRQ_Handler,          /*  24  */
    TIM1_UP_TIM10_IRQ_Handler,          /*  25  */
    TIM1_TRG_COM_TIM11_IRQ_Handler,     /*  26  */
    TIM1_CC_IRQ_Handler,                /*  27  */
    TIM2_IRQ_Handler,                   /*  28  */
    TIM3_IRQ_Handler,                   /*  29  */
    TIM4_IRQ_Handler,                   /*  30  */
    I2C1_EV_IRQ_Handler,                /*  31  */
    I2C1_ER_IRQ_Handler,                /*  32  */
    I2C2_EV_IRQ_Handler,                /*  33  */
    I2C2_ER_IRQ_Handler,                /*  34  */
    SPI1_IRQ_Handler,                   /*  35  */
    SPI2_IRQ_Handler,                   /*  36  */
    USART1_IRQ_Handler,                 /*  37  */
    USART2_IRQ_Handler,                 /*  38  */
    USART3_IRQ_Handler,                 /*  39  */
    EXTI15_10_IRQ_Handler,              /*  40  */
    RTC_Alarm_IRQ_Handler,              /*  41  */
    OTG_FS_WKUP_IRQ_Handler,            /*  42  */
    TIM8_BRK_TIM12_IRQ_Handler,         /*  43  */
    TIM8_UP_TIM13_IRQ_Handler,          /*  44  */
    TIM8_TRG_COM_TIM14_IRQ_Handler,     /*  45  */
    TIM8_CC_IRQ_Handler,                /*  46  */
    DMA1_Stream7_IRQ_Handler,           /*  47  */
    FMC_IRQ_Handler,                    /*  48  */
    SDMMC1_IRQ_Handler,                 /*  49  */
    TIM5_IRQ_Handler,                   /*  50  */
    SPI3_IRQ_Handler,                   /*  51  */
    UART4_IRQ_Handler,                  /*  52  */
    UART5_IRQ_Handler,                  /*  53  */
    TIM6_DAC_IRQ_Handler,               /*  54  */
    TIM7_IRQ_Handler,                   /*  55  */
    DMA2_Stream0_IRQ_Handler,           /*  56  */
    DMA2_Stream1_IRQ_Handler,           /*  57  */
    DMA2_Stream2_IRQ_Handler,           /*  58  */
    DMA2_Stream3_IRQ_Handler,           /*  59  */
    DMA2_Stream4_IRQ_Handler,           /*  60  */
    ETH_IRQ_Handler,                    /*  61  */
    ETH_WKUP_IRQ_Handler,               /*  62  */
    CAN2_TX_IRQ_Handler,                /*  63  */
    CAN2_RX0_IRQ_Handler,               /*  64  */
    CAN2_RX1_IRQ_Handler,               /*  65  */
    CAN2_SCE_IRQ_Handler,               /*  66  */
    OTG_FS_IRQ_Handler,                 /*  67  */
    DMA2_Stream5_IRQ_Handler,           /*  68  */
    DMA2_Stream6_IRQ_Handler,           /*  69  */
    DMA2_Stream7_IRQ_Handler,           /*  70  */
    USART6_IRQ_Handler,                 /*  71  */
    I2C3_EV_IRQ_Handler,                /*  72  */
    I2C3_ER_IRQ_Handler,                /*  73  */
    OTG_HS_EP1_OUT_IRQ_Handler,         /*  74  */
    OTG_HS_EP1_IN_IRQ_Handler,          /*  75  */
    OTG_HS_WKUP_IRQ_Handler,            /*  76  */
    OTG_HS_IRQ_Handler,                 /*  77  */
    DCMI_IRQ_Handler,                   /*  78  */
    RNG_IRQ_Handler,                    /*  80  */
    FPU_IRQ_Handler,                    /*  81  */
    UART7_IRQ_Handler,                  /*  82  */
    UART8_IRQ_Handler,                  /*  83  */
    SPI4_IRQ_Handler,                   /*  84  */
    SPI5_IRQ_Handler,                   /*  85  */
    SPI6_IRQ_Handler,                   /*  86  */
    SAI1_IRQ_Handler,                   /*  87  */
    LTDC_IRQ_Handler,                   /*  88  */
    LTDC_ER_IRQ_Handler,                /*  89  */
    DMA2D_IRQ_Handler,                  /*  90  */
    SAI2_IRQ_Handler,                   /*  91  */
    QUADSPI_IRQ_Handler,                /*  92  */
    LPTIM1_IRQ_Handler,                 /*  93  */
    CEC_IRQ_Handler,                    /*  94  */
    I2C4_EV_IRQ_Handler,                /*  95  */
    I2C4_ER_IRQ_Handler,                /*  96  */
    SPDIF_RX_IRQ_Handler,               /*  97  */
    DFSDM1_FLT0_IRQ_Handler,            /*  99  */
    DFSDM1_FLT1_IRQ_Handler,            /* 100  */
    DFSDM1_FLT2_IRQ_Handler,            /* 101  */
    DFSDM1_FLT3_IRQ_Handler,            /* 102  */
    SDMMC2_IRQ_Handler,                 /* 103  */
    CAN3_TX_IRQ_Handler,                /* 104  */
    CAN3_RX0_IRQ_Handler,               /* 105  */
    CAN3_RX1_IRQ_Handler,               /* 106  */
    CAN3_SCE_IRQ_Handler,               /* 107  */
    JPEG_IRQ_Handler,                   /* 108  */
    MDIOS_IRQ_Handler,                  /* 109  */
#endif
};



void init()
{
    uint8_t     *dest;
    uint32_t     len;

    // zero out the uninitialized global/static variables
    dest = &BSS_START;
    len  = &BSS_END - &BSS_START;
    while (len--)
        *dest++=0;

    // set CPU's vector table address
    SCB->VTOR = (uint32_t)INTERRUPT_VECTORS;

    // start program
    main();
}



#ifdef WEAK_FUNCTIONS
#define MAYBE_WEAK __attribute__((weak))
#else
#define MAYBE_WEAK
#endif


#ifdef ALL_HANDLERS_DEFAULT
MAYBE_WEAK void Default_Handler()
{
    while(1);
}
#else
/* ARM interrupt handlers */
MAYBE_WEAK void NMI_IRQ_Handler                 () { while (1); }   /* -14  */
MAYBE_WEAK void HardFault_IRQ_Handler           () { while (1); }   /* -13  */
MAYBE_WEAK void MemManage_IRQ_Handler           () { while (1); }   /* -12  */
MAYBE_WEAK void BusFault_IRQ_Handler            () { while (1); }   /* -11  */
MAYBE_WEAK void UsageFault_IRQ_Handler          () { while (1); }   /* -10  */
MAYBE_WEAK void Reserved1_IRQ_Handler           () { while (1); }   /*  -9  */
MAYBE_WEAK void Reserved2_IRQ_Handler           () { while (1); }   /*  -8  */
MAYBE_WEAK void Reserved3_IRQ_Handler           () { while (1); }   /*  -7  */
MAYBE_WEAK void Reserved4_IRQ_Handler           () { while (1); }   /*  -6  */
MAYBE_WEAK void SVCall_IRQ_Handler              () { while (1); }   /*  -5  */
MAYBE_WEAK void Debug_IRQ_Handler               () { while (1); }   /*  -4  */
MAYBE_WEAK void Reserved5_IRQ_Handler           () { while (1); }   /*  -3  */
MAYBE_WEAK void PendSV_IRQ_Handler              () { while (1); }   /*  -2  */
MAYBE_WEAK void SysTick_IRQ_Handler             () { while (1); }   /*  -1  */
/* STM32F767xx-specific interrupt handlers */
MAYBE_WEAK void WWDG_IRQ_Handler                () { while (1); }   /*   0  */
MAYBE_WEAK void PVD_IRQ_Handler                 () { while (1); }   /*   1  */
MAYBE_WEAK void TAMP_STAMP_IRQ_Handler          () { while (1); }   /*   2  */
MAYBE_WEAK void RTC_WKUP_IRQ_Handler            () { while (1); }   /*   3  */
MAYBE_WEAK void FLASH_IRQ_Handler               () { while (1); }   /*   4  */
MAYBE_WEAK void RCC_IRQ_Handler                 () { while (1); }   /*   5  */
MAYBE_WEAK void EXTI0_IRQ_Handler               () { while (1); }   /*   6  */
MAYBE_WEAK void EXTI1_IRQ_Handler               () { while (1); }   /*   7  */
MAYBE_WEAK void EXTI2_IRQ_Handler               () { while (1); }   /*   8  */
MAYBE_WEAK void EXTI3_IRQ_Handler               () { while (1); }   /*   9  */
MAYBE_WEAK void EXTI4_IRQ_Handler               () { while (1); }   /*  10  */
MAYBE_WEAK void DMA1_Stream0_IRQ_Handler        () { while (1); }   /*  11  */
MAYBE_WEAK void DMA1_Stream1_IRQ_Handler        () { while (1); }   /*  12  */
MAYBE_WEAK void DMA1_Stream2_IRQ_Handler        () { while (1); }   /*  13  */
MAYBE_WEAK void DMA1_Stream3_IRQ_Handler        () { while (1); }   /*  14  */
MAYBE_WEAK void DMA1_Stream4_IRQ_Handler        () { while (1); }   /*  15  */
MAYBE_WEAK void DMA1_Stream5_IRQ_Handler        () { while (1); }   /*  16  */
MAYBE_WEAK void DMA1_Stream6_IRQ_Handler        () { while (1); }   /*  17  */
MAYBE_WEAK void ADC_IRQ_Handler                 () { while (1); }   /*  18  */
MAYBE_WEAK void CAN1_TX_IRQ_Handler             () { while (1); }   /*  19  */
MAYBE_WEAK void CAN1_RX0_IRQ_Handler            () { while (1); }   /*  20  */
MAYBE_WEAK void CAN1_RX1_IRQ_Handler            () { while (1); }   /*  21  */
MAYBE_WEAK void CAN1_SCE_IRQ_Handler            () { while (1); }   /*  22  */
MAYBE_WEAK void EXTI9_5_IRQ_Handler             () { while (1); }   /*  23  */
MAYBE_WEAK void TIM1_BRK_TIM9_IRQ_Handler       () { while (1); }   /*  24  */
MAYBE_WEAK void TIM1_UP_TIM10_IRQ_Handler       () { while (1); }   /*  25  */
MAYBE_WEAK void TIM1_TRG_COM_TIM11_IRQ_Handler  () { while (1); }   /*  26  */
MAYBE_WEAK void TIM1_CC_IRQ_Handler             () { while (1); }   /*  27  */
MAYBE_WEAK void TIM2_IRQ_Handler                () { while (1); }   /*  28  */
MAYBE_WEAK void TIM3_IRQ_Handler                () { while (1); }   /*  29  */
MAYBE_WEAK void TIM4_IRQ_Handler                () { while (1); }   /*  30  */
MAYBE_WEAK void I2C1_EV_IRQ_Handler             () { while (1); }   /*  31  */
MAYBE_WEAK void I2C1_ER_IRQ_Handler             () { while (1); }   /*  32  */
MAYBE_WEAK void I2C2_EV_IRQ_Handler             () { while (1); }   /*  33  */
MAYBE_WEAK void I2C2_ER_IRQ_Handler             () { while (1); }   /*  34  */
MAYBE_WEAK void SPI1_IRQ_Handler                () { while (1); }   /*  35  */
MAYBE_WEAK void SPI2_IRQ_Handler                () { while (1); }   /*  36  */
MAYBE_WEAK void USART1_IRQ_Handler              () { while (1); }   /*  37  */
MAYBE_WEAK void USART2_IRQ_Handler              () { while (1); }   /*  38  */
MAYBE_WEAK void USART3_IRQ_Handler              () { while (1); }   /*  39  */
MAYBE_WEAK void EXTI15_10_IRQ_Handler           () { while (1); }   /*  40  */
MAYBE_WEAK void RTC_Alarm_IRQ_Handler           () { while (1); }   /*  41  */
MAYBE_WEAK void OTG_FS_WKUP_IRQ_Handler         () { while (1); }   /*  42  */
MAYBE_WEAK void TIM8_BRK_TIM12_IRQ_Handler      () { while (1); }   /*  43  */
MAYBE_WEAK void TIM8_UP_TIM13_IRQ_Handler       () { while (1); }   /*  44  */
MAYBE_WEAK void TIM8_TRG_COM_TIM14_IRQ_Handler  () { while (1); }   /*  45  */
MAYBE_WEAK void TIM8_CC_IRQ_Handler             () { while (1); }   /*  46  */
MAYBE_WEAK void DMA1_Stream7_IRQ_Handler        () { while (1); }   /*  47  */
MAYBE_WEAK void FMC_IRQ_Handler                 () { while (1); }   /*  48  */
MAYBE_WEAK void SDMMC1_IRQ_Handler              () { while (1); }   /*  49  */
MAYBE_WEAK void TIM5_IRQ_Handler                () { while (1); }   /*  50  */
MAYBE_WEAK void SPI3_IRQ_Handler                () { while (1); }   /*  51  */
MAYBE_WEAK void UART4_IRQ_Handler               () { while (1); }   /*  52  */
MAYBE_WEAK void UART5_IRQ_Handler               () { while (1); }   /*  53  */
MAYBE_WEAK void TIM6_DAC_IRQ_Handler            () { while (1); }   /*  54  */
MAYBE_WEAK void TIM7_IRQ_Handler                () { while (1); }   /*  55  */
MAYBE_WEAK void DMA2_Stream0_IRQ_Handler        () { while (1); }   /*  56  */
MAYBE_WEAK void DMA2_Stream1_IRQ_Handler        () { while (1); }   /*  57  */
MAYBE_WEAK void DMA2_Stream2_IRQ_Handler        () { while (1); }   /*  58  */
MAYBE_WEAK void DMA2_Stream3_IRQ_Handler        () { while (1); }   /*  59  */
MAYBE_WEAK void DMA2_Stream4_IRQ_Handler        () { while (1); }   /*  60  */
MAYBE_WEAK void ETH_IRQ_Handler                 () { while (1); }   /*  61  */
MAYBE_WEAK void ETH_WKUP_IRQ_Handler            () { while (1); }   /*  62  */
MAYBE_WEAK void CAN2_TX_IRQ_Handler             () { while (1); }   /*  63  */
MAYBE_WEAK void CAN2_RX0_IRQ_Handler            () { while (1); }   /*  64  */
MAYBE_WEAK void CAN2_RX1_IRQ_Handler            () { while (1); }   /*  65  */
MAYBE_WEAK void CAN2_SCE_IRQ_Handler            () { while (1); }   /*  66  */
MAYBE_WEAK void OTG_FS_IRQ_Handler              () { while (1); }   /*  67  */
MAYBE_WEAK void DMA2_Stream5_IRQ_Handler        () { while (1); }   /*  68  */
MAYBE_WEAK void DMA2_Stream6_IRQ_Handler        () { while (1); }   /*  69  */
MAYBE_WEAK void DMA2_Stream7_IRQ_Handler        () { while (1); }   /*  70  */
MAYBE_WEAK void USART6_IRQ_Handler              () { while (1); }   /*  71  */
MAYBE_WEAK void I2C3_EV_IRQ_Handler             () { while (1); }   /*  72  */
MAYBE_WEAK void I2C3_ER_IRQ_Handler             () { while (1); }   /*  73  */
MAYBE_WEAK void OTG_HS_EP1_OUT_IRQ_Handler      () { while (1); }   /*  74  */
MAYBE_WEAK void OTG_HS_EP1_IN_IRQ_Handler       () { while (1); }   /*  75  */
MAYBE_WEAK void OTG_HS_WKUP_IRQ_Handler         () { while (1); }   /*  76  */
MAYBE_WEAK void OTG_HS_IRQ_Handler              () { while (1); }   /*  77  */
MAYBE_WEAK void DCMI_IRQ_Handler                () { while (1); }   /*  78  */
MAYBE_WEAK void RNG_IRQ_Handler                 () { while (1); }   /*  80  */
MAYBE_WEAK void FPU_IRQ_Handler                 () { while (1); }   /*  81  */
MAYBE_WEAK void UART7_IRQ_Handler               () { while (1); }   /*  82  */
MAYBE_WEAK void UART8_IRQ_Handler               () { while (1); }   /*  83  */
MAYBE_WEAK void SPI4_IRQ_Handler                () { while (1); }   /*  84  */
MAYBE_WEAK void SPI5_IRQ_Handler                () { while (1); }   /*  85  */
MAYBE_WEAK void SPI6_IRQ_Handler                () { while (1); }   /*  86  */
MAYBE_WEAK void SAI1_IRQ_Handler                () { while (1); }   /*  87  */
MAYBE_WEAK void LTDC_IRQ_Handler                () { while (1); }   /*  88  */
MAYBE_WEAK void LTDC_ER_IRQ_Handler             () { while (1); }   /*  89  */
MAYBE_WEAK void DMA2D_IRQ_Handler               () { while (1); }   /*  90  */
MAYBE_WEAK void SAI2_IRQ_Handler                () { while (1); }   /*  91  */
MAYBE_WEAK void QUADSPI_IRQ_Handler             () { while (1); }   /*  92  */
MAYBE_WEAK void LPTIM1_IRQ_Handler              () { while (1); }   /*  93  */
MAYBE_WEAK void CEC_IRQ_Handler                 () { while (1); }   /*  94  */
MAYBE_WEAK void I2C4_EV_IRQ_Handler             () { while (1); }   /*  95  */
MAYBE_WEAK void I2C4_ER_IRQ_Handler             () { while (1); }   /*  96  */
MAYBE_WEAK void SPDIF_RX_IRQ_Handler            () { while (1); }   /*  97  */
MAYBE_WEAK void DFSDM1_FLT0_IRQ_Handler         () { while (1); }   /*  99  */
MAYBE_WEAK void DFSDM1_FLT1_IRQ_Handler         () { while (1); }   /* 100  */
MAYBE_WEAK void DFSDM1_FLT2_IRQ_Handler         () { while (1); }   /* 101  */
MAYBE_WEAK void DFSDM1_FLT3_IRQ_Handler         () { while (1); }   /* 102  */
MAYBE_WEAK void SDMMC2_IRQ_Handler              () { while (1); }   /* 103  */
MAYBE_WEAK void CAN3_TX_IRQ_Handler             () { while (1); }   /* 104  */
MAYBE_WEAK void CAN3_RX0_IRQ_Handler            () { while (1); }   /* 105  */
MAYBE_WEAK void CAN3_RX1_IRQ_Handler            () { while (1); }   /* 106  */
MAYBE_WEAK void CAN3_SCE_IRQ_Handler            () { while (1); }   /* 107  */
MAYBE_WEAK void JPEG_IRQ_Handler                () { while (1); }   /* 108  */
MAYBE_WEAK void MDIOS_IRQ_Handler               () { while (1); }   /* 109  */
#endif  // #ifdef ALL_HANDLERS_DEFAULT
