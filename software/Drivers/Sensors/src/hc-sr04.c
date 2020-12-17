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

#define SOUND_SPEED_M_PER_S 343
#define SOUND_SPEED_M_PER_MS 0.343
#define SOUND_SPEED_M_PER_US 0.000343
#define SOUND_SPEED_CM_PER_US 0.0343
#define CM_TO_US(CM) (2 * CM / SOUND_SPEED_CM_PER_US)
#define US_TO_CM(US) (US * SOUND_SPEED_CM_PER_US / 2)


static void hcsr04_delay_us(uint32_t us) {
    uint32_t start = hcsr04_millis();
    while (hcsr04_millis() - start < us)
        ;  // wait for the counter to reach the us input in the parameter
}


uint32_t hcsr04_getpulsedelay_ms(HCSR04dev_t *dev) {
    uint32_t start, end;
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_RESET);  // pull the TRIG pin low
    hcsr04_delay_us(2);                                                // wait for 2 us
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_SET);    // pull the TRIG pin HIGH
    hcsr04_delay_us(10);                                               // wait for 10 us
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_RESET);  // pull the TRIG pin low

    start = hcsr04_millis();
    while (!(HAL_GPIO_ReadPin(dev->echo_port, dev->echo_pin))) {
        if (hcsr04_millis() - start > CM_TO_US(dev->max_distance_cm)) {
            return 0;  // no response
        }
    }

    start = hcsr04_millis();
    while (HAL_GPIO_ReadPin(dev->echo_port, dev->echo_pin))  // while the pin is high
    {
        if (hcsr04_millis() - start > CM_TO_US(dev->max_distance_cm)) {
            return CM_TO_US(dev->max_distance_cm);  // no response
        }
    }
    end = hcsr04_millis();
    // hcsr04_delay_us(CM_TO_US(dev->max_distance_cm));
    return end - start;
}


static uint32_t hcsr04_getdistance_cm_once(HCSR04dev_t *dev) {
    return US_TO_CM(hcsr04_getpulsedelay_ms(dev));
}


static uint32_t hcsr04_getdistance_cm_median(HCSR04dev_t *dev) {
    uint32_t data[3];
    uint32_t middle = 0;

    for (int i = 0; i < 3; i++) {
        data[i] = hcsr04_getpulsedelay_ms(dev);  //save echo signal
    }

    if ((data[0] <= data[1]) && (data[0] <= data[2])) {
        middle = (data[1] <= data[2]) ? data[1] : data[2];
    } else if ((data[1] <= data[0]) && (data[1] <= data[2])) {
        middle = (data[0] <= data[2]) ? data[0] : data[2];
    } else {
        middle = (data[0] <= data[1]) ? data[0] : data[1];
    }
    return US_TO_CM(middle);
}

uint32_t hcsr04_getdistance_cm(HCSR04dev_t *dev, HCSR04_mode_t mode) {
    switch (mode) {
        case HCSR04_MODE_SINGLE:
            return hcsr04_getdistance_cm_once(dev);
        case HCSR04_MODE_MEDIAN:
            return hcsr04_getdistance_cm_median(dev);
        default:
            return 0;
    }
}
