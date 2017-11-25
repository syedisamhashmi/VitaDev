#include <cstdint>
#include <cstring>

#include <psp2/touch.h>
#include <psp2/ctrl.h>
#include <psp2/types.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>


#include "game.hpp"
#include "graphics.hpp"
#include "utils.hpp"
#include "colors.hpp"

namespace game
{
    unsigned int PLAYER_HEIGHT = 43;
    unsigned int PLAYER_WIDTH = 35;
    unsigned int PLAYER_MOVE_SPEED = 10;
    signed char lx; //Left analog X
    signed char ly; //Left analog Y
    signed char rx; //Right analog X
    signed char ry; //Right analog Y
    
    Player player;
    gamestate state;
    Entity::Entity()
    {
        this->position.x = graphics::SCREEN_W / 2;
        this->position.y = graphics::SCREEN_H / 2;
    }
    Entity::Entity(int x, int y)
    {
        this->position.x = x;
        this->position.y = y;
    }
    
    Position::Position()
    {
        this->x = graphics::SCREEN_W / 2; //Default to center of screen.
        this->y = graphics::SCREEN_H / 2; //Default to center of screen.
    }
    Position::Position(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    
    void checkInput(SceCtrlData pad)
    {
        signed char vallx = (signed char)(pad.lx - 128);
        signed char vally = (signed char)(pad.ly - 128);
        signed char valrx = (signed char)(pad.rx - 128);
        signed char valry = (signed char)(pad.ry - 128);
        
        if(vallx > 10 || vallx < -10)
        {
//            if(lx > 0)
//                player.facing = RIGHT;
//            else
//                if(lx < 0)
//                    player.facing = LEFT;
//            if(lx < 10)
//                player.movestate = MOVING_LEFT;
//            else if(lx > 10)
//                player.movestate = MOVING_RIGHT;
//            else
//                player.movestate = NOT_MOVING;
            player.position.x += (int)((signed char)vallx/ (signed char)game::PLAYER_MOVE_SPEED);
            utils::printsf(10, 80, colors::WHITE32, "vallx x: %d,", vallx); //Print out frame number.
        }
        
        
    }
    
    
    
}








