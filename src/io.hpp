//
//  io.hpp
//  cpptest
//
//  Created by Isam Hashmi on 11/19/17.
//  Copyright © 2017 Isam Hashmi. All rights reserved.
//

#ifndef io_hpp
#define io_hpp

#include <stdio.h>

#include <psp2/touch.h>
#include <psp2/ctrl.h>

namespace io
{
    extern SceCtrlData pad;
    extern SceTouchData touch;
    
    void getio();
    
}


#endif /* io_hpp */
