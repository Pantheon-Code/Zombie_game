#pragma once
#include "item.h"
#include "number_input.h"
#include "text_input.h"
#include "button.h"
#include "weapon.h"


class attacks;

class inventory{
    int max_item_amount;
    int space_taken = 0;
    vector<item *> item_vec;
    unordered_map<string, int> item_map;
    vector<weapon *> weapon_vec;
    unordered_map<string, int> weapon_map;
    int x = 780, y, width = 100, height;
    number_input item_space_input, item_amount_input, attack_points_input, damage_points_input;
    text_input item_name_input;
    button add_item_button, delete_item_button, add_weapon_button;
    int next_item_spot = 0;
    attacks * attacks1;
    public:
    inventory(int y, int max_item_amount, attacks * attacks1);
    void update();
    void add_back_item(string item_to_add_back);
    void add_item();
    void remove_item(string item_to_remove);
    void delete_item(string item_to_delete);
    void draw();
    vector<weapon *> * get_weapon_vec();
    unordered_map<string, int> * get_weapon_map();
    ~inventory();
};