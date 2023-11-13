#include "matrix.h"
#include "uart.h"

void matrix_init() {
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN_Msk; // GPIOA clock enable
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk; // GPIOB clock enable
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN_Msk; // GPIOC clock enable

    /* Set driver's pins as GPIO output */
    GPIOA->MODER = (GPIOA->MODER & (~GPIO_MODER_MODE2_Msk)) | (1 << GPIO_MODER_MODE2_Pos); // C2 - PA2
    GPIOA->MODER = (GPIOA->MODER & (~GPIO_MODER_MODE3_Msk)) | (1 << GPIO_MODER_MODE3_Pos); // C7 - PA3
    GPIOA->MODER = (GPIOA->MODER & (~GPIO_MODER_MODE4_Msk)) | (1 << GPIO_MODER_MODE4_Pos); // SDA - PA4
    GPIOA->MODER = (GPIOA->MODER & (~GPIO_MODER_MODE5_Msk)) | (1 << GPIO_MODER_MODE5_Pos); // C5 - PA5
    GPIOA->MODER = (GPIOA->MODER & (~GPIO_MODER_MODE6_Msk)) | (1 << GPIO_MODER_MODE6_Pos); // C4 - PA6
    GPIOA->MODER = (GPIOA->MODER & (~GPIO_MODER_MODE7_Msk)) | (1 << GPIO_MODER_MODE7_Pos); // C3 - PA7
    GPIOA->MODER = (GPIOA->MODER & (~GPIO_MODER_MODE15_Msk)) | (1 << GPIO_MODER_MODE15_Pos); // C1 - PA15

    GPIOB->MODER = (GPIOB->MODER & (~GPIO_MODER_MODE0_Msk)) | (1 << GPIO_MODER_MODE0_Pos); // C6 - PB0
    GPIOB->MODER = (GPIOB->MODER & (~GPIO_MODER_MODE1_Msk)) | (1 << GPIO_MODER_MODE1_Pos); // SCK - PB1
    GPIOB->MODER = (GPIOB->MODER & (~GPIO_MODER_MODE2_Msk)) | (1 << GPIO_MODER_MODE2_Pos); // C0 - PB2

    GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODE3_Msk)) | (1 << GPIO_MODER_MODE3_Pos); // RST - PC3
    GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODE4_Msk)) | (1 << GPIO_MODER_MODE4_Pos); // LAT - PC4
    GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODE5_Msk)) | (1 << GPIO_MODER_MODE5_Pos); // SB - PC5

    /* Set GPIO output speed as very high speed */
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & (~GPIO_OSPEEDR_OSPEED2_Msk)) | (3 << GPIO_OSPEEDR_OSPEED2_Pos); // C2 - PA2
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & (~GPIO_OSPEEDR_OSPEED3_Msk)) | (3 << GPIO_OSPEEDR_OSPEED3_Pos); // C7 - PA3
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & (~GPIO_OSPEEDR_OSPEED4_Msk)) | (3 << GPIO_OSPEEDR_OSPEED4_Pos); // SDA - PA4
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & (~GPIO_OSPEEDR_OSPEED5_Msk)) | (3 << GPIO_OSPEEDR_OSPEED5_Pos); // C5 - PA5
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & (~GPIO_OSPEEDR_OSPEED6_Msk)) | (3 << GPIO_OSPEEDR_OSPEED6_Pos); // C4 - PA6
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & (~GPIO_OSPEEDR_OSPEED7_Msk)) | (3 << GPIO_OSPEEDR_OSPEED7_Pos); // C3 - PA7
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & (~GPIO_OSPEEDR_OSPEED15_Msk)) | (3 << GPIO_OSPEEDR_OSPEED15_Pos); // C1 - PA15

    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED0_Msk)) | (3 << GPIO_OSPEEDR_OSPEED0_Pos); // C6 - PB0
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED1_Msk)) | (3 << GPIO_OSPEEDR_OSPEED1_Pos); // SCK - PB1
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & (~GPIO_OSPEEDR_OSPEED2_Msk)) | (3 << GPIO_OSPEEDR_OSPEED2_Pos); // C0 - PB2

    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & (~GPIO_OSPEEDR_OSPEED3_Msk)) | (3 << GPIO_OSPEEDR_OSPEED3_Pos); // RST - PC3
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & (~GPIO_OSPEEDR_OSPEED4_Msk)) | (3 << GPIO_OSPEEDR_OSPEED4_Pos); // LAT - PC4
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & (~GPIO_OSPEEDR_OSPEED5_Msk)) | (3 << GPIO_OSPEEDR_OSPEED5_Pos); // SB - PC5


    /* Initialization */
    RST(0);
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);

    // pause(20000 * 100 * 4); // Wait 100ms, 1 instruction takes 12.5 ns for sysclock 80MHz 
    pause(100000000); // Wait 100ms, 1 instruction takes 12.5 ns for sysclock 80MHz

    /* Set RST */
    RST(1);

    init_bank0();
}

