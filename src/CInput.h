#pragma once
#include "Common.h"

enum Keys {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class CInput {
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
private:
};