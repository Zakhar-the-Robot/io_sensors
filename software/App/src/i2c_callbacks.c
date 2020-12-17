// *************************************************************************
//
// Copyright (c) 2020 Andrei Gramakov. All rights reserved.
//
// This file is licensed under the terms of the MIT license.
// For a copy, see: https://opensource.org/licenses/MIT
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "i2c.h"
#include "registers.h"
#include "log.h"
#include "projdefs.h"

uint8_t receiveBuffer[2];

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *I2cHandle) {
    SVR_Set(&registers, receiveBuffer[0], receiveBuffer[1], true, pdMS_TO_TICKS(1000));
    // log_debug("! Write to 0x%x: 0x%x", receiveBuffer[0], receiveBuffer[1]);
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *I2cHandle) {
    // log_debug("! Read from 0x%x: 0x%x", receiveBuffer[0], receiveBuffer[1]);
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c) {
    HAL_I2C_EnableListen_IT(hi2c);  // Restart
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode) {

    // log_warn("! Address requested");
    if (TransferDirection == I2C_DIRECTION_TRANSMIT) {
        // log_warn("ExtMaster -> This device");
        if (HAL_I2C_Slave_Sequential_Receive_IT(hi2c, receiveBuffer, 2, I2C_LAST_FRAME) != HAL_OK) {
            log_error("I2C receive error");
        }
    } else {  // I2C_DIRECTION_RECEIVE
        // log_warn("ExtMaster <- This device");
        if (HAL_I2C_Slave_Sequential_Receive_IT(hi2c, receiveBuffer, 1, I2C_LAST_FRAME) != HAL_OK) {
            log_error("I2C receive error");
        }

        SVR_Get(&registers, receiveBuffer[0], &(receiveBuffer[1]), true, pdMS_TO_TICKS(1000));
        if (HAL_I2C_Slave_Sequential_Transmit_IT(hi2c, &receiveBuffer[1], 1, I2C_LAST_FRAME) != HAL_OK) {
            log_error("I2C receive error");
        }
    }
}