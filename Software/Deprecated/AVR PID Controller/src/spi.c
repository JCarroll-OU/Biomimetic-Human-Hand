#include "spi.h"

void Initialize_SPI(void) {
    // Set the data direction register for port b
    DDRB |= (1 << MISO);                                    // Set MISO to output

    // Enable SPI in slave mode, to enable in master add | (1 << MSTR)
    SPCR |= (1 << SPE);                                     // Set SPI enable bit to 1
    SPCR |= (1 << SPIE);                                    // Enable SPI interrupts
}

uint8_t SPI_Slave_Receive(void) {
    SPI_command_buffer[SPI_command_index++] = SPDR;
    if (SPI_command_index >= MAX_SPI_BUFFER_LENGTH) {
        ClearCommandBuffer();
        return 1;
    } else return 0;
}

uint8_t SPI_Slave_Transmit(void) {
    SPDR = SPI_response_buffer[SPI_response_index++];
    if (SPI_response_index >= MAX_SPI_BUFFER_LENGTH) {
        ClearResponseBuffer();
        return 1;
    } else return 0;
}

void ClearCommandBuffer(void) {
    SPI_command_index = 0;
    for (int i = 0; i < MAX_SPI_BUFFER_LENGTH; i++)
        SPI_command_buffer[i] = SPI_CMD_DUMMY_COMMAND;
}

void ClearResponseBuffer(void) {
    SPI_response_index = 0;
    for (int i = 0; i < MAX_SPI_BUFFER_LENGTH; i++)
        SPI_response_buffer[i] = SPI_CMD_DUMMY_COMMAND;
}