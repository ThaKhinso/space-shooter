#pragma once
#include "Common.h"


class CTransform
{
private:
    /* data */
public:
    Vec2 pos = { 0, 0};
    Vec2 velocity{ 0, 0};
    CTransform(const Vec2& p, const Vec2& s)
        :pos(p), velocity(s) {};
    ~CTransform();
};
