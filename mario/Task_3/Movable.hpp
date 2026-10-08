#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "Object.hpp"

class Movable : public Object {
protected:
    float vertSpeed;
    float horizSpeed;
    BOOL isFly;

public:
    Movable();
    Movable(float xPos, float yPos, float oWidth, float oHeight, char type);
    virtual ~Movable();

    float GetVertSpeed() const;
    float GetHorizSpeed() const;
    BOOL IsFly() const;
    
    void SetVertSpeed(float speed);
    void SetHorizSpeed(float speed);
    void SetIsFly(BOOL fly);
    
    void ApplyGravity();
    virtual void Update() override;
    void ReverseDirection();
};

#endif