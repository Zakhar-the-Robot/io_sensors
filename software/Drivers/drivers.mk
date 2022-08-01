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
Drivers/HC-SR04/hc-sr04.c \
Drivers/MCP2515/src/CANSPI.c \
Drivers/MCP2515/src/MCP2515.c

C_INCLUDES += \
-IDrivers/MCP2515/include \
-IDrivers/HC-SR04
