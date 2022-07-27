// *************************************************************************
//
// Copyright (c) 2022 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************


#include "stm32f4xx_hal.h"

long unsigned log_get_time(void) {
    return HAL_GetTick();
}
