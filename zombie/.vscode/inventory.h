#pragma once
#include "item_node.h"
#include "number_input.h"
#include "text_input.h"
#include "button.h"
#include <fstream>
#include <sstream>


class weapon;
class item;
class food;
class water;

class inventory{
    int x = 15, y = 200, next_item_position = 225;
    int x_placement;
    text_input * item_name = nullptr, * ammo_type = nullptr;
    vector<string> number_input_names = {"Space", "Attack", "Amount", "Hunger", "Thirst", "Ammo"};
    item_node * item_head = nullptr, * item_tail = nullptr;
    vector<number_input*> number_input_list;
    button * add_button = nullptr, * delete_button = nullptr;
    string inventory_file = "csv_files/inventory_file.csv";
    public:
    inventory();
    void update();
    void read_file();
    void change_file();
    void add_item();
    void add_item(item_node * new_item);
    void delete_item();
    void shift_items(int item_height, item_node * dummy_ptr1);
    void remove_item();
    void draw_items();
    void change_tail(item_node * new_tail);
    void change_head(item_node * new_head);
    void change_next_item_position(int next_item_position);
    item_node * get_item_head();
    item_node * get_item_tail();
    int get_next_item_position();
    int get_x_placement();
    void draw();
    ~inventory();
};