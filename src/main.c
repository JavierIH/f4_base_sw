#include <clock.h>
#include <systick.h>
#include <serial.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/usart.h>


volatile uint32_t millis = 0;


void wait(uint32_t delay) {
    uint32_t target = millis + delay;
    while (millis < target);
}

void sys_tick_handler(void){
    millis++;
}

char text_buffer[64];

int main(void) {
    clock_setup();
    serial_setup();

    systick_setup();

    rcc_periph_clock_enable(RCC_GPIOA);

    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
    volatile int counter = 0;
    while (1){
        gpio_set(GPIOA, GPIO5);
        wait(10);
        gpio_clear(GPIOA, GPIO5);
        wait(10);
        //usart_send_blocking(USART2, 'A');
        //serial_send(msg, sizeof(msg));
        sprintf(text_buffer, "HOLA %d \n\r", counter);
        serial_send(text_buffer);
        counter++;
    }

    return 0;
}