#include "Object.hpp"
#include <cmath>

Object::Object() : x(0), y(0), width(1), height(1), vertSpeed(0), 
                   horizSpeed(0.2f), cType(' '), isFly(FALSE) {}

Object::Object(float xPos, float yPos, float oWidth, float oHeight, char type)
    : x(xPos), y(yPos), width(oWidth), height(oHeight), vertSpeed(0),
      horizSpeed(0.2f), cType(type), isFly(FALSE) {}

Object::~Object() {}

void Object::SetPosition(float xPos, float yPos) {
    x = xPos;
    y = yPos;
}

float Object::GetX() const { return x; }
float Object::GetY() const { return y; }
float Object::GetWidth() const { return width; }
float Object::GetHeight() const { return height; }
float Object::GetVertSpeed() const { return vertSpeed; }
float Object::GetHorizSpeed() const { return horizSpeed; }
char Object::GetType() const { return cType; }
BOOL Object::IsFly() const { return isFly; }

void Object::SetVertSpeed(float speed) { vertSpeed = speed; }
void Object::SetHorizSpeed(float speed) { horizSpeed = speed; }
void Object::SetType(char type) { cType = type; }
void Object::SetIsFly(BOOL fly) { isFly = fly; }

void Object::Update() {}

bool Object::IsCollision(const Object& other) const {
    return ((x + width) > other.GetX()) && (x < (other.GetX() + other.GetWidth())) &&
           ((y + height) > other.GetY()) && (y < (other.GetY() + other.GetHeight()));
}