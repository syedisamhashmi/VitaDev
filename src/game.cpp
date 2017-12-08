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
    double PLAYER_BASE_MOVE_SPEED = 5;
    int MAX_AXIS_VALUE = 128;
    double FRICTION = .2;
    double PLAYER_MAX_MOVE_SPEED = 40;
    double PLAYER_CURRENT_MAX_MOVE_SPEED = 10;
    double SPEED_MODIFIER = .1;
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
        signed char vallx = (signed char)(pad.lx - game::MAX_AXIS_VALUE);
        signed char vally = (signed char)(pad.ly - game::MAX_AXIS_VALUE);
        signed char valrx = (signed char)(pad.rx - game::MAX_AXIS_VALUE);
        signed char valry = (signed char)(pad.ry - game::MAX_AXIS_VALUE);
        //Read left axis values for y and x.
        player.lastPosition = player.position;
        
        if(vallx > 10 || vallx < -10)
        {
            
            int i_vallx = (int) vallx;
            double percent = (double)((double)i_vallx/(double)game::MAX_AXIS_VALUE);
            double toAdd =  (percent * game::PLAYER_BASE_MOVE_SPEED) * game::SPEED_MODIFIER;
            game::player.velocity.x += toAdd;
            
            checkPlayerMaxSpeed();
            
            game::player.position.x += game::player.velocity.x;
            
            utils::printsf(10, 80, colors::WHITE32, "vallx x: %f,", toAdd); //Print out lx.

            utils::printsf(10, 110, colors::WHITE32, "velocity x: %f,", game::player.velocity.x); //Print out velocity.
        }
        
        
    }
    
    void drawPlayer()
    {
        applyFriction();
        
        game::player.previousMovestate = game::player.movestate;
        double deltaFrame = utils::abs(game::player.velocity.x) / game::PLAYER_MAX_MOVE_SPEED;
        game::player.animationFrame = game::player.animationFrame + deltaFrame;
        
        if(game::player.movestate != game::player.previousMovestate)
        {
            game::player.animationFrame = 0;
        }
        
        if(game::player.position.x > game::player.lastPosition.x)
        {
            game::player.movestate = MOVING_RIGHT;
            graphics::draw_texture_preloaded_scale_part(game::rightrun, game::player.position.x , game::player.position.y, game::PLAYER_HEIGHT, game::PLAYER_WIDTH,2,2, (int)game::player.animationFrame);
        }
        else if(game::player.position.x == game::player.lastPosition.x)
        {
            game::player.movestate = IDLE;
            graphics::draw_texture_preloaded_scale_part(game::idle, game::player.position.x , game::player.position.y, 48, 24 ,2,2, (int)game::player.animationFrame); //Idle has special height and width
        }
        else if(game::player.position.x < game::player.lastPosition.x)
        {
            game::player.movestate = MOVING_LEFT;
            graphics::draw_texture_preloaded_scale_part(game::leftrun, game::player.position.x, game::player.position.y, game::PLAYER_HEIGHT, game::PLAYER_WIDTH,2,2, (int)game::player.animationFrame);
        }

        
    }
    void checkPlayerMaxSpeed()
    {
        if(utils::abs(game::player.velocity.x)  > game::PLAYER_CURRENT_MAX_MOVE_SPEED)
        {
            if(game::player.velocity.x < 0)
            {
                game::player.velocity.x = -game::PLAYER_CURRENT_MAX_MOVE_SPEED;
            }
            else if(game::player.velocity.x > 0)
            {
                game::player.velocity.x = game::PLAYER_CURRENT_MAX_MOVE_SPEED;
            }
        }
    }
    void applyFriction()
    {
        if(utils::abs(game::player.velocity.x) > game::FRICTION)
        {
            if(game::player.velocity.x > 0)
            {
                if(game::player.velocity.x - game::FRICTION < 0)
                {
                    game::player.velocity.x = 0;
                }
                else
                    game::player.velocity.x -= game::FRICTION;
            }
            else if(game::player.velocity.x < 0)
            {
                if(game::player.velocity.x + game::FRICTION > 0)
                {
                    game::player.velocity.x = 0;
                }
                else
                    game::player.velocity.x += game::FRICTION;
            }
            game::player.position.x += game::player.velocity.x;
        }
    }
    
    
    
    
}








