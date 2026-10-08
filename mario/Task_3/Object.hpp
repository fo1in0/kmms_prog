#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Windows.h>

class Object {
protected:
    float x, y;
    float width, height;
    char cType;

public:
    Object();
    Object(float xPos, float yPos, float oWidth, float oHeight, char type);
    virtual ~Object();

    void SetPosition(float xPos, float yPos);
    float GetX() const;
    float GetY() const;
    float GetWidth() const;
    float GetHeight() const;
    char GetType() const;
    void SetType(char type);
    
    virtual void Update();
    static BOOL IsCollision(const Object& o1, const Object& o2);
};

#endif