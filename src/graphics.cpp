#include <cstdint>
#include <cstring>

#include <psp2/io/fcntl.h>
#include <psp2/io/dirent.h>
#include <psp2/touch.h>
#include <psp2/ctrl.h>
#include <psp2/types.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>
#include <psp2kern/kernel/suspend.h> 

#include "game.hpp"
#include "graphics.hpp"
#include "utils.hpp"
#include "filesystem.hpp"
#include "colors.hpp"
#include "preloaded.hpp"
namespace graphics
{
    //Packaged Vita2d calls
//--------------------------------
    void init()
    {
        vita2d_init();
    }
    void exit()
    {
        vita2d_fini();
    }
    void startDraw()
    {
        vita2d_start_drawing();
    }
    void endDraw()
    {
        vita2d_end_drawing();
    }
    void swapFB()
    {
        vita2d_swap_buffers();
    }
//--------------------------------
    
    void enableTouchControl()
    {
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
        sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    }
    void* gpu_alloc(SceKernelMemBlockType type, unsigned int size, SceGxmMemoryAttribFlags attributes, SceUID *uid)
    {
        void *mem;
        if (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW)
        {
            size = utils::align_mem(size, 256*1024);
        } else
        {
            size = utils::align_mem(size, 4*1024);
        }
        *uid = sceKernelAllocMemBlock("gpu_mem", type, size, NULL);
        if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
            return NULL;
        if (sceGxmMapMemory(mem, size, attributes) < 0)
            return NULL;
        return mem;
    }
    void gpu_free(SceUID uid)
    {
        void *mem = NULL;
        if (sceKernelGetMemBlockBase(uid, &mem) < 0)
            return;
        sceGxmUnmapMemory(mem);
        sceKernelFreeMemBlock(uid);
    }
    
    
    //Packaged Selfmade calls
//--------------------------------
    
    void setUp()
    {
        //TODO Turn off autodimming and turning off of screen.
       // ksceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_OLED_OFF);
       // ksceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_OLED_DIMMING);
    };
    
