#pragma once

#include "Vec2.h"
class CCollision
{


public:
    Vec2 position{ 0,0 }; Vec2 size{ 20, 20 };
    CCollision(Vec2& pos, Vec2& size)
        :position(pos), size(size){};
    ~CCollision(){};
};

