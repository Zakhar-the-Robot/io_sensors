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

#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "adc.h"
#include "task.h"

#include "log.h"
#include "registers.h"

#include "photoresistor.h"


#define CFG_POLL_FREQ_HZ 10

static uint32_t GetLight()
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100000);
    return HAL_ADC_GetValue(&hadc1);
}

static void vTaskPhotoresistor(void *params)
{
    uint32_t val = 0;
    log_info("Start");
    while (1) {
        val = GetLight();
        // log_debug("Light: 0x%x", (int) val);
        SVR_Set(&registers, REG_LIGHT_HI, (val >> 8) & 0xff, false, pdMS_TO_TICKS(1000));
        SVR_Set(&registers, REG_LIGHT_LO, val & 0xff, false, pdMS_TO_TICKS(1000));
        vTaskDelay(pdMS_TO_TICKS(1000 / CFG_POLL_FREQ_HZ));
    }
}

void StartSensorPhotoresistor()
{
    xTaskCreate(vTaskPhotoresistor, "vTaskPhotoresistor", 1024, NULL, 5, NULL);
}
