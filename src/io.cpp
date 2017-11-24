//
//  io.cpp
//  cpptest
//
//  Created by Isam Hashmi on 11/19/17.
//  Copyright © 2017 Isam Hashmi. All rights reserved.
//
#include <psp2/touch.h>
#include <psp2/ctrl.h>

#include "io.hpp"

SceCtrlData pad;
SceTouchData touch;

namespace io
{
    SceCtrlData pad;
    SceTouchData touch;
    void getio()
    {
        sceCtrlPeekBufferPositive(0, &pad, 1);
    }
}
