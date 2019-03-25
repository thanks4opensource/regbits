#include <stdint.h>

#include <LPC8xx.h>

#if 0   // now set in Makefile.base (or overriden by commandline/sub-makefile)
#undef ALL_HANDLERS_DEFAULT
#define WEAK_FUNCTIONS
#endif


void    init(void);
#ifdef ALL_HANDLERS_DEFAULT
void    Default_Handler         (void);
#else
void    NMI_Handler             (void),
        HardFault_Handler       (void),
        SVCall_Handler          (void),
        PendSV_Handler          (void),
        SysTick_Handler         (void),
/* External interrupt handlers follow */
        SPI0_IRQHandler         (void),
        SPI1_IRQHandler         (void),
        UART0_IRQHandler        (void),
        UART1_IRQHandler        (void),
        UART2_IRQHandler        (void),
        Reserved1_IRQHandler    (void),
#ifdef LPC82X
        I2C1_IRQHandler         (void),
        I2C0_IRQHandler         (void),
#endif
#ifdef LPC81X
        I2C_IRQHandler          (void),
#endif
        SCT_IRQHandler          (void),
        MRT_IRQHandler          (void),
        CMP_IRQHandler          (void),
        WDT_IRQHandler          (void),
        BOD_IRQHandler          (void),
        WKT_IRQHandler          (void),
#ifdef LPC82X
        ISE_ADC_SEQA_IRQHandler (void),
        ISE_ADC_SEQB_IRQHandler (void),
        ISE_ADC_THCMP_IRQHandler(void),
        ISE_ADC_OVR_IRQHandler  (void),
        ISE_SDMA_IRQHandler     (void),
        ISE_I2C2_IRQHandler     (void),
        ISE_I2C3_IRQHandler     (void),
#endif
        Reserved11_IRQHandler   (void),
        PININT0_IRQHandler      (void),
        PININT1_IRQHandler      (void),
        PININT2_IRQHandler      (void),
        PININT3_IRQHandler      (void),
        PININT4_IRQHandler      (void),
        PININT5_IRQHandler      (void),
        PININT6_IRQHandler      (void),
        PININT7_IRQHandler      (void);
#endif

int     main(void);

// The following are 'declared' in the linker script
extern uint8_t  BSS_START;
extern uint8_t  BSS_END;
extern uint8_t  TOP_OF_STACK;

