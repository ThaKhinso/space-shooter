#pragma once

#include "Vec2.h"
class CCollision
{
private:
    Vec2 position, size;
public:
    CCollision(Vec2& pos, Vec2& size)
        :position(pos), size(size){};
    ~CCollision(){};
};

