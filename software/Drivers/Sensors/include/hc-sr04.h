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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stm32f4xx.h>


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


uint32_t hcsr04_millis(void); /* not implemented */
int32_t hcsr04_getdistance_cm(HCSR04dev_t *dev, HCSR04_mode_t mode);


#ifdef __cplusplus
}
#endif