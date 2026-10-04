#pragma once
#include "item_node.h"
#include "number_input.h"
#include "text_input.h"
#include "button.h"


class weapon;
class item;

class inventory{
    int x = 15, y = 200, next_item_position = 225;
    text_input * item_name = nullptr;
    number_input * item_space = nullptr, * attack_roll = nullptr, * amount = nullptr;
    item_node * item_head = nullptr, * item_tail = nullptr;
    button * add_button = nullptr, * delete_button = nullptr;
    public:
    inventory();
    void update();
    void add_item();
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
    void draw();
    ~inventory();
};