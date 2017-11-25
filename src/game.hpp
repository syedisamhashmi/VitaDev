#ifndef GAME_H
#define GAME_H

#include <psp2/types.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>
#include <vita2d.h>
#include <psp2/touch.h>
#include <psp2/ctrl.h>


namespace game
{
    extern unsigned int PLAYER_HEIGHT;
    extern unsigned int PLAYER_WIDTH;
    typedef enum  {PAUSED, UNPAUSED} gamestate;
    extern gamestate state;
    
    extern signed char lx; //Left analog X
    extern signed char ly; //Left analog Y
    extern signed char rx; //Right analog X
    extern signed char ry; //Right analog Y
    
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
            unsigned int health;
            unsigned int missiles;
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
    
    
    void checkInput(SceCtrlData pad);
    
    
    
    
    
    
    
    
}



#endif
