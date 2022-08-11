// *************************************************************************
//
// Copyright (c) 2022 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void SPI_Tx(uint8_t data);
void SPI_TxBuffer(uint8_t *buffer, uint8_t length);
uint8_t SPI_Rx(void);
void SPI_RxBuffer(uint8_t *buffer, uint8_t length);

#ifdef __cplusplus
}
#endif