/* Generate at SCK 1 pulse postive => down, wait, up, wait, down, wait */
void pulse_SCK() {
    SCK(0);
    pause(25);
    SCK(1);
    pause(25);
    SCK(0);
    pause(25);
}

/* Generate at LAT 1 pulse negative => up, wait, down, wait, up, wait */
void pulse_LAT() {
    LAT(1);
    pause(25);
    LAT(0);
    pause(25);
    LAT(1);
    pause(25);
}

/* deactivate all rows */
void deactivate_rows() {
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

/* Activate the specified row */
void activate_row(int row) {
    switch (row)
    {
    case 0:
        ROW0(1);
        break;
    case 1:
        ROW1(1);
        break;
    case 2:
        ROW2(1);
        break;
    case 3:
        ROW3(1);
        break;
    case 4:
        ROW4(1);
        break;
    case 5:
        ROW5(1);
        break;
    case 6:
        ROW6(1);
        break;
    case 7:
        ROW7(1);
        break;
    } 
}  

/* Pause, time in ns*/
void pause(int time) {
    const int sys_period = 12.5;

    for (int i = 0; i < (int)(time/sys_period); i++){
        asm volatile("nop");
    }   
    
    // for (int i = 0; i < nb_boucle; i++){
    //     asm volatile("nop");
    // }   

}

/* Send a byte to the user-specified bank */
void send_byte(uint8_t val, int bank) {
    SB(bank);

    // don't use unsigned int !
    for(int i = 7; i >= 0; i--){
        SDA((val >> i) & 0x01); // MSB
        pulse_SCK();
    }
}

/* Set a row of the matrix */
void mat_set_row(int row, const rgb_color *val) {
    for(int i = 7; i >= 0; i--){
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);

        // it takes time to deactive all rows, so we do it in advance instead of doing it just before pulse_LAT() 
        if(i == 6) deactivate_rows(); 
    }

    pulse_LAT();

    activate_row(row);
}

/* Initialisation of bank0 */
void init_bank0() {
    // for bank0, 6 bits * 24 leds / 8 bits = 18
    for(int cpt = 0; cpt < 18; cpt++) {
        send_byte(0xFF, 0);
    }

    pulse_LAT();
}

/* Test Linear Gradient Color*/
void test_pixels() {
    static state_color state = RED2GREEN;

    rgb_color colors[8]; // 8 leds per line

    switch (state)
    {
    case RED2GREEN:
        for(int i = 255; i >= 0; i--){
            for(int j = 0; j < 8; j++){
                colors[j].r = i;
                colors[j].g = 255 - i;
                colors[j].b = 0x00;
            }

            for(int j = 0; j < 8; j++){
                mat_set_row(j, colors);
            }
        }
        state = GREEN2BLUE;
        break;
    
    case GREEN2BLUE:
        for(int i = 255; i >= 0; i--){
            for(int j = 0; j < 8; j++){
                colors[j].r = 0x00;
                colors[j].g = i;
                colors[j].b = 255 - i;
            }

            for(int j = 0; j < 8; j++){
                mat_set_row(j, colors);
            }
        }
        state = BLUE2RED;
        break;

    case BLUE2RED:
        for(int i = 255; i >= 0; i--){
            for(int j = 0; j < 8; j++){
                colors[j].r = 255 - i;
                colors[j].g = 0x00;
                colors[j].b = i;
            }

            for(int j = 0; j < 8; j++){
                mat_set_row(j, colors);
            }
        }
        state = RED2GREEN;
        break;
    }
}
    
void display_image_static(uint8_t *data_start, uint8_t *data_end, int data_size){
    uint8_t dataImageStatic[data_size];
    rgb_color colors[8];

    for(uint8_t * ptr = data_start; ptr < data_end; ptr++){
        dataImageStatic[ptr - data_start] = *ptr;
    }

    for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            colors[i].r = dataImageStatic[8 * 3 * j + i * 3 + 0];
            colors[i].g = dataImageStatic[8 * 3 * j + i * 3 + 1];
            colors[i].b = dataImageStatic[8 * 3 * j + i * 3 + 2];
        }

        mat_set_row(j, colors);
    }
}

// many_frames = 2.4M octets, 38400 -> 3840 trame/s -> 10.25 min
// final.bin = 1 min
void print_trame() {
    static int row = 0;
    rgb_color colors[8];

    for(int i = 0; i < 8; i++){
        colors[i].r = frame[8 * 3 * row + i * 3 + 0];
        colors[i].g = frame[8 * 3 * row + i * 3 + 1];
        colors[i].b = frame[8 * 3 * row + i * 3 + 2];
    }

    mat_set_row(row, colors);

    row++;
    if(row == 8){
        row = 0;
    }
}