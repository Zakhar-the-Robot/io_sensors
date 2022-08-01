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
App/communication/qcan.c \
App/log_cfg.c \
App/printf.c \
App/registers.c \
App/sensors/obstacles.c \
App/sensors/photoresistor.c \
App/app_main.c

C_INCLUDES += \
-IApp


# CXX_SOURCES += \

