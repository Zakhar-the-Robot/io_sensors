// *************************************************************************
//
// Copyright (c) 2022 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "qcan.h"
#include "CANSPI.h"
#include "FreeRTOS.h"
#include "registers.h"
#include "task.h"


static void taskPresence() {
    uCAN_MSG txMessage;
    txMessage.frame.idType = 0;
    txMessage.frame.id     = 0x400;
    txMessage.frame.dlc    = 3;
    txMessage.frame.data0  = 0;
    txMessage.frame.data1  = 2;
    txMessage.frame.data2  = 0;
    txMessage.frame.data3  = 0;
    txMessage.frame.data4  = 0;
    txMessage.frame.data5  = 0;
    txMessage.frame.data6  = 0;
    txMessage.frame.data7  = 0;
    while (1) {
        CANSPI_Transmit(&txMessage);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void taskData() {
    SVR_reg_t regs[16] = {0};

    uCAN_MSG txMessage;
    txMessage.frame.idType = 0;
    txMessage.frame.id     = 0x401;
    txMessage.frame.dlc    = 5;

    while (1) {
        SVR_Dump(&registers, 0, registers.regs_ammount, regs, false, 1000);
        txMessage.frame.data0 = regs[REG_DIST_L];
        txMessage.frame.data1 = regs[REG_DIST_C];
        txMessage.frame.data2 = regs[REG_DIST_R];
        txMessage.frame.data3 = regs[REG_LIGHT_HI];
        txMessage.frame.data4 = regs[REG_LIGHT_LO];
        txMessage.frame.data5 = 0;
        txMessage.frame.data6 = 0;
        txMessage.frame.data7 = 0;
        CANSPI_Transmit(&txMessage);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void StartCommQcan() {
    CANSPI_Initialize();
    xTaskCreate(taskPresence, "qCanPresence", 1024, NULL, 5, NULL);
    xTaskCreate(taskData, "qCanData", 1024, NULL, 5, NULL);
}