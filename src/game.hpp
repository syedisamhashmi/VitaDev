#ifndef GAME_H
#define GAME_H

#include <psp2/types.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>
#include <vita2d.h>
#include <psp2/touch.h>
#include <psp2/ctrl.h>

#include "filesystem.hpp"

namespace game
{
    extern unsigned int PLAYER_HEIGHT;
    extern unsigned int PLAYER_WIDTH;
    extern unsigned int PLAYER_BASE_MOVE_SPEED;
    extern unsigned int PLAYER_MAX_MOVE_SPEED;
    extern unsigned int SPEED_MODIFIER;
    typedef enum  {PAUSED, UNPAUSED} gamestate;
    typedef enum  {IDLE, MOVING_RIGHT, MOVING_LEFT} Movestate;
    
    extern gamestate state;
    
    extern filesystem::Texture* rightrun;
    extern filesystem::Texture* leftrun;
    extern filesystem::Texture* idle;
    
    
    
    extern signed char lx; //Left analog X
    extern signed char ly; //Left analog Y
    extern signed char rx; //Right analog X
    extern signed char ry; //Right analog Y
    
    class Velocity
    {
        public:
            signed int x;
            signed int y;
            Velocity(signed int x, signed int y)
            {
                this->x = x;
                this->y = y;
            }
            Velocity()
            {
                this-> x = 0;
                this-> y = 0;
            }
    };
    class Position
    {
        public:
            Position();
            Position(int x, int y);
            int x;
            int y;
    };
    
    class Entity
    {
        public:
            Position position;
            Entity();
            Entity(int x, int y);
    };
    class Player : public Entity
    {
        public:
            Position lastPosition;
            Movestate movestate;
            Movestate previousMovestate;
            double animationFrame;
            unsigned int health;
            unsigned int missiles;
            Velocity velocity;
            Player()
            {
                this->movestate = IDLE;
                this->previousMovestate = IDLE;
            }
    };
    
    extern Player player;
    
    class Camera
    {
        public:
            Camera();
            Camera(int x, int y);
            Position position;
    };
    
    class Game;
    
    void drawPlayer();
    void checkInput(SceCtrlData pad);
    
    
    
    
    
    
    
    
}



#endif
