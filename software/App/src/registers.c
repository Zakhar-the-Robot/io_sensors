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

#include "registers.h"
#include "SharedVirtualRegisters.h"

SharedVirtualRegisters_t registers;

int RegistersInit(){
    SVR_Init(&registers, 8);
    return 0;
}

