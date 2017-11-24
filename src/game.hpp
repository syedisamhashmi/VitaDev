#ifndef GAME_H
#define GAME_H

#include <psp2/types.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>
#include <vita2d.h>



namespace game
{
    extern unsigned int PLAYER_HEIGHT;
    extern unsigned int PLAYER_WIDTH;
    typedef enum  {PAUSED, UNPAUSED} gamestate;
    extern gamestate state;
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
    
    class Camera
    {
        public:
            Camera();
            Camera(int x, int y);
            Position position;
    };
    
    class Game;
    
    
    
    
    
    
    
    
    
    
}



#endif
