#pragma once
#include "Common.h"


class CTransform
{
private:
    /* data */
public:
    Vec2 pos{ 0, 0};
    Vec2 velocity{ 0, 0};
    CTransform( Vec2& p,  Vec2& s)
        :pos(p), velocity(s)
    {
    
    };
    ~CTransform(){};
};
