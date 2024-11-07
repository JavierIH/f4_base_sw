#include<serial.h>

#define BUFFER_SIZE 64
char rx_buffer[BUFFER_SIZE]; // Buffer de recepción

void serial_setup(void){
    rcc_periph_clock_enable(RCC_USART2);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_DMA1);

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

    usart_set_baudrate(USART2, 115200);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
    usart_enable(USART2);

    dma_stream_reset(DMA1, DMA_STREAM6);
    dma_enable_memory_increment_mode(DMA1, DMA_STREAM6);
    dma_set_peripheral_size(DMA1, DMA_STREAM6, DMA_SxCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_STREAM6, DMA_SxCR_MSIZE_8BIT);
    dma_set_priority(DMA1, DMA_STREAM6, DMA_SxCR_PL_VERY_HIGH);
    dma_set_transfer_mode(DMA1, DMA_STREAM6, DMA_SxCR_DIR_MEM_TO_PERIPHERAL);
    dma_set_peripheral_address(DMA1, DMA_STREAM6, (uint32_t)&USART2_DR);
    dma_channel_select(DMA1, DMA_STREAM6, DMA_SxCR_CHSEL_4);
    usart_enable_tx_dma(USART2);
}

void serial_send(const char *data) {
    dma_set_memory_address(DMA1, DMA_STREAM6, (uint32_t)data);
    dma_set_number_of_data(DMA1, DMA_STREAM6, strlen(data));
    dma_enable_transfer_complete_interrupt(DMA1, DMA_STREAM6);
    dma_enable_stream(DMA1, DMA_STREAM6);
}









