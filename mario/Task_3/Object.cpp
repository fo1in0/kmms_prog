#include "Object.hpp"
#include <cmath>

Object::Object() : x(0), y(0), width(1), height(1), cType(' ') {}

Object::Object(float xPos, float yPos, float oWidth, float oHeight, char type)
    : x(xPos), y(yPos), width(oWidth), height(oHeight), cType(type) {}

Object::~Object() {}

void Object::SetPosition(float xPos, float yPos) {
    x = xPos;
    y = yPos;
}

float Object::GetX() const { return x; }
float Object::GetY() const { return y; }
float Object::GetWidth() const { return width; }
float Object::GetHeight() const { return height; }
char Object::GetType() const { return cType; }
void Object::SetType(char type) { cType = type; }

void Object::Update() {}


BOOL Object::IsCollision(const Object& o1, const Object& o2) {
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}