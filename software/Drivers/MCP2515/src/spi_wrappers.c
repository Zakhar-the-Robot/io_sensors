// *************************************************************************
//
// Copyright (c) 2022 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "spi_wrappers.h"
#include "MCP2515lib_cfg.h"
#include "stm32f4xx_hal_conf.h"


void SPI_Tx(uint8_t data) {
    HAL_SPI_Transmit(SPI_CAN, &data, 1, SPI_TIMEOUT);
}

void SPI_TxBuffer(uint8_t *buffer, uint8_t length) {
    HAL_SPI_Transmit(SPI_CAN, buffer, length, SPI_TIMEOUT);
}

uint8_t SPI_Rx(void) {
    uint8_t retVal;
    HAL_SPI_Receive(SPI_CAN, &retVal, 1, SPI_TIMEOUT);
    return retVal;
}

void SPI_RxBuffer(uint8_t *buffer, uint8_t length) {
    HAL_SPI_Receive(SPI_CAN, buffer, length, SPI_TIMEOUT);
}
