#pragma once
#include "weapon.h"
#include "text_input.h"
#include "button.h"
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class inventory;

class attacks{
    private:
        int x = 780, y = 500;
        float width = 185.0f, height = 20.0f;
        text_input weapon_name;
        button equip_weapon_button, dequip_weapon_button;
        static const int equipable_weapons_amount = 3;
        vector<weapon *> weapons_vec;
        unordered_map<string, int> weapons;
        weapon * three_weapons[equipable_weapons_amount];
        inventory * inventory1;
    public:
        attacks();
        void set_inventory(inventory * inventory1);
        void update();
        weapon * add_weapon(int x, int y, int space, string name, int attack, int damage);
        void delete_weapon(string weapon_name);
        void equip_weapon();
        void unequip_weapon(weapon weapon_to_unequip);
        void draw();
};