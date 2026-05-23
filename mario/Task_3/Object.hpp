#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Windows.h>

class Object {
protected:
    float x, y;
    float width, height;
    float vertSpeed;
    float horizSpeed;
    char cType;
    BOOL isFly;

public:
    Object();
    Object(float xPos, float yPos, float oWidth, float oHeight, char type);
    virtual ~Object();

    void SetPosition(float xPos, float yPos);
    float GetX() const;
    float GetY() const;
    float GetWidth() const;
    float GetHeight() const;
    float GetVertSpeed() const;
    float GetHorizSpeed() const;
    char GetType() const;
    BOOL IsFly() const;
    
    void SetVertSpeed(float speed);
    void SetHorizSpeed(float speed);
    void SetType(char type);
    void SetIsFly(BOOL fly);
    
    virtual void Update();
    virtual bool IsCollision(const Object& other) const;
};

#endif