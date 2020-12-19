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

#include "hc-sr04.h"
#include <stdio.h>

#define SOUND_SPEED_M_PER_S 343
#define SOUND_SPEED_M_PER_MS 0.343
#define SOUND_SPEED_M_PER_US 0.000343
#define SOUND_SPEED_CM_PER_US 0.0343
#define CM_TO_US(CM) (2 * CM / SOUND_SPEED_CM_PER_US)
#define US_TO_CM(US) (US * SOUND_SPEED_CM_PER_US / 2)


#define ERROR_GENERIC (-1)
#define ERROR_TIMEOUT (-2)
#define ERROR_WRONG_STATE (-3)


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

int32_t hcsr04_getdistance_cm(HCSR04dev_t *dev, HCSR04_mode_t mode) {
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
