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
namespace game
{
    unsigned int PLAYER_HEIGHT = 43;
    unsigned int PLAYER_WIDTH = 35;
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
}