// the section "isr_vectors" is placed at the beginning of ram
// by the linker script
void *INTERRUPT_VECTORS[] __attribute__((section(".isr_vectors"))) = {
    (void *)&TOP_OF_STACK,  /* Top of stack           */
    init,                   /* Reset Handler          */
#ifdef ALL_HANDLERS_DEFAULT
    Default_Handler,        /* NMI                    */
    Default_Handler,        /* Hard Fault             */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    Default_Handler,        /* SVCall                 */
    0,                      /* reserved               */
    0,                      /* reserved               */
    Default_Handler,        /* PendSV                 */
    Default_Handler,        /* SysTick                */
/* External interrupt handlers follow                 */
    Default_Handler,        /*  0 SPI0 controller     */
    Default_Handler,        /*  1 SPI1 controller     */
    Default_Handler,        /*  2 reserved            */
    Default_Handler,        /*  3 UART0               */
    Default_Handler,        /*  4 UART1               */
    Default_Handler,        /*  5 UART2               */
    Default_Handler,        /*  6 reserved            */
#ifdef LPC81X
    Default_Handler,        /*  7 reserved            */
    Default_Handler,        /*  8 I2C controller      */
#endif
#ifdef LPC82X
    Default_Handler,        /*  8 I2C1 controller     */
    Default_Handler,        /*  8 I2C0 controller     */
#endif
    Default_Handler,        /*  9 Smart Counter Timer */
    Default_Handler,        /* 10 Multi-Rate Timer    */
    Default_Handler,        /* 11 Comparator          */
    Default_Handler,        /* 12 PIO1 (0:11)         */
    Default_Handler,        /* 13 Brown Out Detect    */
    Default_Handler,        /* 14 reserved            */
    Default_Handler,        /* 15 Wakeup timer        */
#ifdef LPC81X
    Default_Handler,        /* 16 reserved            */
    Default_Handler,        /* 17 reserved            */
    Default_Handler,        /* 18 reserved            */
    Default_Handler,        /* 19 reserved            */
    Default_Handler,        /* 20 reserved            */
    Default_Handler,        /* 21 reserved            */
    Default_Handler,        /* 22 reserved            */
#endif
#ifdef LPC82X
    Default_Handler,        /* 16 ISE_ADC_SEQA        */
    Default_Handler,        /* 17 ISE_ADC_SEQB        */
    Default_Handler,        /* 18 ISE_ADC_THCMP       */
    Default_Handler,        /* 19 ISE_ADC_OVR         */
    Default_Handler,        /* 20 ISE_SDMA            */
    Default_Handler,        /* 21 ISE_I2C2            */
    Default_Handler,        /* 22 ISE_I2C3            */
#endif
    Default_Handler,        /* 23 reserved            */
    Default_Handler,        /* 24 PIO INT0            */
    Default_Handler,        /* 25 PIO INT1            */
    Default_Handler,        /* 26 PIO INT2            */
    Default_Handler,        /* 27 PIO INT3            */
    Default_Handler,        /* 28 PIO INT4            */
    Default_Handler,        /* 29 PIO INT5            */
    Default_Handler,        /* 30 PIO INT6            */
    Default_Handler,        /* 31 PIO INT7            */
#else
    NMI_Handler,            /* NMI                    */
    HardFault_Handler,      /* Hard Fault             */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    0,                      /* reserved               */
    SVCall_Handler,         /* SVCall                 */
    0,                      /* reserved               */
    0,                      /* reserved               */
    PendSV_Handler,         /* PendSV                 */
    SysTick_Handler,        /* SysTick                */
    /* External interrupt handlers follow             */
    SPI0_IRQHandler,        /*  0 SPI0 controller     */
    SPI1_IRQHandler,        /*  1 SPI1 controller     */
    0,                      /*  2 reserved            */
    UART0_IRQHandler,       /*  3 UART0               */
    UART1_IRQHandler,       /*  4 UART1               */
    UART2_IRQHandler,       /*  5 UART2               */
    Reserved1_IRQHandler,   /*  6 reserved            */
#ifdef LPC81X
    0,                      /*  7 reserved            */
    I2C_IRQHandler,         /*  8 I2C controller      */
#endif
#ifdef LPC82X
    I2C1_IRQHandler,        /*  8 I2C1 controller     */
    I2C0_IRQHandler,        /*  8 I2C0 controller     */
#endif
    SCT_IRQHandler,         /*  9 Smart Counter Timer */
    MRT_IRQHandler,         /* 10 Multi-Rate Timer    */
    CMP_IRQHandler,         /* 11 Comparator          */
    WDT_IRQHandler,         /* 12 PIO1 (0:11)         */
    BOD_IRQHandler,         /* 13 Brown Out Detect    */
    0,                      /* 14 reserved            */
    WKT_IRQHandler,         /* 15 Wakeup timer        */
#ifdef LPC81X
    0,                      /* 16 reserved            */
    0,                      /* 17 reserved            */
    0,                      /* 18 reserved            */
    0,                      /* 19 reserved            */
    0,                      /* 20 reserved            */
    0,                      /* 21 reserved            */
    0,                      /* 22 reserved            */
#endif
#ifdef LPC82X
    ISE_ADC_SEQA_IRQHandler,    /* 16 ISE_ADC_SEQA    */
    ISE_ADC_SEQB_IRQHandler,    /* 17 ISE_ADC_SEQB    */
    ISE_ADC_THCMP_IRQHandler,   /* 18 ISE_ADC_THCMP   */
    ISE_ADC_OVR_IRQHandler,     /* 19 ISE_ADC_OVR     */
    ISE_SDMA_IRQHandler,        /* 20 ISE_SDMA        */
    ISE_I2C2_IRQHandler,        /* 21 ISE_I2C2        */
    ISE_I2C3_IRQHandler,        /* 22 ISE_I2C3        */
#endif
    Reserved11_IRQHandler,  /* 23 reserved            */
    PININT0_IRQHandler,     /* 24 PIO INT0            */
    PININT1_IRQHandler,     /* 25 PIO INT1            */
    PININT2_IRQHandler,     /* 26 PIO INT2            */
    PININT3_IRQHandler,     /* 27 PIO INT3            */
    PININT4_IRQHandler,     /* 28 PIO INT4            */
    PININT5_IRQHandler,     /* 29 PIO INT5            */
    PININT6_IRQHandler,     /* 30 PIO INT6            */
    PININT7_IRQHandler,     /* 31 PIO INT7            */
#endif
};



