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

#include <stdio.h>

#ifdef STM32F411xE
#include "stm32f411xe.h"
#endif

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

int32_t hcsr04_getdistance_cm(HCSR04dev_t *dev, HCSR04_mode_t mode);

#ifdef __cplusplus
}
#endif
