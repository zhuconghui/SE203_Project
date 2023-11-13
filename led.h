#ifndef LED_H
#define LED_H


typedef enum{
	LED_OFF,
    LED_GREEN,
	LED_YELLOW,
	LED_BLUE
} state_led;

void led_init();
void led_g_on();
void led_g_off();
void led_y_on();
void led_b_on();
void led_y_b_off();
void led(state_led state_led);

#endif