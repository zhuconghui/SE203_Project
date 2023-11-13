#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "timer.h"

int fibo(int n);

// int var; // test init_bss

extern uint8_t _binary_image_raw_start;
extern uint8_t _binary_image_raw_end;
extern int _binary_image_raw_size;

int main() {
    // state_led state_led = LED_OFF; // test variable for LED
    // uint8_t byte_received; // test variable for UART
    // uint32_t sum = 0; // test variable for UART

    clocks_init();
    irq_init();
    // led_init();
    timer_init(2080); // 1000000/(60*8)
    uart_init(38400);
    uart_irq_led_init();
    matrix_init();
    // button_init();

    while(1){
        // test_pixels();
        // display_image_static(&_binary_image_raw_start, &_binary_image_raw_end, (int)&_binary_image_raw_size);
        // print_trame();

        // uart_putchar('a');
        // uart_puts("Hello World!");
        // uart_puts("Byte received: \n\r");
        // uart_putchar(uart_getchar());
        // uart_puts("\n\r");

        // uart_puts("Wait for data\n\r");
        // for(uint8_t i = 0; i < 100; i++){
        //     byte_received = uart_getchar();
        //     // uart_putchar(byte_received);
        //     sum += byte_received;
        // }
        // uart_putchar(sum >> 0);
        // uart_putchar(sum >> 8);
        // uart_putchar(sum >> 16);
        // uart_putchar(sum >> 24);

        // uart_puts("\n\r");


        
        // led_g_on();

        // for (int i=0; i<5; i++){
        //     asm volatile("nop");
        // }

        // led_g_off();

        // led_y_on();
        // led_b_on();
        // led_y_b_off();

        // led(state_led);
        
        // if      (state_led == LED_OFF)      state_led = LED_GREEN;
        // else if (state_led == LED_GREEN)    state_led = LED_YELLOW;
        // else if (state_led == LED_YELLOW)   state_led = LED_BLUE;
        // else if (state_led == LED_BLUE)     state_led = LED_GREEN;

        // for (int i=0; i<100; i++){
        //     asm volatile("nop");
        // }
    }

    return 0;
}

int fibo(int n) {
    int t1 = 0, t2 = 1, nextTerm = 0;
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else {
        for (int i = 2; i <= n; i++) {
            nextTerm = t1 + t2;
            t1 = t2;
            t2 = nextTerm;
        }
        return nextTerm;
    }
}