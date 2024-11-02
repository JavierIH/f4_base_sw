#include <clock.h>
#include <systick.h>
#include <usart.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>


volatile uint32_t millis = 0;

void wait(uint32_t delay) {
    uint32_t target = millis + delay;
    while (millis < target);
}

void sys_tick_handler(void){
    millis++;
}

int main(void) {
    clock_setup();
    usart_setup();
    systick_setup();

    rcc_periph_clock_enable(RCC_GPIOA);

    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

    while (1){
        gpio_set(GPIOA, GPIO5);
        wait(100);
        gpio_clear(GPIOA, GPIO5);
        wait(100);
    }

    return 0;
}
