#pragma once
class CLifeSpan {
public:
    int remaining = 0;
    int total = 0;
    CLifeSpan(int total) : remaining(total){

    }
    ~CLifeSpan(){};
};