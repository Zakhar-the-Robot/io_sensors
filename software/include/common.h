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
#include <Arduino.h>
#include "ArduinoLog.h"


/* Peripherals and sw configs
   ********************************************************************* */

#define DEBUG 1
#define LOG_LEVEL LOG_LEVEL_NOTICE
// #define LOG_LEVEL LOG_LEVEL_VERBOSE
#define PRINT_REGS 0
#define PRINT_ANGLES 0

#define REGS_NUM 8
// i2c
#define DEVICE_I2C_ADDRESS 0x2b

/*********************************************************************** Peripherals and sw configs*/
/* Macros
   ********************************************************************* */
#define SIZE_ARR(x) (sizeof(x) / sizeof(x[0]))

#define ESP_RETURN_RES_ON_ERROR(x) \
    do {                           \
        esp_err_t res = (x);       \
        if (res != ESP_OK)         \
            return res;            \
    } while (0)

/*********************************************************************** Macros*/
/* Registers
   ********************************************************************* */

enum reristers {
    REG_CMD = 0x00,
    REG_ARG = 0x01,
    REG_LIGHT_LO = 0x02,
    REG_LIGHT_HI = 0x03,
};

/*********************************************************************** Registers*/
/* Pinout
   ********************************************************************* */
#define PIN_I2C_SDA 2
#define PIN_I2C_SCL 3

#define PIN_SENSOR_PHOTORES A3
#define PIN_LED 13

/*********************************************************************** Pinout*/
/* Commands
   ********************************************************************* */

#define CMD_NONE (-1U)
#define CMD_DONE (0)

#define CMD_FORWARD 119
#define CMD_BACKWARD 115
#define CMD_LEFT 97
#define CMD_RIGHT 100
#define CMD_SHIVER 0x71
#define CMD_STOP_KB 0x20
#define CMD_STOP 0xA0

#define CMD_SPEED0 0x30
#define CMD_SPEED1 0x31
#define CMD_SPEED2 0x32
#define CMD_SPEED3 0x33

#define CMD_MPU_CALIBRATE 99

#define CMD_TEST 0x74

/*********************************************************************** Commands*/