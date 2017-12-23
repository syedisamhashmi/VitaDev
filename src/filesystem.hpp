//
//  filesystem.h
//  cpptest
//
//  Created by Isam Hashmi on 11/18/17.
//  Copyright © 2017 Isam Hashmi. All rights reserved.
//

#ifndef filesystem_h
#define filesystem_h

#include <stdio.h>
#include <png.h>
#include <string>
#include <psp2/types.h>
#include <psp2/kernel/sysmem.h>
//#include "graphics.hpp"
namespace filesystem
{
    typedef enum {NOT_PRELOADED, IDLE_ANIMATION,  RIGHT_RUN_ANIMATION, LEFT_RUN_ANIMATION} preloaded_animations;
    
    
    class Header
    {
        public:
            unsigned int height;
            unsigned int width;
            unsigned int states;
            Header(unsigned int height, unsigned int width, unsigned int states);
            Header()
            {
                this->height = 0;
                this->width = 0;
                this->states = 0;
            };
    };
    class pixel
    {
        public:
            unsigned char red;
            unsigned char green;
            unsigned char blue;
            unsigned char alpha;
            pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
            pixel();
    };
    class Texture
    {
        public:
            filesystem::preloaded_animations preloaded;
            filesystem::Header header;
            pixel** pixels;
            void format(unsigned int height, unsigned int width, unsigned int states);
            Texture(unsigned int height, unsigned int width, unsigned int states);
    };
   
    
    
    Texture* loadFile(std::string filename);
    
    filesystem::Texture* loadFile_multiThread(std::string filename);
    int read(SceSize args, void* argp);
    filesystem::Header* readHeader(SceUID file);
    filesystem::Texture* preload(filesystem::preloaded_animations animation);
    
    void preloadTiles();   
}


#endif /* filesystem_h */
