#include <psp2/kernel/processmgr.h>
#include <psp2/message_dialog.h>
#include <psp2/ime_dialog.h>

#include <string>
#include <inttypes.h>
#include <stdint.h>

#include "utils.hpp"
#include "graphics.hpp"
#include "colors.hpp"
#include "filesystem.hpp"
#include "io.hpp"

#include "game.hpp" 

int main(int argc, char *argv[])
{
    int framecount = 0;
    std::string idleFile = "ux0:/test/idle.rgba";
    std::string rightRunFile = "ux0:/test/rightrun.rgba";
    
    graphics::enableTouchControl(); //Vita2d and Selfmade
    graphics::setUp(); //Turn off system control;
    
    graphics::initializeFramebuffers(); //Selfmade
    filesystem::Texture* idle = filesystem::loadFile(idleFile);
    filesystem::Texture* rightrun = filesystem::loadFile(rightRunFile);

    

    double x = 0;
    bool exit = false;
    while(!exit)
    {
        graphics::colorScreen(colors::BLACK16);
        utils::printsf(700, 0, colors::WHITE32, "Frame: %d", framecount);
        io::getio();    //Vita2d and Selfmade
        
        
        graphics::draw_texture_scale_loaded(idle, x, 50, 1, 1);
        //Works.
        graphics::draw_texture_scale_loaded(idle, x, 100, 2, 2);
        //Works.

        graphics::draw_texture_part_loaded(rightrun, 200, 200, game::PLAYER_HEIGHT, game::PLAYER_WIDTH, (int)x);
        //Works.

        //graphics::draw_texture_file(rightRunFile, 200, 200);
        //Works.
       
        //graphics::draw_texture_part_file(rightRunFile, 200, 200,43,35, (int) x);
        //Works.
        
        //graphics::draw_texture_part_file_scale(rightRunFile, 200, 200,43, 35, 2, 2, (int) x);
        
        graphics::draw_texture_part_loaded_scale(rightrun, 200 + 20*(x), 350, game::PLAYER_HEIGHT, game::PLAYER_WIDTH, 2, 2, (int) x);
        //Works.
        
        utils::printsf(250, 300, colors::WHITE32, "%f", x);
        
        x+=.4;

        //if(x >= 10)
        //    x = 0;
        graphics::swapFramebuffers(); //Selfmade
        sceDisplayWaitVblankStart();
        framecount+=1;
    }
    
   
    graphics::freeFramebuffers(); //Vita2d and Selfmade
    sceKernelExitProcess(0);
    return 0;
}


