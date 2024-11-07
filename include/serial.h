#ifndef _SERIAL_H
#define _SERIAL_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>

#include <string.h>

void serial_setup(void);
void serial_send(const char *data);

#endif //_SERIAL_H