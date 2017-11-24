#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <psp2/kernel/sysmem.h>
#include <psp2/gxm.h>
namespace utils
{
    
    unsigned int align_mem(unsigned int addr, unsigned int align);
    int abs(int val);
    void printc(int x, int y, uint32_t color, char c);
    void prints(int x, int y, uint32_t color, const char *string);
    void printsf(int x, int y, uint32_t color, const char *s, ...);
    
    
}


#endif
