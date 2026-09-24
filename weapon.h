#pragma once
#include "item.h"
#include <iostream>

class weapon : public item{
    private:
    int attack, damage;
    public:
        weapon(int x, int y, int space, string name, int attack, int damage);
        void draw();
};