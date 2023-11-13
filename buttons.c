#include "buttons.h"
#include "led.h"

void button_init(void) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN_Msk; // GPIOC clock enable
    GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODE13_Msk)); // PC13 input
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC; // EXTI13 is connected to PC13
    EXTI->IMR1 |= EXTI_IMR1_IM13_Msk; // interrupt request from line 13 is not masked
    EXTI->FTSR1 |= EXTI_FTSR1_FT13_Msk; // failing trigger enabled for line 13
    NVIC_EnableIRQ(EXTI15_10_IRQn); // enable interrupt from EXTI line 13
}

void EXTI15_10_IRQHandler() {
    EXTI->PR1 |= EXTI_PR1_PIF13_Msk; // clear pending interrupt flag
    if(GPIOB->ODR & GPIO_ODR_OD14_Msk) { // if led green on
        led_g_off();
    }
    else {
        led_g_on();    
    }
}
