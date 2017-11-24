//
//  filesystem.c
//  cpptest
//
//  Created by Isam Hashmi on 11/18/17.
//  Copyright © 2017 Isam Hashmi. All rights reserved.
//



#include <psp2/io/fcntl.h>
#include <psp2/io/dirent.h>
#include <psp2/kernel/threadmgr.h>


#include <inttypes.h>
#include <cstring>

#include "filesystem.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include "graphics.hpp"
#include "preloaded.hpp"
namespace filesystem
{
    Texture::Texture(unsigned int height, unsigned int width, unsigned int states)
    {
        this->format(height, width, states);
    }
    void Texture::format(unsigned int height, unsigned int width, unsigned int states)
    {
        this->header.height = height;
        this->header.width = width;
        this->header.states = states;
        this->pixels = new pixel*[this->header.height];
        for(unsigned int i = 0; i < this->header.height; i++)
        {
            this->pixels[i] = new pixel[this->header.width];
        }
    }
    Texture* loadFile(std::string filename) //Good for small files
    {
        
        SceUID fileUID = sceIoOpen(filename.c_str(), SCE_O_RDONLY, 0777); //Open file
        
        filesystem::Header* fileHeader = readHeader(fileUID);
        
        
        filesystem::Texture* temp = new Texture(fileHeader->height, fileHeader->width, fileHeader->states);
        delete fileHeader;
        
        pixel** pixels = new pixel*[temp->header.height];
        for(unsigned int i = 0; i < temp->header.height; i++)
        {
            pixels[i] = new pixel[temp->header.width];
        }
        
        sceIoLseek(fileUID, sizeof(temp->header.height) + sizeof(temp->header.width) + sizeof(temp->header.states), SCE_SEEK_SET);
        long double percent = 0;
        for(unsigned int y = 0; y < temp->header.height; y++)
        {
            for(unsigned int x = 0; x < temp->header.width; x++)
            {
                
                unsigned char red, green, blue, alpha;
                sceIoRead(fileUID, &red, 1);
                sceIoRead(fileUID, &green, 1);
                sceIoRead(fileUID, &blue, 1);
                sceIoRead(fileUID, &alpha, 1);
                
                pixels[y][x].red = red;
                pixels[y][x].green = green;
                pixels[y][x].blue = blue;
                pixels[y][x].alpha = alpha;
                

                graphics::colorScreen(colors::BLACK16);
                
            }
            utils::printsf(50, 460,colors::WHITE32, "Height %u.", temp->header.height);
            utils::printsf(50, 490,colors::WHITE32, "Width %u.", temp->header.width);
            percent = (((double)y * temp->header.width) / ((double)temp->header.height*(double)temp->header.width)) * 100;
            utils::printsf(50, 520,colors::WHITE32, "Loading %s: %.2Lf%% complete.", filename.c_str(), percent)  ;
            graphics::swapFramebuffers();
        }
        temp->pixels = pixels;
        sceIoClose(fileUID);
        graphics::colorScreen(colors::BLACK16);
        graphics::swapFramebuffers();
        return temp;
    }
    
    Texture* loadFile_multiThread(std::string filename) //TODO for larger files to load into memory
    {
        SceUID thread;
        thread = sceKernelCreateThread("secondHalf", read, 0x10000, 0x10000, 0, 0, NULL);
        if (thread >= 0) {
            sceKernelStartThread(thread, filename.size(), &filename);
        }
    }
    int read(SceSize args, void* argp)
    {
        for(int x = 0; x < 10000; x++)
        {
            if(x%10000 == 0)
            utils::printsf(10 + ((x/10000)*30), 10, colors::WHITE32, "number is %d", x);
            graphics::swapFramebuffers(); //Selfmade
            sceDisplayWaitVblankStart();
        }
        
//sceKernelExitDeleteThread(1);
        return 1;
    }
    filesystem::Header::Header(unsigned int height, unsigned int width, unsigned int states)
    {
        this->height = height;
        this->width = width;
        this->states = states;
    }
    
    
    filesystem::Header* readHeader(SceUID file)
    {
        sceIoLseek(file,0, SCE_SEEK_SET);
        unsigned int height;
        sceIoRead(file, &height, 4);
        
        unsigned int width;
        sceIoRead(file, &width, 4);
        
        unsigned int states;
        sceIoRead(file, &states, 4);
        
        filesystem::Header* returnVal =  new filesystem::Header(height, width, states);
        sceIoLseek(file,0, SCE_SEEK_SET);
        return returnVal;
    }
    

    filesystem::Texture* preload(preloaded_animations animation)
    {
        filesystem::Texture* temp = new Texture(0,0,0);
        temp->preloaded = filesystem::NOT_PRELOADED;
        if(animation != filesystem::NOT_PRELOADED)
        {
            temp->preloaded = animation;
        }
        
        if(temp->preloaded != filesystem::NOT_PRELOADED)
        {
            if(temp->preloaded == filesystem::IDLE_ANIMATION)
            {
                unsigned int height = preloaded::idle[0];
                unsigned int width = preloaded::idle[4];
                unsigned char states = preloaded::idle[8];
                temp->header.height = height;
                temp->header.width = width;
                temp->header.states = states;
            }
            if(temp->preloaded == filesystem::RIGHT_RUN_ANIMATION)
            {
                
                unsigned int height = 0;
                memcpy(&height, &(preloaded::rightrun[0]), 4);
                unsigned int width = 0;
                memcpy(&width, &(preloaded::rightrun[4]), 4);
                unsigned int states = 0;
                memcpy(&states, &preloaded::rightrun[8], 4);
                temp->header.height = height;
                temp->header.width = width;
                temp->header.states = states;
            }
            
        }
        
        return temp;
    }
    
    
}
