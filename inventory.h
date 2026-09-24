#pragma once
#include "item.h"
#include "number_input.h"
#include "text_input.h"
#include "button.h"
#include "attacks.h"

class inventory{
    int max_item_amount;
    int space_taken = 0;
    vector<item> item_list_vec;
    unordered_map<string, int> item_list;
    int x = 780, y, width = 100, height;
    number_input item_space, item_amount, attack_points, damage_points;
    text_input item_name;
    button add_item_button, delete_item_button, add_weapon_button;
    int next_item_spot;
    attacks * attacks1;
    public:
    inventory(int y, int max_item_amount, attacks * attacks1);
    void update();
    void add_item();
    void delete_item();
    void remove_item();
    void draw();
};