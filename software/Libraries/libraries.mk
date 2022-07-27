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
Libraries/SharedVirtualRegisters/src/SharedVirtualRegisters.c \
Libraries/SharedVirtualRegisters/src/svr_mux_freertos.c \
Libraries/SharedVirtualRegisters/src/svr_mux_noos.c \
Libraries/log.cx/src/log.c

C_INCLUDES += \
-ILibraries/log.cx/src \
-ILibraries/SharedVirtualRegisters/include
