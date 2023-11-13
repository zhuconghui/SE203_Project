#include "uart.h"
#include "led.h"
#include "CMSIS/stm32l475xx.h"

/* Initialisation of USART1 */
void uart_init(int baudrate) {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; // Turn on clock of GPIOB in bus AHB2
    GPIOB->MODER = (GPIOB->MODER &~GPIO_MODER_MODE6_Msk ) | ( 0b10 << GPIO_MODER_MODE6_Pos); // set PB6 like mode AF
    GPIOB->MODER = (GPIOB->MODER &~GPIO_MODER_MODE7_Msk ) | ( 0b10 << GPIO_MODER_MODE7_Pos); // set PB7 like mode AF
    GPIOB->AFR[0] = (GPIOB->AFR[0] &~GPIO_AFRL_AFSEL6_Msk) | (0b0111 << GPIO_AFRL_AFSEL6_Pos); // PB6 as AF7 mode (USART1_TX)
    GPIOB->AFR[0] = (GPIOB->AFR[0] &~GPIO_AFRL_AFSEL7_Msk) | (0b0111 << GPIO_AFRL_AFSEL7_Pos); // PB7 as AF7 mode (USART1_RX)
    
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Turn on clock of USART1 in bus APB2
    RCC->CCIPR = (RCC->CCIPR &~RCC_CCIPR_USART1SEL_Msk) | ( 0b00 << RCC_CCIPR_USART1SEL_Pos); // Select type of clock PCLK for USART1

    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST; // reset USART1 register
    RCC->APB2RSTR = (RCC->APB2RSTR &~RCC_APB2RSTR_USART1RST_Msk) | (0b0 << RCC_APB2RSTR_USART1RST_Pos); // set USART1 register
    
    // note: next configurations needs to be done before USART enable, located at the end
    USART1->BRR = (USART1->BRR &~USART_BRR_DIV_FRACTION_Msk) | (80000000/baudrate << USART_BRR_DIV_FRACTION_Pos); //set bps
    USART1->CR1 = (USART1->CR1 &~USART_CR1_OVER8_Msk) | (0b0<<USART_CR1_OVER8_Pos); // set oversampling16 mode for USART1 OVER8=0
    USART1->CR1 = (USART1->CR1 &~USART_CR1_M1_Msk) | (0b0<<USART_CR1_M1_Pos) | (0<<USART_CR1_M0_Pos); // set M[1] in 0 and M[0] in 0, for 8 bits data length
    USART1->CR1 = (USART1->CR1 &~USART_CR1_PCE_Msk) | (0b0<<USART_CR1_PCE_Pos); //sets parity control disabled
    USART1->CR2 = (USART1->CR2 &~USART_CR2_STOP_Msk) | (0b00<<USART_CR2_STOP_Pos); //sets stop bits to 1 bit
    USART1->CR1 |= USART_CR1_UE; // USART enable
    USART1->CR1 |= USART_CR1_RE; // USART enable Receiver
    USART1->CR1 |= USART_CR1_TE; // USART enable Transmitter
}

/* 
    Send data 
    Type of data: char(uint8_t)
*/
void uart_putchar(uint8_t c) {
    while((USART1->ISR & USART_ISR_TXE_Msk) == 0) {} // When transmit data register is not empty, wait 

    USART1->TDR = c; // Send data
}

/* 
    Read data received 
    Type of data: char(uint8_t)
*/
uint8_t uart_getchar() {
    // while((USART1->ISR & USART_ISR_RXNE) == 0) {} // When data is not received, wait

    // return (uint8_t) (USART1->RDR & USART_RDR_RDR);

    while (!(USART1->ISR & USART_ISR_RXNE));
    return (uint8_t) (USART1->RDR & USART_RDR_RDR);
}

/*
    Send data
    Type of data: string
*/
void uart_puts(const char *s) {
    // uint8_t i = 0;

    // while(s[i] != '\0') {
    //     uart_putchar(s[i]);
    //     i++;
    // }

    for(; *s != '\0'; s++){
        uart_putchar(*s);
    }
}

/*
    Read data received
    Type of data: string
*/
void uart_gets(char *s, size_t size) {
    size_t i = 0;

    while(i < size){
        s[i] = (char)(uart_getchar());
        i++;
    }

    s[size] = '\0';
}

uint8_t frame[192]; 

void USART1_IRQHandler(){
    if (USART1->ISR & USART_ISR_ORE || USART1->ISR & USART_ISR_FE) {// Overrun error or Framing error
        USART1->RQR |= USART_RQR_RXFRQ_Msk; 
        USART1->ICR |= USART_ICR_ORECF_Msk;
        USART1->ICR |= USART_ICR_FECF_Msk; 
        return; // return and wait for next
    }

    static int index = 0;
    uint8_t byte_received = 0;

    // byte_received = uart_getchar();
    if(USART1->ISR & USART_ISR_RXNE) byte_received = (uint8_t) (USART1->RDR & USART_RDR_RDR);

    if(byte_received == 0xFF || index == 192) {
		index = 0;
	} 
    else {
        frame[index] = byte_received;
		index++;
	}
}

// Setting for interruption
void uart_irq_led_init  (void){

    USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Interrupt Enable
    
    //enable nvic irq
    NVIC_EnableIRQ(USART1_IRQn);
}