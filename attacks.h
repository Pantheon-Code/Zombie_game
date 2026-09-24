#pragma once
#include "weapon.h"
#include "text_input.h"
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;
class attacks{
    private:
        int x = 780, y = 500;
        float width = 185.0f, height = 20.0f;
        int next_weapon_position = y + 50;
        text_input weapon_name;
        static const int equipable_weapons_amount = 3;
        vector<weapon> weapons_vec;
        unordered_map<string, int> weapons;
        weapon * three_weapons[equipable_weapons_amount];
    public:
        attacks();
        void update();
        void add_weapon(int space, string name, int attack, int damage);
        void delete_weapon(string weapon_name);
        void equip_weapon(weapon weapon_to_equip);
        void unequip_weapon(weapon weapon_to_unequip);
        void draw();
};