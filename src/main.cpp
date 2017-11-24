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


#include "preloaded.hpp"


int main(int argc, char *argv[])
{
    int framecount = 0;
    std::string idleFile = "ux0:/test/idle.rgba";
    std::string rightRunFile = "ux0:/test/rightrun.rgba";
    
    graphics::enableTouchControl(); //Vita2d and Selfmade
    graphics::setUp(); //Turn off system control;
    
    graphics::initializeFramebuffers(); //Selfmade
    
    filesystem::Texture* rightrun = filesystem::preload(filesystem::RIGHT_RUN_ANIMATION);
    filesystem::Texture* idle = filesystem::preload(filesystem::IDLE_ANIMATION);
    

    double x = 0;
    bool exit = false;
    while(!exit)
    {
        graphics::colorScreen(colors::BLACK16); //Flush screen BLACK.
        utils::printsf(700, 0, colors::WHITE32, "Frame: %d", framecount); //Print out frame number.
        io::getio();    //Vita2d and Selfmade
        
        
        graphics::draw_texture_preloaded(rightrun,150,150);
        //graphics::draw_texture_preloaded(idle,200,120);
        
        
      //  graphics::draw_texture_part_loaded_scale(rightrun, 200 + 20*(x), 350, game::PLAYER_HEIGHT, game::PLAYER_WIDTH, 2, 2, (int) x);
        //Works.
        
        //utils::printsf(250, 300, colors::WHITE32, "width |%u|", rightrun->header.width);
        //utils::printsf(250, 330, colors::WHITE32, "height |%u|", rightrun->header.height);
        //utils::printsf(250, 360, colors::WHITE32, "states |%u|", rightrun->header.states);
        
        
        
        graphics::draw_texture_preloaded_part(rightrun,150 + (10*x) ,200,game::PLAYER_HEIGHT,game::PLAYER_WIDTH,(int)x);
        
        
        
        x+=.2;

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


