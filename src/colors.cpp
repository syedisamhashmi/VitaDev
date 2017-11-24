//
//  colors.hpp
//  cpptest
//
//  Created by Isam Hashmi on 11/18/17.
//  Copyright © 2017 Isam Hashmi. All rights reserved.
//

#include "colors.hpp"
namespace colors
{
    uint32_t RGBA832(unsigned char r, unsigned char g,
                     unsigned char b, unsigned char a)
    {
        return ( (((a)&0xFF)<<24) | (((b)&0xFF)<<16) |
                (((g)&0xFF)<<8) | (((r)&0xFF)<<0) );
    };
    
    uint16_t RGB16(unsigned char r, unsigned char g, unsigned char b)
    {
        return ( ( ((r)&0x1F)<<11) | (((g)&0x3F)<<5) | (((b)&0x1F)<<0) );
    };
    
    uint32_t RED32 =  RGBA832(255, 0,   0,   255);
    uint32_t GREEN32 = RGBA832(0,   255, 0,   255);
    uint32_t BLUE32 =  RGBA832(0,   0,   255, 255);
    uint32_t CYAN32 =  RGBA832(0,   255, 255, 255);
    uint32_t LIME32 = RGBA832(50,  205, 50,  255);
    uint32_t PURPLE32 = RGBA832(147, 112, 219, 255);
    uint32_t WHITE32 = RGBA832(255, 255, 255, 255);
    uint32_t BLACK32 = RGBA832(0,   0,   0,   255);
    
    uint16_t RED16 =  RGB16(255, 0,   0);
    uint16_t GREEN16 = RGB16(0,   255, 0);
    uint16_t BLUE16 =  RGB16(0,   0,   255);
    uint16_t CYAN16 =  RGB16(0,   255, 255);
    uint16_t LIME16 = RGB16(50,  205, 50);
    uint16_t PURPLE16 = RGB16(147, 112, 219);
    uint16_t WHITE16 = RGB16(255, 255, 255);
    uint16_t BLACK16 = RGB16(0,   0,   0);

}

