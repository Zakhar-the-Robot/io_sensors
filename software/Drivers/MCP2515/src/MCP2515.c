// Based on https://github.com/eziya/STM32_SPI_MCP2515
// Copyright (c) 2022 Andrei Gramakov. All rights reserved.

#include "MCP2515.h"
#include "MCP2515lib_cfg.h"
#include "main.h"
#include "spi_wrappers.h"

#define MCP2515_CS_HIGH() HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_SET)
#define MCP2515_CS_LOW() HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_RESET)


/* MCP2515 초기화 */
bool MCP2515_Initialize(void) {
    MCP2515_CS_HIGH();

    uint8_t loop = 10;

    do {
        /* SPI Ready */
        if (HAL_SPI_GetState(SPI_CAN) == HAL_SPI_STATE_READY)
            return true;

        loop--;
    } while (loop > 0);

    return false;
}

bool MCP2515_SetConfigMode(void) {
    /* CANCTRL Register Configuration*/
    MCP2515_WriteByte(MCP2515_CANCTRL, 0x80);

    uint8_t loop = 10;

    do {
        if ((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x80)
            return true;

        loop--;
    } while (loop > 0);

    return false;
}

bool MCP2515_SetNormalMode(void) {
    /* CANCTRL Register Normal */
    MCP2515_WriteByte(MCP2515_CANCTRL, 0x00);

    uint8_t loop = 10;

    do {
        if ((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x00)
            return true;

        loop--;
    } while (loop > 0);

    return false;
}

bool MCP2515_SetSleepMode(void) {
    /* CANCTRL Register Sleep */
    MCP2515_WriteByte(MCP2515_CANCTRL, 0x20);

    uint8_t loop = 10;
    do {
        if ((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x20)
            return true;
        loop--;
    } while (loop > 0);

    return false;
}

/* MCP2515 SPI-Reset */
void MCP2515_Reset(void) {
    MCP2515_CS_LOW();

    SPI_Tx(MCP2515_RESET);

    MCP2515_CS_HIGH();
}

uint8_t MCP2515_ReadByte(uint8_t address) {
    uint8_t retVal;

    MCP2515_CS_LOW();

    SPI_Tx(MCP2515_READ);
    SPI_Tx(address);
    retVal = SPI_Rx();

    MCP2515_CS_HIGH();

    return retVal;
}

void MCP2515_ReadRxSequence(uint8_t instruction, uint8_t *data, uint8_t length) {
    MCP2515_CS_LOW();

    SPI_Tx(instruction);
    SPI_RxBuffer(data, length);

    MCP2515_CS_HIGH();
}

void MCP2515_WriteByte(uint8_t address, uint8_t data) {
    MCP2515_CS_LOW();

    SPI_Tx(MCP2515_WRITE);
    SPI_Tx(address);
    SPI_Tx(data);

    MCP2515_CS_HIGH();
}

void MCP2515_WriteByteSequence(uint8_t startAddress, uint8_t endAddress, uint8_t *data) {
    MCP2515_CS_LOW();

    SPI_Tx(MCP2515_WRITE);
    SPI_Tx(startAddress);
    SPI_TxBuffer(data, (endAddress - startAddress + 1));

    MCP2515_CS_HIGH();
}

void MCP2515_LoadTxSequence(uint8_t instruction, uint8_t *idReg, uint8_t dlc, uint8_t *data) {
    MCP2515_CS_LOW();

    SPI_Tx(instruction);
    SPI_TxBuffer(idReg, 4);
    SPI_Tx(dlc);
    SPI_TxBuffer(data, dlc);

    MCP2515_CS_HIGH();
}

void MCP2515_LoadTxBuffer(uint8_t instruction, uint8_t data) {
    MCP2515_CS_LOW();

    SPI_Tx(instruction);
    SPI_Tx(data);

    MCP2515_CS_HIGH();
}

void MCP2515_RequestToSend(uint8_t instruction) {
    MCP2515_CS_LOW();

    SPI_Tx(instruction);

    MCP2515_CS_HIGH();
}

uint8_t MCP2515_ReadStatus(void) {
    uint8_t retVal;

    MCP2515_CS_LOW();

    SPI_Tx(MCP2515_READ_STATUS);
    retVal = SPI_Rx();

    MCP2515_CS_HIGH();

    return retVal;
}

uint8_t MCP2515_GetRxStatus(void) {
    uint8_t retVal;

    MCP2515_CS_LOW();

    SPI_Tx(MCP2515_RX_STATUS);
    retVal = SPI_Rx();

    MCP2515_CS_HIGH();

    return retVal;
}

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data) {
    MCP2515_CS_LOW();

    SPI_Tx(MCP2515_BIT_MOD);
    SPI_Tx(address);
    SPI_Tx(mask);
    SPI_Tx(data);

    MCP2515_CS_HIGH();
}
