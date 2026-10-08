#include "Brick.hpp"

Brick::Brick() : Object() {}

Brick::Brick(float xPos, float yPos, float oWidth, float oHeight, char type)
    : Object(xPos, yPos, oWidth, oHeight, type) {}

Brick::~Brick() {}