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
    
    extern unsigned int tileSize;
    extern unsigned int PLAYER_HEIGHT;
    extern unsigned int PLAYER_WIDTH;
    extern double PLAYER_BASE_MOVE_SPEED;
    extern double PLAYER_MAX_MOVE_SPEED;
    extern double PLAYER_CURRENT_MAX_MOVE_SPEED;
    extern double SPEED_MODIFIER;
    extern double FRICTION;
    extern int MAX_AXIS_VALUE;
    typedef enum  {PAUSED, UNPAUSED} gamestate;
    typedef enum  {IDLE, MOVING_RIGHT, MOVING_LEFT} Movestate;
    typedef enum {tileCount = 2} tileVals;
    extern gamestate state;
    
    extern filesystem::Texture* rightrun;
    extern filesystem::Texture* leftrun;
    extern filesystem::Texture* idle;
    extern filesystem::Texture** tiles;
    
    
    extern signed char lx; //Left analog X
    extern signed char ly; //Left analog Y
    extern signed char rx; //Right analog X
    extern signed char ry; //Right analog Y
    
    class Velocity
    {
        public:
            double x;
            double y;
            Velocity(double x, double y)
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
            Player();
    };
    
    class Camera
    {
        public:
            Camera()
            {
                this->position.x = 0;
                this->position.y = 0;
            }
            Camera(int x, int y)
            {
                this->position.x = x;
                this->position.y = y;
            }
            Position position;
    };
    
    
    extern Player player;
    extern Camera camera;
    
    void drawPlayer();
    void checkInput(SceCtrlData pad);
    void applyFriction();
    void checkPlayerMaxSpeed();
    
    
    
    
    
    
}



#endif
