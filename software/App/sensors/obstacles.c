// *************************************************************************
//
// Copyright (c) 2022 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"

#include "main.h"
#include "obstacles.h"
#include "registers.h"

#include "hc-sr04.h"


static HCSR04dev_t sonar_l = { .trig_port       = SON_TRIG_L_D5_GPIO_Port,
                               .trig_pin        = SON_TRIG_L_D5_Pin,
                               .echo_port       = SON_ECHO_L_D4_GPIO_Port,
                               .echo_pin        = SON_ECHO_L_D4_Pin,
                               .max_distance_cm = MAX_DISTANCE_CM };

static HCSR04dev_t sonar_c = { .trig_port       = SON_TRIG_C_D7_GPIO_Port,
                               .trig_pin        = SON_TRIG_C_D7_Pin,
                               .echo_port       = SON_ECHO_C_D6_GPIO_Port,
                               .echo_pin        = SON_ECHO_C_D6_Pin,
                               .max_distance_cm = MAX_DISTANCE_CM };

static HCSR04dev_t sonar_r = { .trig_port       = SON_TRIG_R_D11_GPIO_Port,
                               .trig_pin        = SON_TRIG_R_D11_Pin,
                               .echo_port       = SON_ECHO_R_D10_GPIO_Port,
                               .echo_pin        = SON_ECHO_R_D10_Pin,
                               .max_distance_cm = MAX_DISTANCE_CM };

void vTaskDistance(void *params)
{
    int32_t dl, dc, dr;
    HAL_TIM_Base_Start(&htim2);
    while (1) {

        dl = hcsr04_getdistance_cm(&sonar_l, HCSR04_MODE_MEDIAN);
        if (dl >= 0) { SVR_Set(&registers, REG_DIST_L, dl, false, pdMS_TO_TICKS(1000)); }

        dc = hcsr04_getdistance_cm(&sonar_c, HCSR04_MODE_MEDIAN);
        if (dc >= 0) { SVR_Set(&registers, REG_DIST_C, dc, false, pdMS_TO_TICKS(1000)); }

        dr = hcsr04_getdistance_cm(&sonar_r, HCSR04_MODE_MEDIAN);
        if (dr >= 0) { SVR_Set(&registers, REG_DIST_R, dr, false, pdMS_TO_TICKS(1000)); }

        vTaskDelay(pdMS_TO_TICKS(1000 / CFG_POLL_FREQ_HZ));
        taskYIELD();
    }
}

void StartSensorObstacles() { xTaskCreate(vTaskDistance, "vTaskDistance", 2048, NULL, 5, NULL); }
