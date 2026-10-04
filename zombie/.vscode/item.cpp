#include "item.h"

item::item(int x, int y, int space, string name){
    this->space = space;
    this->name = name;
    this->x = x;
    this->y = y;
    this->get_out_inventory();
}

string item::get_name(){
    return name;
}

int item::get_height(){
    return height;
}

void item::get_in_inventory(){
    this->height = 20;
    this->in_inventory = false;
}

void item::get_out_inventory(){
    this->height = 20 * this->space + (5 * (this->space - 1));
    this->in_inventory = true;
}


int item::get_space(){
    return this->space;
}

void item::shift(int height){
    this->y -= height;
}

string item::get_item_type(){
    return this->item_type;
}

void item::change_position(int x, int y){
    this->x = x;
    this->y = y;
}

void item::draw(){
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s" ,this->name.c_str()), this->x, this->y, 20, WHITE);
}
