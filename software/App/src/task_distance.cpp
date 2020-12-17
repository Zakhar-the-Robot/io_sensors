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
#include "hc-sr04.h"
#include "main.h"
#include "registers.h"
#include "stm32f4xx_hal.h"
#include "task.h"
#include "tim.h"

#define CFG_POLL_FREQ_HZ 10
#define MAX_DISTANCE_CM 101


HCSR04dev_t sonar_l = {
        .trig_port       = SON_TRIG_L_D5_GPIO_Port,
        .trig_pin        = SON_TRIG_L_D5_Pin,
        .echo_port       = SON_ECHO_L_D4_GPIO_Port,
        .echo_pin        = SON_ECHO_L_D4_Pin,
        .max_distance_cm = MAX_DISTANCE_CM};

HCSR04dev_t sonar_c = {
        .trig_port       = SON_TRIG_C_D7_GPIO_Port,
        .trig_pin        = SON_TRIG_C_D7_Pin,
        .echo_port       = SON_ECHO_C_D6_GPIO_Port,
        .echo_pin        = SON_ECHO_C_D6_Pin,
        .max_distance_cm = MAX_DISTANCE_CM};

HCSR04dev_t sonar_r = {
        .trig_port       = SON_TRIG_R_D11_GPIO_Port,
        .trig_pin        = SON_TRIG_R_D11_Pin,
        .echo_port       = SON_ECHO_R_D10_GPIO_Port,
        .echo_pin        = SON_ECHO_R_D10_Pin,
        .max_distance_cm = MAX_DISTANCE_CM};

uint32_t hcsr04_millis(void) {
    return __HAL_TIM_GET_COUNTER(&htim2);
}


void vTaskDistance(void *params) {
    uint32_t d;
    HAL_TIM_Base_Start(&htim2);
    while (1) {

        d = hcsr04_getdistance_cm(&sonar_l, HCSR04_MODE_MEDIAN);
        if (d) {
            SVR_Set(&registers, REG_DIST_L, d, false, pdMS_TO_TICKS(1000));
        }

        d = hcsr04_getdistance_cm(&sonar_c, HCSR04_MODE_MEDIAN);
        if (d) {
            SVR_Set(&registers, REG_DIST_C, d, false, pdMS_TO_TICKS(1000));
        }

        d = hcsr04_getdistance_cm(&sonar_r, HCSR04_MODE_MEDIAN);
        if (d) {
            SVR_Set(&registers, REG_DIST_R, d, false, pdMS_TO_TICKS(1000));
        }

        vTaskDelay(pdMS_TO_TICKS(1000 / CFG_POLL_FREQ_HZ));
        taskYIELD();
    }
}