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
#include <stm32f4xx.h>
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"

#include "main.h"
#include "registers.h"
#include "hc-sr04.h"


#define SOUND_SPEED_M_PER_S 343
#define SOUND_SPEED_M_PER_MS 0.343
#define SOUND_SPEED_M_PER_US 0.000343
#define SOUND_SPEED_CM_PER_US 0.0343
#define CM_TO_US(CM) (2 * CM / SOUND_SPEED_CM_PER_US)
#define US_TO_CM(US) (US * SOUND_SPEED_CM_PER_US / 2)


#define ERROR_GENERIC (-1)
#define ERROR_TIMEOUT (-2)
#define ERROR_WRONG_STATE (-3)
#define CFG_POLL_FREQ_HZ 10
#define MAX_DISTANCE_CM 200


typedef struct {
    GPIO_TypeDef *trig_port;
    uint16_t trig_pin;
    GPIO_TypeDef *echo_port;
    uint16_t echo_pin;
    uint32_t max_distance_cm;
} HCSR04dev_t;

typedef enum {
    HCSR04_MODE_SINGLE,
    HCSR04_MODE_MEDIAN,
    // HCSR04_MODE_KALMAN
} HCSR04_mode_t;

static HCSR04dev_t sonar_l = {
        .trig_port       = SON_TRIG_L_D5_GPIO_Port,
        .trig_pin        = SON_TRIG_L_D5_Pin,
        .echo_port       = SON_ECHO_L_D4_GPIO_Port,
        .echo_pin        = SON_ECHO_L_D4_Pin,
        .max_distance_cm = MAX_DISTANCE_CM};

static HCSR04dev_t sonar_c = {
        .trig_port       = SON_TRIG_C_D7_GPIO_Port,
        .trig_pin        = SON_TRIG_C_D7_Pin,
        .echo_port       = SON_ECHO_C_D6_GPIO_Port,
        .echo_pin        = SON_ECHO_C_D6_Pin,
        .max_distance_cm = MAX_DISTANCE_CM};

static HCSR04dev_t sonar_r = {
        .trig_port       = SON_TRIG_R_D11_GPIO_Port,
        .trig_pin        = SON_TRIG_R_D11_Pin,
        .echo_port       = SON_ECHO_R_D10_GPIO_Port,
        .echo_pin        = SON_ECHO_R_D10_Pin,
        .max_distance_cm = MAX_DISTANCE_CM};

static uint32_t hcsr04_millis(void) {
    return __HAL_TIM_GET_COUNTER(&htim2);
}

static void hcsr04_delay_us(uint32_t us) {
    uint32_t start = hcsr04_millis();
    while (hcsr04_millis() - start < us)
        ;  // wait for the counter to reach the us input in the parameter
}


static int32_t hcsr04_getpulsedelay_us(HCSR04dev_t *dev) {
    uint32_t start, end;
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_RESET);  // pull the TRIG pin low
    hcsr04_delay_us(2);                                                // wait for 2 us
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_SET);    // pull the TRIG pin HIGH
    hcsr04_delay_us(10);                                               // wait for 10 us
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_RESET);  // pull the TRIG pin low

    start = hcsr04_millis();
    while (!(HAL_GPIO_ReadPin(dev->echo_port, dev->echo_pin))) {
        if (hcsr04_millis() - start > CM_TO_US(dev->max_distance_cm)) {
            return ERROR_WRONG_STATE;  // no response
        }
    }

    start = hcsr04_millis();
    while (HAL_GPIO_ReadPin(dev->echo_port, dev->echo_pin) &&
           (hcsr04_millis() - start < CM_TO_US(dev->max_distance_cm)))  // while the pin is high
    {
    }
    end = hcsr04_millis();
    if ((end - start)> CM_TO_US(dev->max_distance_cm))
    {
        return ERROR_TIMEOUT;
    }

    return end - start;
}


static uint32_t hcsr04_getdistance_cm_once(HCSR04dev_t *dev) {
    int32_t res = hcsr04_getpulsedelay_us(dev);
    if (res >= 0) {
        return US_TO_CM(res);
    }
    switch (res) {
        case ERROR_TIMEOUT:
            return dev->max_distance_cm;
        default:
            return res;
    }
}


static uint32_t hcsr04_getdistance_cm_median(HCSR04dev_t *dev) {
    uint32_t data[3];
    uint32_t middle = 0;

    for (int i = 0; i < 3; i++) {
        data[i] = hcsr04_getdistance_cm_once(dev);  //save echo signal
    }

    if ((data[0] <= data[1]) && (data[0] <= data[2])) {
        middle = (data[1] <= data[2]) ? data[1] : data[2];
    } else if ((data[1] <= data[0]) && (data[1] <= data[2])) {
        middle = (data[0] <= data[2]) ? data[0] : data[2];
    } else {
        middle = (data[0] <= data[1]) ? data[0] : data[1];
    }
    return middle;
}

static int32_t hcsr04_getdistance_cm(HCSR04dev_t *dev, HCSR04_mode_t mode) {
    int val;
    switch (mode) {
        case HCSR04_MODE_SINGLE:
            val= hcsr04_getdistance_cm_once(dev);
            break;
        case HCSR04_MODE_MEDIAN:
            val= hcsr04_getdistance_cm_median(dev);
            break;
        default:
            val= 0;
            break;
    }
    return val;
}

void vTaskDistance(void *params) {
    int32_t dl,dc,dr;
    HAL_TIM_Base_Start(&htim2);
    while (1) {

        dl = hcsr04_getdistance_cm(&sonar_l, HCSR04_MODE_MEDIAN);
        if (dl>=0) {
            SVR_Set(&registers, REG_DIST_L, dl, false, pdMS_TO_TICKS(1000));
        }

        dc = hcsr04_getdistance_cm(&sonar_c, HCSR04_MODE_MEDIAN);
        if (dc>=0) {
            SVR_Set(&registers, REG_DIST_C, dc, false, pdMS_TO_TICKS(1000));
        }

        dr = hcsr04_getdistance_cm(&sonar_r, HCSR04_MODE_MEDIAN);
        if (dr>=0) {
            SVR_Set(&registers, REG_DIST_R, dr, false, pdMS_TO_TICKS(1000));
        }

        vTaskDelay(pdMS_TO_TICKS(1000 / CFG_POLL_FREQ_HZ));
        taskYIELD();
    }
}
