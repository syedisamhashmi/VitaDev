#include <cstdarg>
#include <cstdio>

#include "utils.hpp"
#include "graphics.hpp"
#include "font.hpp"
#define ALIGN(x, a)    (((x) + ((a) - 1)) & ~((a) - 1))
namespace utils
{
    font::fontStyle fontType = (font::msx_font);
    unsigned int align_mem(unsigned int addr, unsigned int align)
    {
        return (((addr) + ((align) - 1)) & ~((align) - 1));
    }
    int abs(int val)
    {
        return val < 0 ? -val : val;
    }
    void printc(int x, int y, uint32_t color, char c)
    {
        
        unsigned char *font = (unsigned char *)(&fontType[c*8]);
      
        
        int i, j, pos_x, pos_y;
        for (i = 0; i < 8; ++i) {
            pos_y = y + i*2;
            for (j = 0; j < 8; ++j) {
                pos_x = x + j*2;
                if ((*font & (128 >> j))) {
                    graphics::draw_pixel(pos_x + 0, pos_y + 0, color);
                    graphics::draw_pixel(pos_x + 1, pos_y + 0, color);
                    graphics::draw_pixel(pos_x + 0, pos_y + 1, color);
                    graphics::draw_pixel(pos_x + 1, pos_y + 1, color);
                }
            }
            ++font;
        }
    }
    void prints(int x, int y, uint32_t color, const char *string)
    {
        if (string == NULL) return;
        
        int startx = x;
        const char *s = string;
        
        while (*s) {
            if (*s == '\n') {
                x = startx;
                y += 16;
            } else if (*s == ' ') {
                x += 16;
            } else if(*s == '\t') {
                x += 16*4;
            } else {
                printc(x, y, color, *s);
                x += 16;
            }
            ++s;
        }
    }
    void printsf(int x, int y, uint32_t color, const char *s, ...)
    {
        char buf[256];
        va_list argptr;
        va_start(argptr, s);
        vsnprintf(buf, sizeof(buf), s, argptr);
        va_end(argptr);
        prints(x, y, color, buf);
    }

    
    
    
    
    
}
