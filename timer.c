#include "timer.h"
#include "uart.h"

extern uint8_t _binary_image_raw_start;
extern uint8_t _binary_image_raw_end;
extern int _binary_image_raw_size;


void timer_init(int max_us){
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN_Msk; // TIM2 clock enable
    TIM2->SR &= 0x0000; // clear update interrupt flag
    TIM2->CNT &= ~TIM_CNT_CNT; // reset counter
    TIM2->CR1 = (TIM2->CR1 &~TIM_CR1_CMS ) | ( 0b00 << TIM_CR1_CMS_Pos);  //set TM2 edge-aligned mode
    TIM2->CR1 = (TIM2->CR1 &~TIM_CR1_DIR_Msk ) | ( 0 << TIM_CR1_DIR_Pos); //set TM2 as upcounter    
    TIM2->PSC = (TIM2->PSC &~TIM_PSC_PSC ) | ( 79 << TIM_PSC_PSC_Pos);  // prescale TIM2 clock 79+1 (with reference to SYSCLK)
    TIM2->ARR = (TIM2->ARR &~TIM_ARR_ARR ) | ( max_us << TIM_ARR_ARR_Pos); //set TIM2 auto reload register
    TIM2->DIER = (TIM2->DIER &~TIM_DIER_UIE ) | ( 1 << TIM_DIER_UIE_Pos);  //enable update interrupt
    NVIC_EnableIRQ(TIM2_IRQn); // enable TIM2 interrupt
    TIM2->CR1 |= TIM_CR1_CEN_Msk; // enable timer
}

void TIM2_IRQHandler(){
    /* Flash LEDs */
    // if(GPIOB->ODR & GPIO_ODR_OD14_Msk){
    //     led_g_off();
    // } 
    // else {
    //     led_g_on();    
    // }

    print_trame();
    // display_image_static(&_binary_image_raw_start, &_binary_image_raw_end, (int)&_binary_image_raw_size);

    TIM2->SR &= 0x0000;  // Reset all flags
}