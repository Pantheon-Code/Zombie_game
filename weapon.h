#pragma once
#include "item.h"
#include <iostream>

class weapon : public item{
    private:
    int attack, damage;
    bool deleted = false;
    public:
        weapon(int x, int y, int space, string name, int attack, int damage);
        weapon(const weapon &weapon_to_copy);
        weapon();
        void change_position(int y);
        void change_deleted(bool new_deleted);
        bool get_deleted();
        void change_inventory();
        void draw();
};