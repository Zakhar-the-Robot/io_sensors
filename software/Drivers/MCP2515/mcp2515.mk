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

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

C_SOURCES += \
${mkfile_dir}/src/spi_wrappers.c \
${mkfile_dir}/src/CANSPI.c \
${mkfile_dir}/src/MCP2515.c

C_INCLUDES += -I${mkfile_dir}/include

