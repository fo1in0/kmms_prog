#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include "Movable.hpp"

class Map;

class MovingObject : public Movable {
public:
    MovingObject();
    MovingObject(float xPos, float yPos, float oWidth, float oHeight, char type);
    ~MovingObject();
    
    void Update() override;
    void VertMove(Object** bricks, int brickCount);
};

class MovingObjectManager {
private:
    MovingObject** moving;
    int length;
    
public:
    MovingObjectManager();
    ~MovingObjectManager();
    
    MovingObject* AddMovingObject(float x, float y, float width, float height, char type);
    void DeleteMoving(int index);
    void UpdateAll(Object** bricks, int brickCount, int mapHeight);
    void DrawAll(class Map& map);
    int GetLength() const;
    MovingObject* Get(int index) const;
    void Clear();
};

#endif