#include "Movable.hpp"

Movable::Movable() : Object(), vertSpeed(0), horizSpeed(2.0f), isFly(FALSE) {}

Movable::Movable(float xPos, float yPos, float oWidth, float oHeight, char type)
    : Object(xPos, yPos, oWidth, oHeight, type), vertSpeed(0), horizSpeed(2.0f), isFly(FALSE) {}

Movable::~Movable() {}

float Movable::GetVertSpeed() const { return vertSpeed; }
float Movable::GetHorizSpeed() const { return horizSpeed; }
BOOL Movable::IsFly() const { return isFly; }

void Movable::SetVertSpeed(float speed) { vertSpeed = speed; }
void Movable::SetHorizSpeed(float speed) { horizSpeed = speed; }
void Movable::SetIsFly(BOOL fly) { isFly = fly; }

void Movable::ApplyGravity() {
    isFly = TRUE;
    vertSpeed += 0.5f;
    y += vertSpeed;
}

void Movable::Update() {}

void Movable::ReverseDirection() {
    horizSpeed = -horizSpeed;
}