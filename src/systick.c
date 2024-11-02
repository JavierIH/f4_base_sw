#include<systick.h>


void systick_setup(void){
    systick_set_reload(rcc_ahb_frequency / 1000 - 1);  //1 ms
    systick_set_frequency(1000, 180000000);
    systick_counter_enable();
    systick_interrupt_enable();
}





