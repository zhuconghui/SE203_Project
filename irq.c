#include "irq.h"


#define MAKE_DEFAULT_HANDLER(x_IRQHandler) \
    void __attribute__((weak))x_IRQHandler(void) { \
    	__disable_irq(); \
        while(1); \
    }

MAKE_DEFAULT_HANDLER(NMI_Handler);
MAKE_DEFAULT_HANDLER(HardFault_Handler);
MAKE_DEFAULT_HANDLER(MemManage_Handler);
MAKE_DEFAULT_HANDLER(BusFault_Handler);
MAKE_DEFAULT_HANDLER(UsageFault_Handler);
MAKE_DEFAULT_HANDLER(SVC_Handler);
MAKE_DEFAULT_HANDLER(PendSV_Handler);
MAKE_DEFAULT_HANDLER(SysTick_Handler);
MAKE_DEFAULT_HANDLER(WWDG_IRQHandler);
MAKE_DEFAULT_HANDLER(PVD_PVM_IRQHandler);
MAKE_DEFAULT_HANDLER(TAMP_STAMP_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC_WKUP_IRQHandler);
MAKE_DEFAULT_HANDLER(FLASH_IRQHandler);
MAKE_DEFAULT_HANDLER(RCC_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI0_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI1_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI2_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI3_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI4_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel1_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel2_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel3_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel4_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel5_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel6_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA1_Channel7_IRQHandler);
MAKE_DEFAULT_HANDLER(ADC1_2_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_TX_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_RX0_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_RX1_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN1_SCE_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI9_5_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_BRK_TIM15_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_UP_TIM16_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_TRG_COM_TIM17_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM1_CC_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM2_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM3_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM4_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C1_EV_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C1_ER_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C2_EV_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C2_ER_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI1_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI2_IRQHandler);
MAKE_DEFAULT_HANDLER(USART1_IRQHandler);
MAKE_DEFAULT_HANDLER(USART2_IRQHandler);
MAKE_DEFAULT_HANDLER(USART3_IRQHandler);
MAKE_DEFAULT_HANDLER(EXTI15_10_IRQHandler);
MAKE_DEFAULT_HANDLER(RTC_Alarm_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT3_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_BRK_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_UP_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_TRG_COM_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM8_CC_IRQHandler);
MAKE_DEFAULT_HANDLER(ADC3_IRQHandler);
MAKE_DEFAULT_HANDLER(FMC_IRQHandler);
MAKE_DEFAULT_HANDLER(SDMMC1_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM5_IRQHandler);
MAKE_DEFAULT_HANDLER(SPI3_IRQHandler);
MAKE_DEFAULT_HANDLER(UART4_IRQHandler);
MAKE_DEFAULT_HANDLER(UART5_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM6_DAC_IRQHandler);
MAKE_DEFAULT_HANDLER(TIM7_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel1_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel2_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel3_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel4_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel5_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT0_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT1_IRQHandler);
MAKE_DEFAULT_HANDLER(DFSDM1_FLT2_IRQHandler);
MAKE_DEFAULT_HANDLER(COMP_IRQHandler);
MAKE_DEFAULT_HANDLER(LPTIM1_IRQHandler);
MAKE_DEFAULT_HANDLER(LPTIM2_IRQHandler);
MAKE_DEFAULT_HANDLER(OTG_FS_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel6_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2_Channel7_IRQHandler);
MAKE_DEFAULT_HANDLER(LPUART1_IRQHandler);
MAKE_DEFAULT_HANDLER(QUADSPI_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C3_EV_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C3_ER_IRQHandler);
MAKE_DEFAULT_HANDLER(SAI1_IRQHandler);
MAKE_DEFAULT_HANDLER(SAI2_IRQHandler);
MAKE_DEFAULT_HANDLER(SWPMI1_IRQHandler);
MAKE_DEFAULT_HANDLER(TSC_IRQHandler);
MAKE_DEFAULT_HANDLER(LCD_IRQHandler);
MAKE_DEFAULT_HANDLER(AES_IRQHandler);
MAKE_DEFAULT_HANDLER(RNG_IRQHandler);
MAKE_DEFAULT_HANDLER(FPU_IRQHandler);
MAKE_DEFAULT_HANDLER(CRS_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C4_EV_IRQHandler);
MAKE_DEFAULT_HANDLER(I2C4_ER_IRQHandler);
MAKE_DEFAULT_HANDLER(DCMI_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN2_TX_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN2_RX0_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN2_RX1_IRQHandler);
MAKE_DEFAULT_HANDLER(CAN2_SCE_IRQHandler);
MAKE_DEFAULT_HANDLER(DMA2D_IRQHandler);

extern uint32_t _stack;
extern uint32_t _start; // _start is defined as a label in init.c

void *vector_table_init[] __attribute__((section(".vtor_init"), aligned(512))) = {
    // Stack and Reset Handler
    &_stack,            /* Top of stack */
    &_start,             /* Reset handler */

    // ARM internal exceptions
    NMI_Handler,        /* NMI handler */
    HardFault_Handler,  /* Hard Fault handler */
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVC_Handler,        /* SVC handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pending SVC handler */
    SysTick_Handler    /* SysTick hanlder */

};

