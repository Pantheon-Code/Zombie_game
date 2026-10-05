#pragma once
#include "weapon.h"
#include "text_input.h"
#include "button.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include "inventory.h"

using namespace std;
class attacks{
    private:
        int x = 630, y = 200;
        text_input * weapon_input = nullptr;
        button * equip_button = nullptr, * unequip_button = nullptr;
        item_node * item_list[3] = {nullptr, nullptr, nullptr};
        inventory * inventory1 = nullptr;
    public:
        attacks(inventory * inventory1);
        void update();
        item_node * delete_weapon(string weapon_name);
        void add_weapon(item_node * weapon);
        void equip_weapon();
        void unequip_weapon();
        void draw();
};