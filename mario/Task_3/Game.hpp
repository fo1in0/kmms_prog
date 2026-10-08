#ifndef GAME_HPP
#define GAME_HPP

#include "Mario.hpp"
#include "Brick.hpp"
#include "MovingObject.hpp"
#include "Map.hpp"

class Game {
private:
    Mario mario;
    Brick** bricks;
    int brickLength;
    MovingObjectManager movingManager;
    Map map;
    int level;
    int score;
    int maxLevel;
    
    void CreateLevel(int lvl);
    void PlayerDead();
    void HorizonMoveMap(float dx);
    void MarioCollision();
    Brick* GetNewBrick();
    void CreateBrick(float x, float y, float w, float h, char type);
    
public:
    Game();
    ~Game();
    
    void Run();
    void ProcessInput();
    void Update();
    void Render();
};

#endif