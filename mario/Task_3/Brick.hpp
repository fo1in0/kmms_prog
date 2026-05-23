#ifndef BRICK_HPP
#define BRICK_HPP

#include "Object.hpp"

class Mario;
class MovingObjectManager;

class Brick : public Object {
public:
    Brick();
    Brick(float xPos, float yPos, float oWidth, float oHeight, char type);
    ~Brick();
};

#endif