#include "MovingObject.hpp"
#include "Map.hpp"
#include "Object.hpp"
#include <cstdlib>
#include <cstring>

MovingObject::MovingObject() : Object() {}

MovingObject::MovingObject(float xPos, float yPos, float oWidth, float oHeight, char type)
    : Object(xPos, yPos, oWidth, oHeight, type) {
    horizSpeed = 0.2f;
    vertSpeed = 0;
    isFly = FALSE;
}

MovingObject::~MovingObject() {}

void MovingObject::Update() {}

void MovingObject::ReverseDirection() {
    horizSpeed = -horizSpeed;
}

void MovingObject::VertMove(Object** bricks, int brickCount) {
    isFly = TRUE;
    vertSpeed += 0.05f;
    y += vertSpeed;

    for (int i = 0; i < brickCount; i++) {
        if (bricks[i] && IsCollision(*bricks[i])) {
            y -= vertSpeed;
            if (vertSpeed > 0) {
                isFly = FALSE;
                vertSpeed = 0;
            }
            break;
        }
    }
}

MovingObjectManager::MovingObjectManager() : moving(nullptr), length(0) {}

MovingObjectManager::~MovingObjectManager() {
    Clear();
}

MovingObject* MovingObjectManager::AddMovingObject(float x, float y, float width, float height, char type) {
    MovingObject** newMoving = new MovingObject*[length + 1];
    for (int i = 0; i < length; i++)
        newMoving[i] = moving[i];
    
    newMoving[length] = new MovingObject(x, y, width, height, type);
    delete[] moving;
    moving = newMoving;
    length++;
    return moving[length - 1];
}

void MovingObjectManager::DeleteMoving(int index) {
    delete moving[index];
    for (int i = index; i < length - 1; i++)
        moving[i] = moving[i + 1];
    length--;
}

void MovingObjectManager::UpdateAll(Object** bricks, int brickCount, int mapHeight) {
    for (int i = 0; i < length; i++) {
        if (!moving[i]) continue;
   
        moving[i]->VertMove(bricks, brickCount);
            
        float oldX = moving[i]->GetX();
        moving[i]->SetPosition(moving[i]->GetX() + moving[i]->GetHorizSpeed(), moving[i]->GetY());
        
              for (int j = 0; j < brickCount; j++) {
            if (bricks[j] && moving[i]->IsCollision(*bricks[j])) {
                moving[i]->SetPosition(oldX, moving[i]->GetY());
                moving[i]->ReverseDirection();
                break;
            }
        }
        
        if (moving[i]->GetType() == 'o') {
            MovingObject temp = *moving[i];
            temp.VertMove(bricks, brickCount);
            if (temp.IsFly() == TRUE) {
                moving[i]->SetPosition(oldX, moving[i]->GetY());
                moving[i]->ReverseDirection();
            }
        }
        
        if (moving[i]->GetY() > mapHeight) {
            DeleteMoving(i);
            i--;
        }
    }
}

void MovingObjectManager::DrawAll(Map& map) {
    for (int i = 0; i < length; i++)
        if (moving[i])
            map.PutObject(*moving[i]);
}

int MovingObjectManager::GetLength() const { return length; }

MovingObject* MovingObjectManager::Get(int index) const {
    return (index >= 0 && index < length) ? moving[index] : nullptr;
}

void MovingObjectManager::Clear() {
    for (int i = 0; i < length; i++)
        delete moving[i];
    delete[] moving;
    moving = nullptr;
    length = 0;
}