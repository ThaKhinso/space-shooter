#pragma once
#include <iostream>

class Vec2
{
private:
    /* data */
public:
    double x,y = 0;


    Vec2(/* args */);
    Vec2(double xin, double yin);

    friend std::ostream& operator << (std::ostream& stream, const Vec2& lhs);

    bool operator == (Vec2 lhs);
    bool operator != (Vec2 lhs);
    
    Vec2 operator + (Vec2 lhs);
    Vec2 operator - (Vec2 lhs);
    Vec2 operator * (Vec2 lhs);
    Vec2 operator / (Vec2 lhs);

    void operator += (const Vec2& lhs);
    void operator -= (const Vec2& lhs);

    //Note This don't multiply or divide two vectors
    //This multiply or divide the vectors's members
    void operator *= (const float lhs);
    void operator /= (const float lhs);

    void normalize();
    static Vec2 normalize(Vec2 vector);
    double length();
    ~Vec2();
};
