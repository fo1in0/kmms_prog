#ifndef MARIO_HPP
#define MARIO_HPP

#include "Object.hpp"

class Mario : public Object {
public:
    Mario();
    ~Mario();
    
    void Jump();
    void Update() override;
    void Reset();
};

#endif