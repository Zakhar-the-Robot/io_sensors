# *************************************************************************
#
# Copyright (c) 2022 Andrei Gramakov. All rights reserved.
#
# This file is licensed under the terms of the MIT license.  
# For a copy, see: https://opensource.org/licenses/MIT
#
# site:    https://agramakov.me
# e-mail:  mail@agramakov.me
#
# *************************************************************************

C_SOURCES += \
App/communication/i2c_callbacks.c \
App/communication/CANSPI.c \
App/communication/MCP2515.c \
App/mics/printf.c \
App/registers.c \
App/sensors/hc-sr04.c \
App/sensors/photoresistor.c \
log_cfg.c \
app_main.c

C_INCLUDES += \
-IApp


# CXX_SOURCES += \