void * const vector_table[] __attribute__((section(".vtor"),aligned(512))) = { // vector table is aligned to 256 bytes because bits[8:0] must be 0
    // Stack and Reset Handler
    &_stack,            /* Top of stack  (initial value of the SP register) */
    &_start,             /* Reset handler (initial value of the PC register) */

    // ARM internal exceptions
    NMI_Handler,        /* NMI handler */
    HardFault_Handler,  /* Hard Fault handler */
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    0,                  /* Reserved */
    SVC_Handler,        /* SVC handler */
    0,                  /* Reserved */
    0,                  /* Reserved */
    PendSV_Handler,     /* Pending SVC handler */
    SysTick_Handler,    /* SysTick hanlder */

    // STM32L475 External interrupts
    WWDG_IRQHandler,         /* Watchdog IRQ */
    PVD_PVM_IRQHandler,      /* ... */
    TAMP_STAMP_IRQHandler,   /* ... */
    RTC_WKUP_IRQHandler,     /* ... */
    FLASH_IRQHandler,        /* ... */
    RCC_IRQHandler,          /* ... */
    EXTI0_IRQHandler,        /* ... */
    EXTI1_IRQHandler,        /* ... */
    EXTI2_IRQHandler,        /* ... */
    EXTI3_IRQHandler,        /* ... */
    EXTI4_IRQHandler,        /* ... */
    DMA1_Channel1_IRQHandler,/* ... */
    DMA1_Channel2_IRQHandler,/* ... */
    DMA1_Channel3_IRQHandler,/* ... */
    DMA1_Channel4_IRQHandler,/* ... */
    DMA1_Channel5_IRQHandler,/* ... */
    DMA1_Channel6_IRQHandler,/* ... */
    DMA1_Channel7_IRQHandler,/* ... */
    ADC1_2_IRQHandler,       /* ... */
    CAN1_TX_IRQHandler,      /* ... */
    CAN1_RX0_IRQHandler,     /* ... */
    CAN1_RX1_IRQHandler,     /* ... */
    CAN1_SCE_IRQHandler,     /* ... */
    EXTI9_5_IRQHandler,      /* ... */
    TIM1_BRK_TIM15_IRQHandler,/* ... */
    TIM1_UP_TIM16_IRQHandler,/* ... */
    TIM1_TRG_COM_TIM17_IRQHandler,/* ... */
    TIM1_CC_IRQHandler,      /* ... */
    TIM2_IRQHandler,         /* ... */
    TIM3_IRQHandler,         /* ... */
    TIM4_IRQHandler,         /* ... */
    I2C1_EV_IRQHandler,      /* ... */
    I2C1_ER_IRQHandler,      /* ... */
    I2C2_EV_IRQHandler,      /* ... */
    I2C2_ER_IRQHandler,      /* ... */
    SPI1_IRQHandler,         /* ... */
    SPI2_IRQHandler,         /* ... */
    USART1_IRQHandler,       /* ... */
    USART2_IRQHandler,       /* ... */
    USART3_IRQHandler,       /* ... */
    EXTI15_10_IRQHandler,    /* ... */
    RTC_Alarm_IRQHandler,    /* ... */
    DFSDM1_FLT3_IRQHandler,  /* ... */
    TIM8_BRK_IRQHandler,     /* ... */
    TIM8_UP_IRQHandler,      /* ... */
    TIM8_TRG_COM_IRQHandler, /* ... */
    TIM8_CC_IRQHandler,      /* ... */
    ADC3_IRQHandler,         /* ... */
    FMC_IRQHandler,          /* ... */
    SDMMC1_IRQHandler,       /* ... */
    TIM5_IRQHandler,         /* ... */
    SPI3_IRQHandler,         /* ... */
    UART4_IRQHandler,        /* ... */
    UART5_IRQHandler,        /* ... */
    TIM6_DAC_IRQHandler,     /* ... */
    TIM7_IRQHandler,         /* ... */
    DMA2_Channel1_IRQHandler,/* ... */
    DMA2_Channel2_IRQHandler,/* ... */
    DMA2_Channel3_IRQHandler,/* ... */
    DMA2_Channel4_IRQHandler,/* ... */
    DMA2_Channel5_IRQHandler,/* ... */
    DFSDM1_FLT0_IRQHandler,  /* ... */
    DFSDM1_FLT1_IRQHandler,  /* ... */
    DFSDM1_FLT2_IRQHandler,  /* ... */
    COMP_IRQHandler,         /* ... */
    LPTIM1_IRQHandler,       /* ... */
    LPTIM2_IRQHandler,       /* ... */
    OTG_FS_IRQHandler,       /* ... */ 
    DMA2_Channel6_IRQHandler,/* ... */
    DMA2_Channel7_IRQHandler,/* ... */
    LPUART1_IRQHandler,      /* ... */
    QUADSPI_IRQHandler,      /* ... */
    I2C3_EV_IRQHandler,      /* ... */
    I2C3_ER_IRQHandler,      /* ... */
    SAI1_IRQHandler,         /* ... */
    SAI2_IRQHandler,         /* ... */
    SWPMI1_IRQHandler,       /* ... */
    TSC_IRQHandler,          /* ... */
    LCD_IRQHandler,          /* ... */
    AES_IRQHandler,          /* ... */
    RNG_IRQHandler,          /* ... */
    FPU_IRQHandler,          /* ... */
    CRS_IRQHandler,          /* ... */
    I2C4_EV_IRQHandler,      /* ... */
    I2C4_ER_IRQHandler,      /* ... */
    DCMI_IRQHandler,         /* ... */
    CAN2_TX_IRQHandler,      /* ... */
    CAN2_RX0_IRQHandler,     /* ... */
    CAN2_RX1_IRQHandler,     /* ... */
    CAN2_SCE_IRQHandler,     /* ... */
    DMA2D_IRQHandler,        /* ... */
};

void irq_init(){
    SCB->VTOR = (uint32_t)vector_table;
    // __enable_irq();
}
