//
//  colors.hpp
//  cpptest
//
//  Created by Isam Hashmi on 11/18/17.
//  Copyright © 2017 Isam Hashmi. All rights reserved.
//

#ifndef COLORS_H
#define COLORS_H
#include <cstdint>
#include "filesystem.hpp"
namespace colors
{
    uint32_t RGBA832(unsigned char r, unsigned char g,
                     unsigned char b, unsigned char a);
    uint16_t RGB16(unsigned char r, unsigned char g, unsigned char b);
    
    uint32_t pixelToRGBA832(filesystem::pixel p);
    extern uint32_t RED32;
    extern uint32_t GREEN32;
    extern uint32_t BLUE32;
    extern uint32_t CYAN32;
    extern uint32_t LIME32;
    extern uint32_t PURPLE32;
    extern uint32_t WHITE32;
    extern uint32_t BLACK32;
    extern uint32_t CLEAR32;
    
    extern uint16_t RED16;
    extern uint16_t GREEN16;
    extern uint16_t BLUE16;
    extern uint16_t CYAN16;
    extern uint16_t LIME16;
    extern uint16_t PURPLE16;
    extern uint16_t WHITE16;
    extern uint16_t BLACK16;

    
}

#endif /* colors_h */
