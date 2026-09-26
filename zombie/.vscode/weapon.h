#pragma once
#include "item.h"
#include <iostream>

class weapon : public item{
    private:
    int attack, damage, ammo_amount, max_ammo_per_shot = 2;
    string ammo_type = "9mm";
    public:
        weapon(int x, int y, int space, string name, int attack, int damage);
        weapon(const weapon &weapon_to_copy);
        weapon();
        void change_position(int y);
        void change_inventory();
        void shoot();
        int get_attack_points();
        int get_damage_points();
        void draw();
};