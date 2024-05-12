#pragma once

#include "Vec2.h"
class CCollision
{
private:
    Vec2 position{ 0,0 }; Vec2 size{ 20, 20 };
public:
    CCollision(Vec2& pos, Vec2& size)
        :position(pos), size(size){};
    ~CCollision(){};
};

