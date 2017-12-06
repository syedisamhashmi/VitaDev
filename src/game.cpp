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
    unsigned int PLAYER_BASE_MOVE_SPEED = 5;
    unsigned int PLAYER_MAX_MOVE_SPEED = 15;
    unsigned int SPEED_MODIFIER = 10;
    gamestate state;
    filesystem::Texture* rightrun = filesystem::preload(filesystem::RIGHT_RUN_ANIMATION);
    filesystem::Texture* leftrun = filesystem::preload(filesystem::LEFT_RUN_ANIMATION);
    filesystem::Texture* idle = filesystem::preload(filesystem::IDLE_ANIMATION);
    
    signed char lx; //Left analog X
    signed char ly; //Left analog Y
    signed char rx; //Right analog X
    signed char ry; //Right analog Y
    
    
    
    
    
    Player player;
    
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
        player.lastPosition = player.position;
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
            game::player.velocity.x += (int)((signed char)vallx/ (signed char)game::PLAYER_BASE_MOVE_SPEED * (signed char)game::SPEED_MODIFIER);
            
            
            if(utils::abs(game::player.velocity.x)  > game::PLAYER_MAX_MOVE_SPEED)
            {
                if(game::player.velocity.x < 0)
                {
                    game::player.velocity.x = -game::PLAYER_MAX_MOVE_SPEED;
                }
                else if(game::player.velocity.x > 0)
                {
                    game::player.velocity.x = game::PLAYER_MAX_MOVE_SPEED;
                }
            }
            game::player.position.x += game::player.velocity.x;
            
            utils::printsf(10, 80, colors::WHITE32, "vallx x: %d,", vallx); //Print out lx.

            utils::printsf(10, 110, colors::WHITE32, "velocity x: %d,", game::player.velocity.x); //Print out velocity.
}
        
        
    }
    
    void drawPlayer()
    {
        game::player.previousMovestate = game::player.movestate;

        if(game::player.position.x > game::player.lastPosition.x)
        {
            game::player.previousMovestate = game::player.movestate;
            game::player.movestate = MOVING_RIGHT;
            if(game::player.movestate != game::player.previousMovestate)
            {
                game::player.animationFrame = 0;
            }
            graphics::draw_texture_preloaded_scale_part(game::rightrun, game::player.position.x , game::player.position.y, game::PLAYER_HEIGHT, game::PLAYER_WIDTH,2,2, (int)game::player.animationFrame);
            game::player.animationFrame = game::player.animationFrame + ((double)(game::player.position.x - game::player.lastPosition.x))/((double)game::player.velocity.x*game::PLAYER_BASE_MOVE_SPEED);
        }
        if(game::player.position.x == game::player.lastPosition.x)
        {
            game::player.velocity.x = 0;
            game::player.previousMovestate = game::player.movestate;
            game::player.movestate = IDLE;
            if(game::player.movestate != game::player.previousMovestate)
            {
                game::player.animationFrame = 0;
            }
            graphics::draw_texture_preloaded_scale_part(game::idle, game::player.position.x , game::player.position.y, 48, 24 ,2,2, (int)game::player.animationFrame);
            
        }
        if(game::player.position.x < game::player.lastPosition.x)
        {
            game::player.previousMovestate = game::player.movestate;
            game::player.movestate = MOVING_LEFT;
            if(game::player.movestate != game::player.previousMovestate)
            {
                game::player.animationFrame = 0;
            }
            graphics::draw_texture_preloaded_scale_part(game::leftrun, game::player.position.x , game::player.position.y, game::PLAYER_HEIGHT, game::PLAYER_WIDTH,2,2, (int)game::player.animationFrame);
            game::player.animationFrame = game::player.animationFrame + ((double)(game::player.lastPosition.x - game::player.position.x))/((double)utils::abs(game::player.velocity.x)*game::PLAYER_BASE_MOVE_SPEED);
        }
        
        
    }
    
    
    
}








