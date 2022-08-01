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

#include <stdio.h>
#include "FreeRTOS.h"
#include "app_main.h"
#include "cmsis_os2.h"
#include "communication/qcan.h"
#include "gpio.h"
#include "i2c.h"
#include "log.h"
#include "portable.h"
#include "registers.h"
#include "sensors/obstacles.h"
#include "sensors/photoresistor.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "svr_types.h"
#include "task.h"
#include "usart.h"


void app_main() {
    HAL_UART_Transmit(&huart1, (uint8_t *) "START\r\n", 8, 10);
    log_info("Start");
    RegistersInit();
    SVR_reg_t regs[16] = {0};

    log_debug("I2C ready? %d", HAL_I2C_GetState(&hi2c1));
    HAL_I2C_EnableListen_IT(&hi2c1);  // https://community.st.com/s/question/0D50X00009sThWGSA0/how-hal-i2c-slave-works

    StartSensorPhotoresistor();
    StartSensorObstacles();
    StartCommQcan();

    while (1) {
        SVR_Dump(&registers, 0, registers.regs_ammount, regs, false, 1000);
        log_debug("    \tCMD: 0x%x\tMODE: 0x%x\tD_cm: %u|%u|%u \tLIGHT: 0x%x 0x%x",
                  regs[REG_CMD],
                  regs[REG_MODE],
                  regs[REG_DIST_L],
                  regs[REG_DIST_C],
                  regs[REG_DIST_R],
                  regs[REG_LIGHT_HI],
                  regs[REG_LIGHT_LO]);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
