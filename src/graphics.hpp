#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <psp2/types.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>

#include <vita2d.h>

#include "game.hpp"
#include "filesystem.hpp"

namespace graphics
{
    
    static int SCREEN_W = 960;
    static int SCREEN_H = 544;
    static int DISPLAY_STRIDE_IN_PIXELS = 1024;
   
    
    static SceDisplayFrameBuf fb[2];
    static SceUID fb_memuid[2];
    static int cur_fb = 0;
    
    void gpu_free(SceUID uid);
    
    
    
    //Vita2d (can not interact with selfmade)
    void init();    //Sets up framebuffers.
    void exit();     //Call before kernel exit.
    void startDraw(); //Before any drawing using Vita2d
    void endDraw(); //Before swapping using Vita2d, don't draw after this call.
    void swapFB(); //Swap Vita2d Buffers.
    
    
    void enableTouchControl();
    
    
    //Selfmade (can not interact with Vita2d)
    void setUp();
    void initializeFramebuffers(); //graphics::init(); //Vita2d
    void freeFramebuffers(); //Release memory of framebuffers.
    void swapFramebuffers(); //Swap framebuffers (selfmade)
    void clearScreen(); //Set framebuffer.base to white (wholescreen)
    void colorScreen(uint16_t color); //Specify color using RBH or defined color::
    void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
    
    
    //Use filesystem::openfile or filesystem::preload to obtain a Texture*
    
    //Loaded Texture Functions
    void draw_texture_loaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY); //Drawing a texture
    void draw_texture_loaded_scale(filesystem::Texture* texture, unsigned int posX, unsigned int posY, double newHeightScale, double newWidthScale); //Drawing a texture, scaled.
    void draw_texture_loaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum); //Draw a piece of a large texture from a loaded file.
    void draw_texture_loaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum); //Draw a part of a loaded texture and scale it.
    //File Texture Functions
    void draw_texture_file(std::string filename, unsigned int posX, unsigned int posY); // Draw texture straight from file.
    void draw_texture_file_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum); //Draw a piece of a large texture from a file.
    void draw_texture_file_scale_part(std::string filename, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum); //Draw a piece of a large texture from a file scaled.
    //Preloaded texture Functions
    void draw_texture_preloaded(filesystem::Texture* texture, unsigned int posX, unsigned int posY); //Draw a preloaded texture.
    void draw_texture_preloaded_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int pieceNum); //Draw a piece of a preloaded texture.
    void draw_texture_preloaded_scale_part(filesystem::Texture* texture, unsigned int posX, unsigned int posY, unsigned int heightPerPiece, unsigned int widthPerPiece, unsigned int newHeightScale, unsigned int newWidthScale, unsigned int pieceNum); //Draw a part of a preloaded texture to be scaled.
    
    game::Position checkBounds(int posX, int posY, unsigned int x, unsigned int y);
}


#endif
