#ifndef MARIO_HPP
#define MARIO_HPP

#include "Movable.hpp"

class Mario : public Movable {
public:
    Mario();
    ~Mario();
    
    void Jump();
    void Update() override;
    void Reset();
};

#endif