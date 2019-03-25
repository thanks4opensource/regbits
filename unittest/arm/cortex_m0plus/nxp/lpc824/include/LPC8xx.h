/****************************************************************************
 *   $Id:: LPC8xx.h 6437 2012-10-31 11:06:06Z dep00694                     $
 *   Project: NXP LPC8xx software example  
 *
 *   Description:
 *     CMSIS Cortex-M0+ Core Peripheral Access Layer Header File for 
 *     NXP LPC800 Device Series 
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.

 * Permission to use, copy, modify, and distribute this software and its 
 * documentation is hereby granted, under NXP Semiconductors' 
 * relevant copyright in the software, without fee, provided that it 
 * is used in conjunction with NXP Semiconductors microcontrollers. This 
 * copyright, permission, and disclaimer notice must appear in all copies of 
 * this code.
 *
 * modified by ARM 02.09.2019
****************************************************************************/
#ifndef __LPC8xx_H__
#define __LPC8xx_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup LPC8xx_Definitions LPC8xx Definitions
  This file defines all structures and symbols for LPC8xx:
    - Registers and bitfields
    - peripheral base address
    - PIO definitions
  @{
*/


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup LPC8xx_CMSIS LPC8xx CMSIS Definitions
  Configuration of the Cortex-M0+ Processor and Core Peripherals
  @{
*/

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************************/
  Reset_IRQn                    = -15,    /*!< 1 Reset Vector, invoked on Power up and warm reset*/  
  NonMaskableInt_IRQn           = -14,    /*!< 2 Non Maskable Interrupt                           */
  HardFault_IRQn                = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                   */
  SVCall_IRQn                   = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                     */
  DebugMonitor_IRQn             = -4,     /*!<  12  Debug Monitor                                 */
  PendSV_IRQn                   = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                     */
  SysTick_IRQn                  = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                 */

/******  LPC8xx Specific Interrupt Numbers ********************************************************/
  SPI0_IRQn                     = 0,        /*!< SPI0                                             */
  SPI1_IRQn                     = 1,        /*!< SPI1                                             */
  Reserved0_IRQn                = 2,        /*!< Reserved Interrupt                               */	
  UART0_IRQn                    = 3,        /*!< USART0                                           */
  UART1_IRQn                    = 4,        /*!< USART1                                           */
  UART2_IRQn                    = 5,        /*!< USART2                                           */
  Reserved1_IRQn                = 6,        /*!< Reserved Interrupt                               */    
  I2C1_IRQn                     = 7,        /*!< I2C1                                             */
  I2C0_IRQn                     = 8,        /*!< I2C0                                             */
  SCT_IRQn                      = 9,        /*!< SCT                                              */
  MRT_IRQn                      = 10,       /*!< MRT                                              */ 
  CMP_IRQn                      = 11,       /*!< CMP                                              */
  WDT_IRQn                      = 12,       /*!< WDT                                              */
  BOD_IRQn                      = 13,       /*!< BOD                                              */
  FLASH_IRQn                    = 14,       /*!< FLASH                                            */
  WKT_IRQn                      = 15,       /*!< WKT Interrupt                                    */
  ADC_SEQA_IRQn                 = 16,       /*!< ADC Seq. A                                       */    
  ADC_SEQB_IRQn                 = 17,       /*!< ADC Seq. B                                       */
  ADC_THCMP_IRQn                = 18,       /*!< ADC Thresh Comp                                  */    
  ADC_OVR_IRQn                  = 19,       /*!< ADC overrun                                      */
  DMA_IRQn                      = 20,       /*!< DMA                                              */    
  I2C2_IRQn                     = 21,       /*!< I2C2                                             */
  I2C3_IRQn                     = 22,       /*!< I2C3                                             */    
  Reserved11_IRQn               = 23,       /*!< Reserved Interrupt                               */
  PININT0_IRQn                  = 24,       /*!< External Interrupt 0                             */
  PININT1_IRQn                  = 25,       /*!< External Interrupt 1                             */  
  PININT2_IRQn                  = 26,       /*!< External Interrupt 2                             */
  PININT3_IRQn                  = 27,       /*!< External Interrupt 3                             */
  PININT4_IRQn                  = 28,       /*!< External Interrupt 4                             */
  PININT5_IRQn                  = 29,       /*!< External Interrupt 5                             */
  PININT6_IRQn                  = 30,       /*!< External Interrupt 6                             */
  PININT7_IRQn                  = 31,       /*!< External Interrupt 7                             */
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0+ Processor and Core Peripherals */
#define __CM0PLUS_REV             0x0001
#define __MPU_PRESENT             0         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

/*@}*/ /* end of group LPC8xx_CMSIS */


#include "core_cm0plus.h"                  /* Cortex-M0+ processor and core peripherals          */
#include "system_LPC8xx.h"                 /* System Header                                      */


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/
/* ARM 02.09.2019 */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #  warning Not supported compiler type
#endif

//------------- System Control (SYSCON) --------------------------------------
typedef struct
{
  __IO uint32_t SYSMEMREMAP;            /*!< Offset: 0x000 System memory remap (R/W) */
  __IO uint32_t PRESETCTRL;             /*!< Offset: 0x004 Peripheral reset control (R/W) */
  __IO uint32_t SYSPLLCTRL;             /*!< Offset: 0x008 System PLL control (R/W) */
  __IO uint32_t SYSPLLSTAT;             /*!< Offset: 0x00C System PLL status (R/W ) */
       uint32_t RESERVED0[4];

  __IO uint32_t SYSOSCCTRL;             /*!< Offset: 0x020 System oscillator control (R/W) */
  __IO uint32_t WDTOSCCTRL;             /*!< Offset: 0x024 Watchdog oscillator control (R/W) */
  __IO uint32_t IRCCTRL;                // 0x28            
       uint32_t RESERVED1;
  __IO uint32_t SYSRSTSTAT;             /*!< Offset: 0x030 System reset status Register (R/W ) */
       uint32_t RESERVED2[3];
  __IO uint32_t SYSPLLCLKSEL;           /*!< Offset: 0x040 System PLL clock source select (R/W) */	
  __IO uint32_t SYSPLLCLKUEN;           /*!< Offset: 0x044 System PLL clock source update enable (R/W) */
       uint32_t RESERVED3[10];

  __IO uint32_t MAINCLKSEL;             /*!< Offset: 0x070 Main clock source select (R/W) */
  __IO uint32_t MAINCLKUEN;             /*!< Offset: 0x074 Main clock source update enable (R/W) */
  __IO uint32_t SYSAHBCLKDIV;           /*!< Offset: 0x078 System AHB clock divider (R/W) */
       uint32_t RESERVED4[1];

  __IO uint32_t SYSAHBCLKCTRL;          /*!< Offset: 0x080 System AHB clock control (R/W) */
       uint32_t RESERVED5[4];         
  __IO uint32_t UARTCLKDIV;             /*!< Offset: 0x094 UART clock divider (R/W) */         
       uint32_t RESERVED6[18];

  __IO uint32_t CLKOUTSEL;              /*!< Offset: 0x0E0 CLKOUT clock source select (R/W) */
  __IO uint32_t CLKOUTUEN;              /*!< Offset: 0x0E4 CLKOUT clock source update enable (R/W) */
  __IO uint32_t CLKOUTDIV;              /*!< Offset: 0x0E8 CLKOUT clock divider (R/W) */       
       uint32_t RESERVED7;
  __IO uint32_t UARTFRGDIV;             /*!< Offset: 0x0F0 UART fractional divider SUB(R/W) */ 
  __IO uint32_t UARTFRGMULT;             /*!< Offset: 0x0F4 UART fractional divider ADD(R/W) */   
       uint32_t RESERVED8[1];  
  __IO uint32_t EXTTRACECMD;            /*!< (@ 0x400480FC) External trace buffer command register  */  
  __IO uint32_t PIOPORCAP0;             /*!< Offset: 0x100 POR captured PIO status 0 (R/ ) */  
       uint32_t RESERVED9[12];
  __IO uint32_t IOCONCLKDIV6;           // 0x134
  __IO uint32_t IOCONCLKDIV5;           // 0x138
  __IO uint32_t IOCONCLKDIV4;           // 0x13c
  __IO uint32_t IOCONCLKDIV3;           // 0x140
  __IO uint32_t IOCONCLKDIV2;           // 0x144
  __IO uint32_t IOCONCLKDIV1;           // 0x148
  __IO uint32_t IOCONCLKDIV0;           // 0x14c
  __IO uint32_t BODCTRL;                /*!< Offset: 0x150 BOD control (R/W) */
  __IO uint32_t SYSTCKCAL;              /*!< Offset: 0x154 System tick counter calibration (R/W) */
       uint32_t RESERVED10[6];
  __IO uint32_t IRQLATENCY;             /*!< (@ 0x40048170) IRQ delay */
  __IO uint32_t NMISRC;                 /*!< (@ 0x40048174) NMI Source Control     */
  __IO uint32_t PINTSEL[8];             /*!< (@ 0x40048178) GPIO Pin Interrupt Select register 0 */
       uint32_t RESERVED11[27];
  __IO uint32_t STARTERP0;              /*!< Offset: 0x204 Start logic signal enable Register 0 (R/W) */      
       uint32_t RESERVED12[3];
  __IO uint32_t STARTERP1;              /*!< Offset: 0x214 Start logic signal enable Register 0 (R/W) */      
       uint32_t RESERVED13[6];
  __IO uint32_t PDSLEEPCFG;             /*!< Offset: 0x230 Power-down states in Deep-sleep mode (R/W) */
  __IO uint32_t PDAWAKECFG;             /*!< Offset: 0x234 Power-down states after wake-up (R/W) */        
  __IO uint32_t PDRUNCFG;               /*!< Offset: 0x238 Power-down configuration Register (R/W) */
       uint32_t RESERVED14[111];
  __I  uint32_t DEVICE_ID;              // 0x3f8
} LPC_SYSCON_TypeDef;




// ---------------- IOCON ----------------
typedef struct {                            /*!< (@ 0x40044000) IOCONFIG Structure     */
  __IO uint32_t PIO0_17;                    /*!< (@ 0x40044000) I/O configuration for pin PIO0_17 */
  __IO uint32_t PIO0_13;                    /*!< (@ 0x40044004) I/O configuration for pin PIO0_13 */
  __IO uint32_t PIO0_12;                    /*!< (@ 0x40044008) I/O configuration for pin PIO0_12 */
  __IO uint32_t PIO0_5;                     /*!< (@ 0x4004400C) I/O configuration for pin PIO0_5 */
  __IO uint32_t PIO0_4;                     /*!< (@ 0x40044010) I/O configuration for pin PIO0_4 */
  __IO uint32_t PIO0_3;                     /*!< (@ 0x40044014) I/O configuration for pin PIO0_3 */
  __IO uint32_t PIO0_2;                     /*!< (@ 0x40044018) I/O configuration for pin PIO0_2 */
  __IO uint32_t PIO0_11;                    /*!< (@ 0x4004401C) I/O configuration for pin PIO0_11 */
  __IO uint32_t PIO0_10;                    /*!< (@ 0x40044020) I/O configuration for pin PIO0_10 */
  __IO uint32_t PIO0_16;                    /*!< (@ 0x40044024) I/O configuration for pin PIO0_16 */
  __IO uint32_t PIO0_15;                    /*!< (@ 0x40044028) I/O configuration for pin PIO0_15 */
  __IO uint32_t PIO0_1;                     /*!< (@ 0x4004402C) I/O configuration for pin PIO0_1 */
  __IO uint32_t Reserved0;                  /*!< (@ 0x40044030) Reserved */
  __IO uint32_t PIO0_9;                     /*!< (@ 0x40044034) I/O configuration for pin PIO0_9 */
  __IO uint32_t PIO0_8;                     /*!< (@ 0x40044038) I/O configuration for pin PIO0_8 */
  __IO uint32_t PIO0_7;                     /*!< (@ 0x4004403C) I/O configuration for pin PIO0_7 */
  __IO uint32_t PIO0_6;                     /*!< (@ 0x40044040) I/O configuration for pin PIO0_6 */
  __IO uint32_t PIO0_0;                     /*!< (@ 0x40044044) I/O configuration for pin PIO0_0 */
  __IO uint32_t PIO0_14;                    /*!< (@ 0x40044048) I/O configuration for pin PIO0_14 */
  __IO uint32_t Reserved1;                  // 0x4c
  __IO uint32_t PIO0_28;                    // 0x50
  __IO uint32_t PIO0_27;                    // 0x54
  __IO uint32_t PIO0_26;                    // 0x58
  __IO uint32_t PIO0_25;                    // 0x5c
  __IO uint32_t PIO0_24;                    // 0x60
  __IO uint32_t PIO0_23;                    // 0x64
  __IO uint32_t PIO0_22;                    // 0x68
  __IO uint32_t PIO0_21;                    // 0x6c
  __IO uint32_t PIO0_20;                    // 0x70
  __IO uint32_t PIO0_19;                    // 0x74
  __IO uint32_t PIO0_18;                    // 0x78
} LPC_IOCON_TypeDef;



// ================================================================================
// ================                    FLASHCTRL                   ================
// ================================================================================
typedef struct {                         /*!< (@ 0x40040000) FLASHCTRL Structure */
  __I  uint32_t  RESERVED0[4];
  __IO uint32_t  FLASHCFG;               /*!< (@ 0x40040010) Flash configuration register */
  __I  uint32_t  RESERVED1[3];
  __IO uint32_t  FMSSTART;               /*!< (@ 0x40040020) Signature start address register */
  __IO uint32_t  FMSSTOP;                /*!< (@ 0x40040024) Signature stop-address register  */
  __I  uint32_t  RESERVED2;
  __I  uint32_t  FMSW0;                  /*!< (@ 0x4004002C) Signature Word */
} LPC_FLASHCTRL_TypeDef;



//------------- Power Management Unit (PMU) --------------------------
typedef struct
{
  __IO uint32_t PCON;                   /*!< Offset: 0x000 Power control Register (R/W) */
  __IO uint32_t GPREG0;                 /*!< Offset: 0x004 General purpose Register 0 (R/W) */
  __IO uint32_t GPREG1;                 /*!< Offset: 0x008 General purpose Register 1 (R/W) */
  __IO uint32_t GPREG2;                 /*!< Offset: 0x00C General purpose Register 2 (R/W) */
  __IO uint32_t GPREG3;                 /*!< Offset: 0x010 General purpose Register 3 (R/W) */
  __IO uint32_t DPDCTRL;                /*!< Offset: 0x014 Deep power-down control register (R/W) */
} LPC_PMU_TypeDef;



//------------- Switch Matrix (SWM) --------------------------
typedef struct
{
  union {
    __IO uint32_t PINASSIGN[12];
    struct {
      __IO uint32_t PINASSIGN0;
      __IO uint32_t PINASSIGN1;
      __IO uint32_t PINASSIGN2;
      __IO uint32_t PINASSIGN3;
      __IO uint32_t PINASSIGN4;
      __IO uint32_t PINASSIGN5;
      __IO uint32_t PINASSIGN6;
      __IO uint32_t PINASSIGN7;
      __IO uint32_t PINASSIGN8;
      __IO uint32_t PINASSIGN9;
      __IO uint32_t PINASSIGN10;
      __IO uint32_t PINASSIGN11;

    };
  };
  __I  uint32_t  RESERVED0[100];
  __IO uint32_t  PINENABLE0;
} LPC_SWM_TypeDef;



// ------------------------------------------------------------------------------------------------
// -----                      General Purpose I/O (GPIO)                                      -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            
  __IO uint8_t B0[29];            // 0x0 - 0x1c Byte pin registers P0.0 - P0.28
  __I  uint8_t RESERVED0[4067];
  __IO uint32_t W0[29];           // 0x1000 - 0x1074 Word pin registers
       uint32_t RESERVED1[995];
  __IO uint32_t DIR0;             // 0x2000
       uint32_t RESERVED2[31];
  __IO uint32_t MASK0;            // 0x2080
       uint32_t RESERVED3[31];
  __IO uint32_t PIN0;             // 0x2100 
       uint32_t RESERVED4[31];
  __IO uint32_t MPIN0;            // 0x2180
       uint32_t RESERVED5[31];
  __IO uint32_t SET0;             // 0x2200
       uint32_t RESERVED6[31];
  __O  uint32_t CLR0;             // 0x2280
       uint32_t RESERVED7[31];
  __O  uint32_t NOT0;             // 0x2300
       uint32_t RESERVED8[31];
  __O  uint32_t DIRSET0;          // 0x2380
       uint32_t RESERVED9[31];
  __O  uint32_t DIRCLR0;          // 0x2400
       uint32_t RESERVED10[31];
  __O  uint32_t DIRNOT0;          // 0x2480
} LPC_GPIO_PORT_TypeDef;



// ------------------------------------------------------------------------------------------------
// ----- Pin Interrupts and Pattern Match  (PIN_INT)                                          -----
// ------------------------------------------------------------------------------------------------
typedef struct {                            /*!< (@ 0xA0004000) PIN_INT Structure */
  __IO uint32_t ISEL;                       /*!< (@ 0xA0004000) Pin Interrupt Mode register */
  __IO uint32_t IENR;                       /*!< (@ 0xA0004004) Pin Interrupt Enable (Rising) register */
  __IO uint32_t SIENR;                      /*!< (@ 0xA0004008) Set Pin Interrupt Enable (Rising) register */
  __IO uint32_t CIENR;                      /*!< (@ 0xA000400C) Clear Pin Interrupt Enable (Rising) register */
  __IO uint32_t IENF;                       /*!< (@ 0xA0004010) Pin Interrupt Enable Falling Edge / Active Level register */
  __IO uint32_t SIENF;                      /*!< (@ 0xA0004014) Set Pin Interrupt Enable Falling Edge / Active Level register */
  __IO uint32_t CIENF;                      /*!< (@ 0xA0004018) Clear Pin Interrupt Enable Falling Edge / Active Level address */
  __IO uint32_t RISE;                       /*!< (@ 0xA000401C) Pin Interrupt Rising Edge register */
  __IO uint32_t FALL;                       /*!< (@ 0xA0004020) Pin Interrupt Falling Edge register */
  __IO uint32_t IST;                        /*!< (@ 0xA0004024) Pin Interrupt Status register */
  __IO uint32_t PMCTRL;                     /*!< (@ 0xA0004028) GPIO pattern match interrupt control register          */
  __IO uint32_t PMSRC;                      /*!< (@ 0xA000402C) GPIO pattern match interrupt bit-slice source register */
  __IO uint32_t PMCFG;                      /*!< (@ 0xA0004030) GPIO pattern match interrupt bit slice configuration register */
} LPC_PIN_INT_TypeDef;




//------------- CRC Engine (CRC) -----------------------------------------
typedef struct
{
  __IO uint32_t MODE;
  __IO uint32_t SEED;
  union {
  __I  uint32_t SUM;
  __O  uint32_t WR_DATA;
  };
} LPC_CRC_TypeDef;





//------------- Comparator (CMP) --------------------------------------------------
typedef struct {                            /*!< (@ 0x40024000) CMP Structure          */
  __IO uint32_t  CTRL;                      /*!< (@ 0x40024000) Comparator control register */
  __IO uint32_t  LAD;                       /*!< (@ 0x40024004) Voltage ladder register */
} LPC_CMP_TypeDef;






//------------- Self Wakeup Timer (WKT) --------------------------------------------------
typedef struct {                            /*!< (@ 0x40028000) WKT Structure          */
  __IO uint32_t  CTRL;                      /*!< (@ 0x40028000) Alarm/Wakeup Timer Control register */
       uint32_t  Reserved[2];
  __IO uint32_t  COUNT;                     /*!< (@ 0x4002800C) Alarm/Wakeup TImer counter register */
} LPC_WKT_TypeDef;






//------------- Multi-Rate Timer(MRT) --------------------------------------------------
typedef struct {
__IO uint32_t INTVAL;        							
__IO uint32_t TIMER;         							
__IO uint32_t CTRL;          							
__IO uint32_t STAT;          							
} MRT_Channel_cfg_Type;

typedef struct {
  MRT_Channel_cfg_Type Channel[4]; 		
  uint32_t Reserved0[45];          // Address offsets = 0x40 - 0xF0
  __IO uint32_t IDLE_CH; 			
  __IO uint32_t IRQ_FLAG; 						
} LPC_MRT_TypeDef;






//------------- Universal Asynchronous Receiver Transmitter (USART) -----------
typedef struct
{
  __IO uint32_t  CFG;
  __IO uint32_t  CTL;
  __IO uint32_t  STAT;
  __IO uint32_t  INTENSET;
  __O  uint32_t  INTENCLR;
  __I  uint32_t  RXDAT;
  __I  uint32_t  RXDATSTAT;
  __IO uint32_t  TXDAT;
  __IO uint32_t  BRG;
  __I  uint32_t  INTSTAT;
  __IO uint32_t  OSR;
  __IO uint32_t  ADDR;
} LPC_USART_TypeDef;







//------------- SPI -----------------------
typedef struct
{
  __IO uint32_t  CFG;			    /* 0x00 */
  __IO uint32_t  DLY;
  __IO uint32_t  STAT;
  __IO uint32_t  INTENSET;
  __O  uint32_t  INTENCLR;		/* 0x10 */
  __I  uint32_t  RXDAT;
  __IO uint32_t  TXDATCTL;
  __IO uint32_t  TXDAT;
  __IO uint32_t  TXCTL; 		  /* 0x20 */
  __IO uint32_t  DIV;
  __I  uint32_t  INTSTAT;
} LPC_SPI_TypeDef;






//------------- Inter-Integrated Circuit (I2C) -------------------------------
typedef struct
{
  __IO uint32_t  CFG;			  /* 0x00 */
  __IO uint32_t  STAT;
  __IO uint32_t  INTENSET;
  __O  uint32_t  INTENCLR;
  __IO uint32_t  TIMEOUT;		/* 0x10 */
  union {
    __IO uint32_t  CLKDIV;
    __IO uint32_t  DIV;
  };
  __IO uint32_t  INTSTAT;
       uint32_t  Reserved0[1];  
  __IO uint32_t  MSTCTL;			  /* 0x20 */
  __IO uint32_t  MSTTIME;
  __IO uint32_t  MSTDAT;
       uint32_t  Reserved1[5];
  __IO uint32_t  SLVCTL;			  /* 0x40 */
  __IO uint32_t  SLVDAT;
  __IO uint32_t  SLVADR0;
  __IO uint32_t  SLVADR1;
  __IO uint32_t  SLVADR2;			  /* 0x50 */
  __IO uint32_t  SLVADR3;
  __IO uint32_t  SLVQUAL0;
       uint32_t  Reserved2[9];
  __I  uint32_t  MONRXDAT;			/* 0x80 */		
} LPC_I2C_TypeDef;






// ================================================================================
// == preferred SCT structure (fully populated with array access)     =============
// ================================================================================

#define CONFIG_SCT_nEV   (8)      // Number of events 
#define CONFIG_SCT_nRG   (8)      // Number of match/compare registers 
#define CONFIG_SCT_nOU   (6)      // Number of outputs 

typedef struct {

  __IO  uint32_t CONFIG;           // 0x0

  union {
    __IO uint32_t CTRL;            // 0x4
    struct {
      __IO uint16_t CTRL_L;
      __IO uint16_t CTRL_H;
    };
  };

  union {
    __IO uint32_t LIMIT;           // 0x8
    struct {
      __IO uint16_t LIMIT_L;
      __IO uint16_t LIMIT_H;
    };
  };

  union {
    __IO uint32_t HALT;            // 0xc
    struct {
      __IO uint16_t HALT_L;
      __IO uint16_t HALT_H;
    };
  };

  union {
    __IO uint32_t STOP;            // 0x10
    struct {
      __IO uint16_t STOP_L;
      __IO uint16_t STOP_H;
    };
  };

  union {
    __IO uint32_t START;           // 0x14
    struct {
      __IO uint16_t START_L;
      __IO uint16_t START_H;
    };
  };

  uint32_t RESERVED1[10];

  union {
    __IO uint32_t COUNT;           // 0x40
    struct {
      __IO uint16_t COUNT_L;
      __IO uint16_t COUNT_H;
    };
  };

  union {
    __IO uint32_t STATE;           // 0x44
    struct {
      __IO uint16_t STATE_L;
      __IO uint16_t STATE_H;
    };
  };

  __I  uint32_t INPUT;             // 0x48

  union {
    __IO uint32_t REGMODE;         // 0x4c
    struct {
      __IO uint16_t REGMODE_L;
      __IO uint16_t REGMODE_H;
    };
  };

  __IO uint32_t OUTPUT;            // 0x50
  __IO uint32_t OUTPUTDIRCTRL;     // 0x54
  __IO uint32_t RES;               // 0x58
  __IO uint32_t DMAREQ0;           // 0x5c
  __IO uint32_t DMAREQ1;           // 0x60
  uint32_t RESERVED2[35];          // 0x64 - 0xec
  __IO uint32_t EVEN;              // 0xf0
  __IO uint32_t EVFLAG;            // 0xf4
  __IO uint32_t CONEN;             // 0xf8
  __IO uint32_t CONFLAG;           // 0xfc

  union {                          // Match / Capture 0x100 - 0x13c
    __IO union {                          
      uint32_t U;                  // MATCH[i].U  Unified 32-bit register
      struct {
        uint16_t L;                // MATCH[i].L  Access to L value
        uint16_t H;                // MATCH[i].H  Access to H value
      };
    } MATCH[CONFIG_SCT_nRG];

    __I union {
      uint32_t U;                  // CAP[i].U  Unified 32-bit register 
      struct {
        uint16_t L;                // CAP[i].L  Access to L value 
        uint16_t H;                // CAP[i].H  Access to H value 
      };
    } CAP[CONFIG_SCT_nRG];
  };

  uint32_t RESERVED3[32 - CONFIG_SCT_nRG];  // ...-0x17C reserved

  union {
    __IO uint16_t MATCH_L[CONFIG_SCT_nRG];  // 0x180-... Match Value L counter 
    __I  uint16_t CAP_L[CONFIG_SCT_nRG];    // 0x180-... Capture Value L counter
  };

  uint16_t RESERVED4[32 - CONFIG_SCT_nRG];  // ...-0x1BE reserved

  union {
    __IO uint16_t MATCH_H[CONFIG_SCT_nRG];  // 0x1C0-... Match Value H counter
    __I  uint16_t CAP_H[CONFIG_SCT_nRG];    // 0x1C0-... Capture Value H counter
  };

  uint16_t RESERVED5[32 - CONFIG_SCT_nRG];  // ...-0x1FE reserved
  
  union {
    __IO union {                            // 0x200-... Match Reload / Capture Control value
      uint32_t U;                           // MATCHREL[i].U  Unified 32-bit register
      struct {
        uint16_t L;                         // MATCHREL[i].L  Access to L value 
        uint16_t H;                         // MATCHREL[i].H  Access to H value 
      };
    } MATCHREL[CONFIG_SCT_nRG];

    __IO union {
      uint32_t U;                           // CAPCTRL[i].U  Unified 32-bit register
      struct {
        uint16_t L;                         // CAPCTRL[i].L  Access to L value 
        uint16_t H;                         // SCTCAPCTRL[i].H  Access to H value
      };
    } CAPCTRL[CONFIG_SCT_nRG];
  };

  uint32_t RESERVED6[32 - CONFIG_SCT_nRG];   // ...-0x27C reserved 

  union {
    __IO uint16_t MATCHREL_L[CONFIG_SCT_nRG]; // 0x280-... Match Reload value L counter
    __IO uint16_t CAPCTRL_L[CONFIG_SCT_nRG];  // 0x280-... Capture Control value L counter
  };

  uint16_t RESERVED7[32 - CONFIG_SCT_nRG];    // ...-0x2BE reserved 

  union {
    __IO uint16_t MATCHREL_H[CONFIG_SCT_nRG]; // 0x2C0-... Match Reload value H counter 
    __IO uint16_t CAPCTRL_H[CONFIG_SCT_nRG];  // 0x2C0-... Capture Control value H counter 
  };

  uint16_t RESERVED8[32 - CONFIG_SCT_nRG];    // ...-0x2FE reserved

  __IO struct {                               // 0x300-0x3FC  EVENT[i].STATE / EVENT[i].CTRL
    uint32_t STATE;
    uint32_t CTRL;
  } EVENT[CONFIG_SCT_nEV];

  uint32_t RESERVED9[128 - (2 * CONFIG_SCT_nEV)]; // ...-0x4FC reserved 

  __IO struct {                               // 0x500-0x57C  OUT[n].SET / OUT[n].CLR 
    uint32_t SET;                             // Output n Set Register 
    uint32_t CLR;                             // Output n Clear Register
  } OUT[CONFIG_SCT_nOU];

  uint32_t RESERVED10[((0x300 / 4) - 1) - (2 * CONFIG_SCT_nOU)]; // ...-0x7F8 reserved 
  
  __I  uint32_t MODULECONTENT;                // 0x7FC Module Content 

} LPC_SCT_TypeDef;







// ================================================================================
// == optional SCT structure (user manual verbatim, no array access)  =============
// ================================================================================
/*
typedef struct {                                    //!< (@ 0x50004000) SCT Structure                                            
  __IO uint32_t  CONFIG;                            //!< (@ 0x50004000) SCT configuration register                               
  __IO uint32_t  CTRL;                              //!< (@ 0x50004004) SCT control register                                     
  __IO uint32_t  LIMIT;                             //!< (@ 0x50004008) SCT limit register                                       
  __IO uint32_t  HALT;                              //!< (@ 0x5000400C) SCT halt condition register                              
  __IO uint32_t  STOP;                              //!< (@ 0x50004010) SCT stop condition register                              
  __IO uint32_t  START;                             //!< (@ 0x50004014) SCT start condition register                             
  __I  uint32_t  RESERVED0[10];
  __IO uint32_t  COUNT;                             //!< (@ 0x50004040) SCT counter register                                     
  __IO uint32_t  STATE;                             //!< (@ 0x50004044) SCT state register                                       
  __I  uint32_t  INPUT;                             //!< (@ 0x50004048) SCT input register                                       
  __IO uint32_t  REGMODE;                           //!< (@ 0x5000404C) SCT match/capture registers mode register                
  __IO uint32_t  OUTPUT;                            //!< (@ 0x50004050) SCT output register                                      
  __IO uint32_t  OUTPUTDIRCTRL;                     //!< (@ 0x50004054) SCT output counter direction control register            
  __IO uint32_t  RES;                               //!< (@ 0x50004058) SCT conflict resolution register                         
  __IO uint32_t  DMAREQ0;                           //!< (@ 0x5000405C) SCT DMA request 0 register                               
  __IO uint32_t  DMAREQ1;                           //!< (@ 0x50004060) SCT DMA request 1 register                               
  __I  uint32_t  RESERVED1[35];
  __IO uint32_t  EVEN;                              //!< (@ 0x500040F0) SCT event enable register                                
  __IO uint32_t  EVFLAG;                            //!< (@ 0x500040F4) SCT event flag register                                  
  __IO uint32_t  CONEN;                             //!< (@ 0x500040F8) SCT conflict enable register                             
  __IO uint32_t  CONFLAG;                           //!< (@ 0x500040FC) SCT conflict flag register                               
  
  union {
    __IO uint32_t  CAP0;                            //!< (@ 0x50004100) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
    __IO uint32_t  MATCH0;                          //!< (@ 0x50004100) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                                           
  };
  
  union {
    __IO uint32_t  CAP1;                            //!< (@ 0x50004104) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
    __IO uint32_t  MATCH1;                          //!< (@ 0x50004104) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                                           
  };
  
  union {
    __IO uint32_t  CAP2;                            //!< (@ 0x50004108) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
    __IO uint32_t  MATCH2;                          //!< (@ 0x50004108) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                                           
  };
  
  union {
    __IO uint32_t  MATCH3;                          //!< (@ 0x5000410C) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                                           
    __IO uint32_t  CAP3;                            //!< (@ 0x5000410C) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
  };
  
  union {
    __IO uint32_t  CAP4;                            //!< (@ 0x50004110) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
    __IO uint32_t  MATCH4;                          //!< (@ 0x50004110) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                                           
  };
  
  union {
    __IO uint32_t  MATCH5;                          //!< (@ 0x50004114) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                                           
    __IO uint32_t  CAP5;                            //!< (@ 0x50004114) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
  };
  
  union {
    __IO uint32_t  CAP6;                            //!< (@ 0x50004118) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
    __IO uint32_t  MATCH6;                          //!< (@ 0x50004118) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                                           
  };
  
  union {
    __IO uint32_t  CAP7;                            //!< (@ 0x5000411C) SCT capture register of capture channel 0 to 7; REGMOD0 to REGMODE7 = 1                                              
    __IO uint32_t  MATCH7;                          //!< (@ 0x5000411C) SCT match value register of match channels 0 to 7; REGMOD0 to REGMODE7 = 0                              
  };
  __I  uint32_t  RESERVED2[56];
  
  union {
    __IO uint32_t  CAPCTRL0;                        //!< (@ 0x50004200) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
    __IO uint32_t  MATCHREL0;                       //!< (@ 0x50004200) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
  };
  
  union {
    __IO uint32_t  CAPCTRL1;                        //!< (@ 0x50004204) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
    __IO uint32_t  MATCHREL1;                       //!< (@ 0x50004204) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
  };
  
  union {
    __IO uint32_t  CAPCTRL2;                        //!< (@ 0x50004208) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
    __IO uint32_t  MATCHREL2;                       //!< (@ 0x50004208) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
  };
  
  union {
    __IO uint32_t  MATCHREL3;                       //!< (@ 0x5000420C) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
    __IO uint32_t  CAPCTRL3;                        //!< (@ 0x5000420C) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
  };
  
  union {
    __IO uint32_t  CAPCTRL4;                        //!< (@ 0x50004210) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
    __IO uint32_t  MATCHREL4;                       //!< (@ 0x50004210) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
  };
  
  union {
    __IO uint32_t  CAPCTRL5;                        //!< (@ 0x50004214) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
    __IO uint32_t  MATCHREL5;                       //!< (@ 0x50004214) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
  };
  
  union {
    __IO uint32_t  CAPCTRL6;                        //!< (@ 0x50004218) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
    __IO uint32_t  MATCHREL6;                       //!< (@ 0x50004218) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
  };
  
  union {
    __IO uint32_t  CAPCTRL7;                        //!< (@ 0x5000421C) SCT capture control register 0 to 7; REGMOD0 = 1 to REGMODE7 = 1                                                     
    __IO uint32_t  MATCHREL7;                       //!< (@ 0x5000421C) SCT match reload value register 0 to 7; REGMOD0 = 0 to REGMODE7 = 0                                                     
  };
  __I  uint32_t  RESERVED3[56];
  __IO uint32_t  EV0_STATE;                         //!< (@ 0x50004300) SCT event state register 0                               
  __IO uint32_t  EV0_CTRL;                          //!< (@ 0x50004304) SCT event control register 0                             
  __IO uint32_t  EV1_STATE;                         //!< (@ 0x50004308) SCT event state register 0                               
  __IO uint32_t  EV1_CTRL;                          //!< (@ 0x5000430C) SCT event control register 0                             
  __IO uint32_t  EV2_STATE;                         //!< (@ 0x50004310) SCT event state register 0                               
  __IO uint32_t  EV2_CTRL;                          //!< (@ 0x50004314) SCT event control register 0                             
  __IO uint32_t  EV3_STATE;                         //!< (@ 0x50004318) SCT event state register 0                               
  __IO uint32_t  EV3_CTRL;                          //!< (@ 0x5000431C) SCT event control register 0                             
  __IO uint32_t  EV4_STATE;                         //!< (@ 0x50004320) SCT event state register 0                               
  __IO uint32_t  EV4_CTRL;                          //!< (@ 0x50004324) SCT event control register 0                             
  __IO uint32_t  EV5_STATE;                         //!< (@ 0x50004328) SCT event state register 0                               
  __IO uint32_t  EV5_CTRL;                          //!< (@ 0x5000432C) SCT event control register 0                             
  __IO uint32_t  EV6_STATE;                         //!< (@ 0x50004330) SCT event state register 0                               
  __IO uint32_t  EV6_CTRL;                          //!< (@ 0x50004334) SCT event control register 0                             
  __IO uint32_t  EV7_STATE;                         //!< (@ 0x50004338) SCT event state register 0                               
  __IO uint32_t  EV7_CTRL;                          //!< (@ 0x5000433C) SCT event control register 0                             
  __I  uint32_t  RESERVED4[112];
  __IO uint32_t  OUT0_SET;                          //!< (@ 0x50004500) SCT output 0 set register                                
  __IO uint32_t  OUT0_CLR;                          //!< (@ 0x50004504) SCT output 0 clear register                              
  __IO uint32_t  OUT1_SET;                          //!< (@ 0x50004508) SCT output 0 set register                                
  __IO uint32_t  OUT1_CLR;                          //!< (@ 0x5000450C) SCT output 0 clear register                              
  __IO uint32_t  OUT2_SET;                          //!< (@ 0x50004510) SCT output 0 set register                                
  __IO uint32_t  OUT2_CLR;                          //!< (@ 0x50004514) SCT output 0 clear register                              
  __IO uint32_t  OUT3_SET;                          //!< (@ 0x50004518) SCT output 0 set register                                
  __IO uint32_t  OUT3_CLR;                          //!< (@ 0x5000451C) SCT output 0 clear register                              
  __IO uint32_t  OUT4_SET;                          //!< (@ 0x50004520) SCT output 0 set register                                
  __IO uint32_t  OUT4_CLR;                          //!< (@ 0x50004524) SCT output 0 clear register                              
  __IO uint32_t  OUT5_SET;                          //!< (@ 0x50004528) SCT output 0 set register                                
  __IO uint32_t  OUT5_CLR;                          //!< (@ 0x5000452C) SCT output 0 clear register                              
} LPC_SCT_TypeDef;
*/







//------------- Windowed Watchdog Timer (WWDT) -----------------------------------------
typedef struct
{
  __IO uint32_t MOD;                    /*!< Offset: 0x000 Watchdog mode register (R/W) */
  __IO uint32_t TC;                     /*!< Offset: 0x004 Watchdog timer constant register (R/W) */
  __O  uint32_t FEED;                   /*!< Offset: 0x008 Watchdog feed sequence register (W) */
  __I  uint32_t TV;                     /*!< Offset: 0x00C Watchdog timer value register (R) */
       uint32_t RESERVED;               /*!< Offset: 0x010 RESERVED                          */
  __IO uint32_t WARNINT;                /*!< Offset: 0x014 Watchdog timer warning int. register (R/W) */
  __IO uint32_t WINDOW;                 /*!< Offset: 0x018 Watchdog timer window value register (R/W) */
} LPC_WWDT_TypeDef;









//------------- DMA Trigger Mux -----------------------------------------
typedef struct {
  __IO uint32_t DMA_ITRIG_INMUX0;       // 0x0
  __IO uint32_t DMA_ITRIG_INMUX1;       // 0x4
  __IO uint32_t DMA_ITRIG_INMUX2;       // 0x8
  __IO uint32_t DMA_ITRIG_INMUX3;       // 0xC
  __IO uint32_t DMA_ITRIG_INMUX4;       // 0x10
  __IO uint32_t DMA_ITRIG_INMUX5;       // 0x14
  __IO uint32_t DMA_ITRIG_INMUX6;       // 0x18
  __IO uint32_t DMA_ITRIG_INMUX7;       // 0x1C
  __IO uint32_t DMA_ITRIG_INMUX8;       // 0x20
  __IO uint32_t DMA_ITRIG_INMUX9;       // 0x24
  __IO uint32_t DMA_ITRIG_INMUX10;      // 0x28
  __IO uint32_t DMA_ITRIG_INMUX11;      // 0x2C
  __IO uint32_t DMA_ITRIG_INMUX12;      // 0x30
  __IO uint32_t DMA_ITRIG_INMUX13;      // 0x34
  __IO uint32_t DMA_ITRIG_INMUX14;      // 0x38
  __IO uint32_t DMA_ITRIG_INMUX15;      // 0x3C
  __IO uint32_t DMA_ITRIG_INMUX16;      // 0x40
  __IO uint32_t DMA_ITRIG_INMUX17;      // 0x44
} LPC_DMATRIGMUX_TypeDef;






//------------- Input Mux -----------------------------------------
typedef struct {
  __IO uint32_t DMA_INMUX_INMUX0;       // 0x0
  __IO uint32_t DMA_INMUX_INMUX1;       // 0x4
       uint32_t Preserved[6];           // 0x8 - 0x1C
  __IO uint32_t SCT0_INMUX0;            // 0x20
  __IO uint32_t SCT0_INMUX1;            // 0x24
  __IO uint32_t SCT0_INMUX2;            // 0x28
  __IO uint32_t SCT0_INMUX3;            // 0x2C
} LPC_INPUTMUX_TypeDef;






/*------------- ADC -----------------------------------------*/
typedef struct {
  __IO uint32_t CTRL;           // 0x0
       uint32_t RESERVED0;      // 0x4
  __IO uint32_t SEQA_CTRL;      // 0x8
  __IO uint32_t SEQB_CTRL;      // 0xC
  __IO uint32_t SEQA_GDAT;      // 0x10
  __IO uint32_t SEQB_GDAT;      // 0x14
       uint32_t RESERVED1[2];   // 0x18 - 0x1C
  __IO uint32_t DAT[12];        // 0x20 - 0x4C
  __IO uint32_t THR0_LOW;       // 0x50
  __IO uint32_t THR1_LOW;       // 0x54
  __IO uint32_t THR0_HIGH;      // 0x58
  __IO uint32_t THR1_HIGH;      // 0x5C
  __IO uint32_t CHAN_THRSEL;    // 0x60
  __IO uint32_t INTEN;          // 0x64
  __IO uint32_t FLAGS;          // 0x68
  __IO uint32_t TRM;            // 0x6C
} LPC_ADC_TypeDef;






/*------------- DMA -----------------------------------------*/
#define NUM_DMA_CHANNELS 18

typedef struct {
  __IO uint32_t  CFG;
  __I  uint32_t  CTLSTAT;
  __IO uint32_t  XFERCFG;
  __I  uint32_t  RESERVED;
} LPC_DMA_CHANNEL_T;

typedef struct {
  __IO uint32_t  CTRL;                          // 0x0
  __I  uint32_t  INTSTAT;                       // 0x4
  __IO uint32_t  SRAMBASE;                      // 0x8
  __I  uint32_t  RESERVED0[5];                  // 0x10 - 0x1C
  __IO uint32_t  ENABLESET0;                    // 0x20
  __I  uint32_t  RESERVED1;                     // 0x24
  __O  uint32_t  ENABLECLR0;                    // 0x28
  __I  uint32_t  RESERVED2;                     // 0x2C
  __I  uint32_t  ACTIVE0;                       // 0x30
  __I  uint32_t  RESERVED3;                     // 0x34
  __I  uint32_t  BUSY0;                         // 0x38
  __I  uint32_t  RESERVED4;                     // 0x3C
  __IO uint32_t  ERRINT0;                       // 0x40
  __I  uint32_t  RESERVED5;                     // 0x44
  __IO uint32_t  INTENSET0;                     // 0x48
  __I  uint32_t  RESERVED6;                     // 0x4C
  __O  uint32_t  INTENCLR0;                     // 0x50
  __I  uint32_t  RESERVED7;                     // 0x54
  __IO uint32_t  INTA0;                         // 0x58
  __I  uint32_t  RESERVED8;                     // 0x5C
  __IO uint32_t  INTB0;                         // 0x60
  __I  uint32_t  RESERVED9;                     // 0x64
  __O  uint32_t  SETVALID0;                     // 0x68
  __I  uint32_t  RESERVED10;                    // 0x6C
  __O  uint32_t  SETTRIG0;                      // 0x70
  __I  uint32_t  RESERVED11;                    // 0x74
  __O  uint32_t  ABORT0;                        // 0x78
  __I  uint32_t  Absolutely_Nothing[225];       // 0x7C - 0x3FC
  LPC_DMA_CHANNEL_T CHANNEL[NUM_DMA_CHANNELS];  // 0x400 - 0x51C
} LPC_DMA_TypeDef;

/* ARM 02.09.2019 */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define LPC_FLASH_BASE        (0x00000000UL)
#define LPC_RAM_BASE          (0x10000000UL)
#define LPC_ROM_BASE          (0x1FFF0000UL)
#define LPC_APB0_BASE         (0x40000000UL)
#define LPC_AHB_BASE          (0x50000000UL)

/* APB0 peripherals */
#define LPC_WWDT_BASE         (LPC_APB0_BASE + 0x00000)
#define LPC_MRT_BASE          (LPC_APB0_BASE + 0x04000)
#define LPC_WKT_BASE          (LPC_APB0_BASE + 0x08000)
#define LPC_SWM_BASE          (LPC_APB0_BASE + 0x0C000)
#define LPC_ADC_BASE          (LPC_APB0_BASE + 0x1C000)
#define LPC_PMU_BASE          (LPC_APB0_BASE + 0x20000)
#define LPC_CMP_BASE          (LPC_APB0_BASE + 0x24000)
#define LPC_DMATRIGMUX_BASE   (LPC_APB0_BASE + 0x28000)
#define LPC_INPUTMUX_BASE     (LPC_APB0_BASE + 0x2C000)

#define LPC_FLASHCTRL_BASE    (LPC_APB0_BASE + 0x40000)
#define LPC_IOCON_BASE        (LPC_APB0_BASE + 0x44000)
#define LPC_SYSCON_BASE       (LPC_APB0_BASE + 0x48000)
#define LPC_I2C_BASE          (LPC_APB0_BASE + 0x50000)
#define LPC_I2C0_BASE         (LPC_APB0_BASE + 0x50000)
#define LPC_I2C1_BASE         (LPC_APB0_BASE + 0x54000)
#define LPC_I2C2_BASE         (LPC_APB0_BASE + 0x70000)
#define LPC_I2C3_BASE         (LPC_APB0_BASE + 0x74000)
#define LPC_SPI0_BASE         (LPC_APB0_BASE + 0x58000)
#define LPC_SPI1_BASE         (LPC_APB0_BASE + 0x5C000)
#define LPC_USART0_BASE       (LPC_APB0_BASE + 0x64000)
#define LPC_USART1_BASE       (LPC_APB0_BASE + 0x68000)
#define LPC_USART2_BASE       (LPC_APB0_BASE + 0x6C000)

/* AHB peripherals                                                            */
#define LPC_CRC_BASE         (LPC_AHB_BASE + 0x00000)
#define LPC_SCT_BASE         (LPC_AHB_BASE + 0x04000)
#define LPC_DMA_BASE         (LPC_AHB_BASE + 0x08000)
#define LPC_GPIO_PORT_BASE    (0xA0000000)
#define LPC_PIN_INT_BASE     (LPC_GPIO_PORT_BASE  + 0x4000)

/******************************************************************************/
/*                         Peripheral declarations                            */
/******************************************************************************/
#define LPC_DMA               ((LPC_DMA_TypeDef        *) LPC_DMA_BASE       )
#define LPC_ADC               ((LPC_ADC_TypeDef        *) LPC_ADC_BASE       )
#define LPC_DMATRIGMUX        ((LPC_DMATRIGMUX_TypeDef *) LPC_DMATRIGMUX_BASE)
#define LPC_INPUTMUX          ((LPC_INPUTMUX_TypeDef   *) LPC_INPUTMUX_BASE  )

#define LPC_WWDT              ((LPC_WWDT_TypeDef   *) LPC_WWDT_BASE  )
#define LPC_MRT               ((LPC_MRT_TypeDef    *) LPC_MRT_BASE   )


#define LPC_WKT               ((LPC_WKT_TypeDef    *) LPC_WKT_BASE   )
#define LPC_SWM               ((LPC_SWM_TypeDef    *) LPC_SWM_BASE   )
#define LPC_PMU               ((LPC_PMU_TypeDef    *) LPC_PMU_BASE   )
#define LPC_CMP               ((LPC_CMP_TypeDef    *) LPC_CMP_BASE   )

#define LPC_FLASHCTRL         ((LPC_FLASHCTRL_TypeDef *) LPC_FLASHCTRL_BASE )
#define LPC_IOCON             ((LPC_IOCON_TypeDef  *) LPC_IOCON_BASE )
#define LPC_SYSCON            ((LPC_SYSCON_TypeDef *) LPC_SYSCON_BASE)
#define LPC_I2C               ((LPC_I2C_TypeDef    *) LPC_I2C_BASE   )
#define LPC_I2C0              ((LPC_I2C_TypeDef    *) LPC_I2C0_BASE  )
#define LPC_I2C1              ((LPC_I2C_TypeDef    *) LPC_I2C1_BASE  )
#define LPC_I2C2              ((LPC_I2C_TypeDef    *) LPC_I2C2_BASE  )
#define LPC_I2C3              ((LPC_I2C_TypeDef    *) LPC_I2C3_BASE  )
#define LPC_SPI0              ((LPC_SPI_TypeDef    *) LPC_SPI0_BASE  )
#define LPC_SPI1              ((LPC_SPI_TypeDef    *) LPC_SPI1_BASE  )
#define LPC_USART0            ((LPC_USART_TypeDef   *) LPC_USART0_BASE )
#define LPC_USART1            ((LPC_USART_TypeDef   *) LPC_USART1_BASE )
#define LPC_USART2            ((LPC_USART_TypeDef   *) LPC_USART2_BASE )

#define LPC_CRC               ((LPC_CRC_TypeDef    *) LPC_CRC_BASE   )
#define LPC_SCT               ((LPC_SCT_TypeDef    *) LPC_SCT_BASE   )
#define LPC_SCT0              ((LPC_SCT_TypeDef    *) LPC_SCT_BASE   )

#define LPC_GPIO_PORT         ((LPC_GPIO_PORT_TypeDef  *) LPC_GPIO_PORT_BASE  )
#define LPC_PIN_INT          ((LPC_PIN_INT_TypeDef   *) LPC_PIN_INT_BASE  )

#ifdef __cplusplus
}
#endif

#endif  /* __LPC8xx_H__ */
