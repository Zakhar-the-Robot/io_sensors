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

#include <cstdint>
#include <cstdio>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "gpio.h"
#include "log.h"
#include "registers.h"
#include "stm32f4xx_hal.h"
#include "task.h"
#include "tim.h"

#define CFG_POLL_FREQ_HZ 10
#define MAX_DISTANCE_CM 400
#define SOUND_SPEED_M_PER_S 343
#define SOUND_SPEED_M_PER_MS 0.343
#define SOUND_SPEED_M_PER_US 0.000343
#define SOUND_SPEED_CM_PER_US 0.0343
#define MAX_DELAY_MS (2 * MAX_DISTANCE_CM / SOUND_SPEED_CM_PER_US)

uint32_t local_time, sensor_time;
uint32_t distance;

void delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(&htim2, 0);  // set the counter value a 0
    while (__HAL_TIM_GET_COUNTER(&htim2) < us)
        ;  // wait for the counter to reach the us input in the parameter
}

uint32_t hcsr04_getdelay_ms(void) {
    local_time = 0;
    HAL_GPIO_WritePin(SONIC_TRIG_NUCLEO_D12_GPIO_Port, SONIC_TRIG_NUCLEO_D12_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low
    delay_us(2);                                                              // wait for 2 us

    HAL_GPIO_WritePin(SONIC_TRIG_NUCLEO_D12_GPIO_Port, SONIC_TRIG_NUCLEO_D12_Pin, GPIO_PIN_SET);    // pull the TRIG pin HIGH
    delay_us(10);                                                             // wait for 10 us
    HAL_GPIO_WritePin(SONIC_TRIG_NUCLEO_D12_GPIO_Port, SONIC_TRIG_NUCLEO_D12_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low

    // read the time for which the pin is high

    while (!(HAL_GPIO_ReadPin(SONIC_ECHO_NUCLEO_D11_GPIO_Port, SONIC_ECHO_NUCLEO_D11_Pin))) {
        // printf(".\r\n");
    }
    while (HAL_GPIO_ReadPin(SONIC_ECHO_NUCLEO_D11_GPIO_Port, SONIC_ECHO_NUCLEO_D11_Pin))  // while the pin is high
    {
        local_time++;  // measure time for which the pin is high
        delay_us(1);
        if (local_time >= MAX_DELAY_MS)
            break;
    }
    delay_us(MAX_DELAY_MS);
    return local_time;
}

uint32_t hcsr04_getdistance_cm_once(void) {
    return (hcsr04_getdelay_ms() * SOUND_SPEED_CM_PER_US / 2);
}

uint32_t hcsr04_getdistance_cm(uint32_t n_measurements) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < n_measurements; i++) {
        sum += hcsr04_getdistance_cm_once();
        delay_us(1000);
    }
    return (sum / n_measurements);
}

uint32_t hcsr04_getdistance_cm_median() {
    uint32_t data[3];
    uint32_t middle = 0;

    for (int i = 0; i < 3; i++) {
        data[i] = hcsr04_getdelay_ms();  //save echo signal
    }

    if ((data[0] <= data[1]) && (data[0] <= data[2])) {
        middle = (data[1] <= data[2]) ? data[1] : data[2];
    } else if ((data[1] <= data[0]) && (data[1] <= data[2])) {
        middle = (data[0] <= data[2]) ? data[0] : data[2];
    } else {
        middle = (data[0] <= data[1]) ? data[0] : data[1];
    }

    return (middle * SOUND_SPEED_CM_PER_US / 2);
}

void vTaskDistance(void *params) {
    HAL_TIM_Base_Start(&htim2);
    int d;
    log_info("Start");
    while (1) {
        d = hcsr04_getdistance_cm_median();
        // log_debug("Distance: %u cm", d);
        SVR_Set(&registers, REG_DIST, d, false, pdMS_TO_TICKS(1000));
        vTaskDelay(pdMS_TO_TICKS(1000 / CFG_POLL_FREQ_HZ));
        taskYIELD();
    }
}