#if 0
// from
// Projects/STM32L476G-Discovery/Templates_LL/Src/system_stm32l4xx.c
// SystemInit(void)
void set_defaults()
{
    /* Reset the RCC clock configuration */
    RCC->CR |= RCC_CR_MSION;

    RCC->CFGR = 0x00000000;

    /* Reset HSEON, CSSON , HSION, and PLLON bits */
    RCC->CR &= ~(  RCC_CR_HSEON
                 | RCC_CR_CSSON
                 | RCC_CR_HSION
                 | RCC_CR_PLLON
                 | RCC_CR_PLLSAI1ON
                 | RCC_CR_PLLSAI2ON);

    /* Reset PLLCFGR register */
    RCC->PLLCFGR = 0x00001000;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Disable all interrupts */
    RCC->CIER = 0x00000000;
}
#endif



void __attribute__ ((isr)) init()
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

#if 0
    set_defaults();
#endif

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
MAYBE_WEAK void NMI_Handler             () { while (1); }
MAYBE_WEAK void HardFault_Handler       () { while (1); }
MAYBE_WEAK void SVCall_Handler          () { while (1); }
MAYBE_WEAK void PendSV_Handler          () { while (1); }
MAYBE_WEAK void SysTick_Handler         () { while (1); }
/* External interrupt handlers follow */
MAYBE_WEAK void SPI0_IRQHandler         () { while (1); }
MAYBE_WEAK void SPI1_IRQHandler         () { while (1); }
MAYBE_WEAK void UART0_IRQHandler        () { while (1); }
MAYBE_WEAK void UART1_IRQHandler        () { while (1); }
MAYBE_WEAK void UART2_IRQHandler        () { while (1); }
MAYBE_WEAK void Reserved1_IRQHandler    () { while (1); }
#ifdef LPC81X
MAYBE_WEAK void I2C_IRQHandler          () { while (1); }
#endif
#ifdef LPC82X
MAYBE_WEAK void I2C1_IRQHandler         () { while (1); }
MAYBE_WEAK void I2C0_IRQHandler         () { while (1); }
#endif
MAYBE_WEAK void SCT_IRQHandler          () { while (1); }
MAYBE_WEAK void MRT_IRQHandler          () { while (1); }
MAYBE_WEAK void CMP_IRQHandler          () { while (1); }
MAYBE_WEAK void WDT_IRQHandler          () { while (1); }
MAYBE_WEAK void BOD_IRQHandler          () { while (1); }
MAYBE_WEAK void WKT_IRQHandler          () { while (1); }
#ifdef LPC82X
MAYBE_WEAK void ISE_ADC_SEQA_IRQHandler () { while (1); }
MAYBE_WEAK void ISE_ADC_SEQB_IRQHandler () { while (1); }
MAYBE_WEAK void ISE_ADC_THCMP_IRQHandler() { while (1); }
MAYBE_WEAK void ISE_ADC_OVR_IRQHandler  () { while (1); }
MAYBE_WEAK void ISE_SDMA_IRQHandler     () { while (1); }
MAYBE_WEAK void ISE_I2C2_IRQHandler     () { while (1); }
MAYBE_WEAK void ISE_I2C3_IRQHandler     () { while (1); }
#endif
MAYBE_WEAK void Reserved11_IRQHandler   () { while (1); }
MAYBE_WEAK void PININT0_IRQHandler      () { while (1); }
MAYBE_WEAK void PININT1_IRQHandler      () { while (1); }
MAYBE_WEAK void PININT2_IRQHandler      () { while (1); }
MAYBE_WEAK void PININT3_IRQHandler      () { while (1); }
MAYBE_WEAK void PININT4_IRQHandler      () { while (1); }
MAYBE_WEAK void PININT5_IRQHandler      () { while (1); }
MAYBE_WEAK void PININT6_IRQHandler      () { while (1); }
MAYBE_WEAK void PININT7_IRQHandler      () { while (1); }
#endif
