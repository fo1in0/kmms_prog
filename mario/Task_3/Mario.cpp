#include "Mario.hpp"

Mario::Mario() : Movable(39, 10, 3, 3, '@') {
    vertSpeed = 0;
    isFly = FALSE;
    horizSpeed = 0.2f;
}

Mario::~Mario() {}

void Mario::Jump() {
    if (!isFly)
        vertSpeed = -1.0f;
}

void Mario::Update() {}

void Mario::Reset() {
    x = 39;
    y = 10;
    vertSpeed = 0;
    isFly = FALSE;
}