    void initializeFramebuffers()
    {
        int ret;
        
        SceGxmInitializeParams params;
        
        params.flags                        = 0x0;
        params.displayQueueMaxPendingCount  = 0x2; //Double buffering
        params.displayQueueCallback         = 0x0;
        params.displayQueueCallbackDataSize = 0x0;
        params.parameterBufferSize          = (16 * 1024 * 1024);
        
        /* Initialize the GXM */
        ret = sceGxmInitialize(&params);
        
        /* Setup framebuffers */
        fb[0].size        = sizeof(fb[0]);
        fb[0].pitch       = SCREEN_W;
        fb[0].pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;
        fb[0].width       = SCREEN_W;
        fb[0].height      = SCREEN_H;
        
        fb[1].size        = sizeof(fb[1]);
        fb[1].pitch       = SCREEN_W;
        fb[1].pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;
        fb[1].width       = SCREEN_W;
        fb[1].height      = SCREEN_H;
        
        /* Allocate memory for the framebuffers */
        fb[0].base = gpu_alloc(SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
                               SCREEN_W * SCREEN_H * 4, SCE_GXM_MEMORY_ATTRIB_RW, &fb_memuid[0]);
        
        if (fb[0].base == NULL)
        {
            //printf("Could not allocate memory for fb[0]. %p", fb[0].base);
            return;
        }
        
        fb[1].base = gpu_alloc(SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW,
                               SCREEN_W * SCREEN_H * 4, SCE_GXM_MEMORY_ATTRIB_RW, &fb_memuid[1]);
        
        if (fb[1].base == NULL) {
            //printf("Could not allocate memory for fb[1]. %p", fb[1].base);
            return;
        }
        
        /* Display the framebuffer 0 */
        cur_fb = 0;
        swapFramebuffers();
    }
    void freeFramebuffers()
    {
        gpu_free(fb_memuid[0]);
        gpu_free(fb_memuid[1]);
        sceGxmTerminate();
    }
    void swapFramebuffers()
    {
        sceDisplaySetFrameBuf(&fb[cur_fb], SCE_DISPLAY_SETBUF_NEXTFRAME);
        cur_fb ^= 1;
    }
    void clearScreen()
    {
        memset(fb[cur_fb].base, 0xFF, SCREEN_W*SCREEN_H*4);
    }
    void colorScreen(uint16_t color)
    {
        memset(fb[cur_fb].base, color, SCREEN_W*SCREEN_H*4);
    }
    void draw_pixel(uint32_t x, uint32_t y, uint32_t color)
    {
        ((uint32_t *)fb[cur_fb].base)[x + y*fb[cur_fb].pitch] = color;
    }
    
    
    //Loaded Texture Functions
    void draw_texture_loaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)
    {
        for(unsigned int y = 0; y < texture->header.height; y++)
        {
            for(unsigned int x = 0 ; x < texture->header.width; x++)
            {
                uint32_t pixelcolor =  colors::RGBA832(texture->pixels[y][x].red, texture->pixels[y][x].green, texture->pixels[y][x].blue, texture->pixels[y][x].alpha);
                
                game::Position pos = checkBounds(posX,posY, x, y);
                
                if(texture->pixels[y][x].alpha != 0)
                    graphics::draw_pixel(pos.x+x, pos.y+y, pixelcolor);
            }
        }
    }
    void draw_texture_loaded_scale(filesystem::Texture* texture, unsigned int posX, unsigned int posY, double newHeightScale, double newWidthScale)
    {
        int newWidth = (int)newWidthScale*texture->header.width;
        int newHeight = (int)newHeightScale*texture->header.height;
        filesystem::pixel** temp = new filesystem::pixel*[newHeight];
        for(unsigned int i = 0; i < newHeight; i++)
        {
            temp[i] = new filesystem::pixel[newWidth];
        }
        //Common resize technique.
        for(unsigned int cy = 0; cy < newHeight; cy++)
        {
            for(unsigned int cx = 0; cx < newWidth; cx++)
            {
                int nearestRow =  (int)(((double)cy / (double)newHeight) * (double)(texture->header.height));
                int nearestCol = (int)(((double)cx / (double)newWidth)  * (double)(texture->header.width));
                temp[cy][cx].red   =  texture->pixels[nearestRow][nearestCol].red;
                temp[cy][cx].green = texture->pixels[nearestRow][nearestCol].green;
                temp[cy][cx].blue  = texture->pixels[nearestRow][nearestCol].blue;
                temp[cy][cx].alpha = texture->pixels[nearestRow][nearestCol].alpha;
            }
        }
        for(unsigned int y = 0; y < newHeight; y++)
        {
            for(unsigned int x = 0 ; x < newWidth; x++)
            {
                uint32_t pixelcolor =  colors::RGBA832(temp[y][x].red, temp[y][x].green,   temp[y][x].blue, temp[y][x].alpha);
                
                //Check bounds on screen to stop crash.
                game::Position pos = checkBounds(posX,posY, x, y);
                
                if(temp[y][x].alpha != 0)
                    graphics::draw_pixel(pos.x+x, pos.y+y, pixelcolor);
            }
        }
        for(unsigned int i = 0; i < newHeight; i++) //Stop memory leak.
        {
            delete [] temp[i];
        } // Delete temp pixels after printing, and subarray.
        delete [] temp;
        //delete temp;
    }
    void draw_texture_loaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)
    {
        if(pieceNum > texture->header.states)
        {
            pieceNum = (int)(pieceNum % texture->header.states);
        }
        unsigned int startX = (pieceNum * (widthPerPiece));
        //unsigned int startY = pieceNum * heightPerPiece;
        
        filesystem::pixel temp;
        for(unsigned int y = 0; y < heightPerPiece; y++)
        {
            for(unsigned int x = 0 ; x < widthPerPiece; x++)
            {
                temp = texture->pixels[y][startX + x];
                uint32_t pixelcolor =  colors::RGBA832(temp.red, temp.green, temp.blue, temp.alpha);
                
                game::Position pos = checkBounds(posX,posY, x, y);
                if(temp.alpha != 0)
                    graphics::draw_pixel(pos.x+x, pos.y+y, pixelcolor);
            }
        }
    }
    void draw_texture_loaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)
    {
        
        filesystem::Texture* part = new filesystem::Texture(heightPerPiece,widthPerPiece, texture->header.states);
        //part->format(heightPerPiece, widthPerPiece);
        
        if(pieceNum > part->header.states)
        {
            pieceNum = (int)(pieceNum % part->header.states);
        }
        
        unsigned int startX = (pieceNum * (widthPerPiece));
        
        for(unsigned int y = 0; y < heightPerPiece; y++)
        {
            for(unsigned int x = 0 ; x < widthPerPiece; x++)
            {
                filesystem::pixel temp = texture->pixels[y][startX + x];
                uint32_t pixelcolor =  colors::RGBA832(temp.red, temp.green, temp.blue, temp.alpha);
                part->pixels[y][x] = temp;
            }
        }
        
        
        draw_texture_loaded_scale(part, posX, posY, newHeightScale, newWidthScale);
        
        for(unsigned int i = 0; i < heightPerPiece; i++) //Stop memory leak.
        {
            delete [] part->pixels[i];
        } // Delete part pixels after printing, and subarray.
        delete [] part->pixels;
        //delete part;
        
    }
    
    
    //File Texture Functions
    void draw_texture_file(std::string filename, unsigned int posX, unsigned int posY)
    {
        SceUID fileUID = sceIoOpen(filename.c_str(), SCE_O_RDONLY, 0777); //Open file
        
        //sceIoLseek(fileUID, 8, SCE_SEEK_SET); //Past 8 byte width and height header.
        
        unsigned int height;
        sceIoRead(fileUID, &height, 4);
        
        unsigned int width;
        sceIoRead(fileUID, &width, 4);
        
        filesystem::pixel temp = filesystem::pixel();
        for(unsigned int y = 0; y < height; y++)
        {
            for(unsigned int x = 0 ; x < width; x++)
            {
                sceIoRead (fileUID, &(temp.red), 1);
                sceIoRead (fileUID, &(temp.green), 1);
                sceIoRead (fileUID, &(temp.blue), 1);
                sceIoRead (fileUID, &(temp.alpha), 1);
                
                
                game::Position pos = checkBounds(posX,posY, x, y);
                
                
                uint32_t pixelcolor =  colors::RGBA832(temp.red, temp.green, temp.blue, temp.alpha);
                
                if(temp.alpha != 0)
                    graphics::draw_pixel(pos.x+x, pos.y+y, pixelcolor);
                
                temp.red = 0;
                temp.green = 0;
                temp.blue = 0;
                temp.alpha = 0;
            }
        }
        
        sceIoClose(fileUID);
        
    }
    void draw_texture_file_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)
    {
        
        SceUID fileUID = sceIoOpen(filename.c_str(), SCE_O_RDONLY, 0777); //Open file
        
        //sceIoLseek(fileUID, 8, SCE_SEEK_SET); //Past 8 byte width and height header.
        
        unsigned int height;
        sceIoRead(fileUID, &height, 4);
        
        unsigned int width;
        sceIoRead(fileUID, &width, 4);
        
        unsigned int states;
        sceIoRead(fileUID, &states, 4);
        
        
        if(pieceNum > states)
        {
            pieceNum = (int)(pieceNum % states);
        }
        
        unsigned int byteToStart = (pieceNum*widthPerPiece)*4;
        
        sceIoLseek(fileUID, byteToStart , SCE_SEEK_CUR);
        
        filesystem::pixel temp =  filesystem::pixel();
        for(unsigned int y = 0; y < heightPerPiece; y++)
        {
            for(unsigned int x = 0 ; x < widthPerPiece; x++)
            {
                sceIoRead (fileUID, &(temp.red), 1);
                sceIoRead (fileUID, &(temp.green), 1);
                sceIoRead (fileUID, &(temp.blue), 1);
                sceIoRead (fileUID, &(temp.alpha), 1);
                

                game::Position pos = checkBounds(posX,posY, x, y);
                
                
                
                uint32_t pixelcolor =  colors::RGBA832(temp.red, temp.green, temp.blue, temp.alpha);
                
                if(temp.alpha != 0)
                    graphics::draw_pixel(pos.x+x, pos.y+y, pixelcolor);
                
                temp.red = 0;
                temp.green = 0;
                temp.blue = 0;
                temp.alpha = 0;
            }
            sceIoLseek(fileUID, (width - widthPerPiece)*4 , SCE_SEEK_CUR); //Go to next height of frame
        }
        
        sceIoClose(fileUID);
    }
    void draw_texture_file_scale_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)
    {
        SceUID fileUID = sceIoOpen(filename.c_str(), SCE_O_RDONLY, 0777); //Open file
        
        //sceIoLseek(fileUID, 8, SCE_SEEK_SET); //Past 8 byte width and height header.
        
        filesystem::Header* tempHeader = filesystem::readHeader(fileUID);
        
        
        unsigned int byteToStart = (pieceNum*widthPerPiece)*4;
        
        sceIoLseek(fileUID, byteToStart , SCE_SEEK_CUR);
        
        filesystem::Texture* part = new filesystem::Texture(heightPerPiece,widthPerPiece, tempHeader->states);
        
        filesystem::pixel temp =  filesystem::pixel();
        for(unsigned int y = 0; y < heightPerPiece; y++)
        {
            for(unsigned int x = 0 ; x < widthPerPiece; x++)
            {
                sceIoRead (fileUID, &(temp.red), 1);
                sceIoRead (fileUID, &(temp.green), 1);
                sceIoRead (fileUID, &(temp.blue), 1);
                sceIoRead (fileUID, &(temp.alpha), 1);
                
                part->pixels[y][x] = temp;
                
                
                temp.red = 0;
                temp.green = 0;
                temp.blue = 0;
                temp.alpha = 0;
            }
            sceIoLseek(fileUID, (tempHeader->width - widthPerPiece)*4 , SCE_SEEK_CUR); //Go to next height of frame
        }
        draw_texture_loaded_scale(part, posX, posY, newHeightScale, newWidthScale);
        sceIoClose(fileUID);
        
    }
    
    
    //Preloaded Texture Functions
    void draw_texture_preloaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY)
    {
        if(texture->preloaded != filesystem::NOT_PRELOADED)
        {
            const unsigned char* animation_to_draw;
            if(texture->preloaded == filesystem::IDLE_ANIMATION)
            {
                animation_to_draw = preloaded::idle;
            }
            if(texture->preloaded == filesystem::RIGHT_RUN_ANIMATION)
            {
                animation_to_draw = preloaded::rightrun;
            }
            
            for(unsigned int y = 0; y < texture->header.height; y++)
            {
                for(unsigned int x = 0 ; x < texture->header.width; x++)
                {
                    unsigned long int allcolors;
                    memcpy(&allcolors, &(animation_to_draw[(12 + (y* texture->header.width) * 4) + (x*4)]), 4);
                    
                    game::Position pos = checkBounds(posX,posY, x, y);
                    if(((allcolors >> 24) & 0xFF) != 0)
                        graphics::draw_pixel(pos.x+x, pos.y+y, allcolors);
                }
            }
            
        }
    }
    void draw_texture_preloaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum)
    {
        if(pieceNum > texture->header.states)
        {
            pieceNum = (int)(pieceNum % texture->header.states);
        }
        if(texture->preloaded != filesystem::NOT_PRELOADED)
        {
            const unsigned char* animation_to_draw;
            if(texture->preloaded == filesystem::IDLE_ANIMATION)
            {
                animation_to_draw = preloaded::idle;
            }
            if(texture->preloaded == filesystem::RIGHT_RUN_ANIMATION)
            {
                animation_to_draw = preloaded::rightrun;
            }
            
            for(unsigned int y = 0; y < heightPerPiece; y++)
            {
                for(unsigned int x = 0 ; x < widthPerPiece; x++)
                {
                    unsigned long int allcolors;
                    memcpy(&allcolors, &(animation_to_draw[(12 + (pieceNum*widthPerPiece * 4) + ((y *(texture->header.width - widthPerPiece))*4 )
                                                            + (y* widthPerPiece) * 4) + (x*4)]), 4);
                    
                    game::Position pos = checkBounds(posX,posY, x, y);
                    if(((allcolors >> 24) & 0xFF) != 0)
                        graphics::draw_pixel(pos.x+x, pos.y+y, allcolors);
                }
            }
            
        }
    }
    
    void draw_texture_preloaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum)
    {
        if(pieceNum > texture->header.states)
        {
            pieceNum = (int)(pieceNum % texture->header.states);
        }
        filesystem::Texture* part = new filesystem::Texture(heightPerPiece, widthPerPiece, texture->header.states);
       
        
        if(texture->preloaded != filesystem::NOT_PRELOADED)
        {
            const unsigned char* animation_to_draw;
            if(texture->preloaded == filesystem::IDLE_ANIMATION)
            {
                animation_to_draw = preloaded::idle;
            }
            if(texture->preloaded == filesystem::RIGHT_RUN_ANIMATION)
            {
                animation_to_draw = preloaded::rightrun;
            }
            if(texture->preloaded == filesystem::LEFT_RUN_ANIMATION)
            {
                animation_to_draw = preloaded::leftrun;
            }
            
            for(unsigned int y = 0; y < heightPerPiece; y++)
            {
                for(unsigned int x = 0 ; x < widthPerPiece; x++)
                {
                    unsigned long int allcolors;
                    memcpy(&allcolors, &(animation_to_draw[(12 + (pieceNum*widthPerPiece * 4) + ((y *(texture->header.width - widthPerPiece))*4 )
                                                            + (y* widthPerPiece) * 4) + (x*4)]), 4);
                    
                    filesystem::pixel tempix = filesystem::pixel(((allcolors >> 0) & 0xFF),
                                                                 ((allcolors >> 8) & 0xFF),
                                                                 ((allcolors >> 16) & 0xFF),
                                                                 ((allcolors >> 24) & 0xFF)) ;
                    part->pixels[y][x] = tempix;
                   // graphics::draw_pixel(pos.x+x, pos.y+y, allcolors);
                }
            }
            
            
            
            draw_texture_loaded_scale(part, posX, posY, newHeightScale, newWidthScale);
           
            for(unsigned int i = 0; i < heightPerPiece; i++) //Stop memory leak.
            {
                delete [] part->pixels[i];
            } // Delete temp pixels after printing, and subarray.
            delete [] part->pixels;
            
            
        }
    }
    
    
    
    
    
    
    game::Position checkBounds(int posX, int posY, unsigned int x, unsigned int y)
    {
        game::Position temp = game::Position(0,0);
        //Check bounds on screen to stop crash.
        if(posX + x > graphics::SCREEN_W || posX > graphics::SCREEN_W)
            posX %= SCREEN_W;
        else if(posX + x < 0 || posX < 0)
        {
            posX = -posX;
            posX %= graphics::SCREEN_W;
        }
        else if(posY + y > graphics::SCREEN_H || posY > graphics::SCREEN_H)
            posY %= SCREEN_H;
        else if(posY + y < 0 || posY < 0)
            posY %= graphics::SCREEN_H;
        
        temp.x = posX;
        temp.y = posY;
        
        return temp;
        
    }
    
    
    
//--------------------------------

    
}



