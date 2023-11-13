#include <stdint.h>
#include "CMSIS/stm32l475xx.h"
#include "led.h"

#define ADDR_BASE_AHB2 0x40021000
#define OFFSET_RCC_AHB2ENR 0x0000004C

#define ADDR_BASE_GPIOB 0x48000400
#define OFFSET_GPIOB_MODER 0x00
#define OFFSET_GPIOB_BSRR 0x18

#define ADDR_BASE_GPIOC 0x48000800
#define OFFSET_GPIOC_MODER 0x00
#define OFFSET_GPIOC_BSRR 0x18


void led_init() {
    /* Use volatile to avoid optimisation */
    // volatile uint32_t *RCC_AHB2ENR = (volatile uint32_t *)(ADDR_BASE_AHB2 + OFFSET_RCC_AHB2ENR); 
    // volatile uint32_t *GPIOB_MODER = (volatile uint32_t *)(ADDR_BASE_GPIOB + OFFSET_GPIOB_MODER);
    // volatile uint32_t *GPIOC_MODER = (volatile uint32_t *)(ADDR_BASE_GPIOC + OFFSET_GPIOC_MODER);

    // *RCC_AHB2ENR |= 1 << 1; // GPIOB clock enable
    // *RCC_AHB2ENR |= 1 << 2; // GPIOC clock enable
    // *GPIOB_MODER = (*GPIOB_MODER & ~(3 << 28)) | (1 << 28); // PB14 output 
    // *GPIOC_MODER &= ~(3 << 18); // PC9 input, led off

    /* Use CMSIS */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN_Msk;
    GPIOB->MODER = (GPIOB->MODER & (~GPIO_MODER_MODE14_Msk)) | (1 << GPIO_MODER_MODE14_Pos);
    GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk; 
}

void led_g_on() {
    // volatile uint32_t *GPIOB_BSRR = (volatile uint32_t *)(ADDR_BASE_GPIOB + OFFSET_GPIOB_BSRR);

    // *GPIOB_BSRR |= 1 << 14; // PB14 on 

    /* Use CMSIS */
    GPIOB->BSRR = GPIO_BSRR_BS14_Msk; // BRR is a virtual register, don't use '|=', make sure that the action is atomic
}

void led_g_off() {
    // volatile uint32_t *GPIOB_BSRR = (volatile uint32_t *)(ADDR_BASE_GPIOB + OFFSET_GPIOB_BSRR);

    // *GPIOB_BSRR |= 1 << 30; // PB14 off

    /* Use CMSIS */
    GPIOB->BSRR = GPIO_BSRR_BR14_Msk; 
}

void led_y_on() {
    // volatile uint32_t *GPIOC_MODER = (volatile uint32_t *)(ADDR_BASE_GPIOC + OFFSET_GPIOC_MODER);
    // volatile uint32_t *GPIOC_BSRR = (volatile uint32_t *)(ADDR_BASE_GPIOC + OFFSET_GPIOC_BSRR);

    // *GPIOC_BSRR |= 1 << 9; // PC9 yellow
    // *GPIOC_MODER = (*GPIOC_MODER & ~(3 << 18)) | (1 << 18); // PC9 output 

    /* Use CMSIS */
    GPIOC->BSRR = GPIO_BSRR_BS9_Msk;
    GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODE9_Msk)) | (1 << GPIO_MODER_MODE9_Pos);
}

void led_b_on() {
    // volatile uint32_t *GPIOC_MODER = (volatile uint32_t *)(ADDR_BASE_GPIOC + OFFSET_GPIOC_MODER);
    // volatile uint32_t *GPIOC_BSRR = (volatile uint32_t *)(ADDR_BASE_GPIOC + OFFSET_GPIOC_BSRR);

    // *GPIOC_BSRR |= 1 << 25; // PC9 blue
    // *GPIOC_MODER = (*GPIOC_MODER & ~(3 << 18)) | (1 << 18); // PC9  output 

    /* Use CMSIS */
    GPIOC->BSRR = GPIO_BSRR_BR9_Msk;
    GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODE9_Msk)) | (1 << GPIO_MODER_MODE9_Pos);
}

void led_y_b_off() {
    // volatile uint32_t *GPIOC_MODER = (volatile uint32_t *)(ADDR_BASE_GPIOC + OFFSET_GPIOC_MODER);

    // *GPIOC_MODER &= ~(3 << 18); // PC9 input

    /* Use CMSIS */
    GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk; 
}

void led(state_led state_led) {
    switch (state_led)
    {
    case LED_OFF:
        led_g_off();
        led_y_b_off();
        
        break;

    case LED_GREEN:
        led_y_b_off();
        led_g_on();

        break;

    case LED_YELLOW:
        led_g_off();
        led_y_on();

        break;
    
    case LED_BLUE:
        led_g_off();
        led_b_on();

        break;
    }
}