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
    
    game::player = game::Entity();

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
        
      
        
        graphics::draw_texture_preloaded_scale_part(rightrun, game::player.position.x , game::player.position.y, game::PLAYER_HEIGHT, game::PLAYER_WIDTH,2,2,(int)x);
        game::player.position.x += 15;
        
        
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


