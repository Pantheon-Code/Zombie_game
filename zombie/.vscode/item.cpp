#include "item.h"

item::item(int x, int y, int space, string name){
    this->space = space;
    this->name = name;
    this->x = x;
    this->y = y;
    this->height = 30 * space + 10 * (space - 1);
    if(!this->height) this->height = 30;
}

string item::get_name(){
    return name;
}

int item::get_height(){
    return height;
}

bool item::get_in_inventory(){
    return in_inventory;
}

void item::shift(int height){
    this->y -= height;
}

void item::draw(){
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s" ,this->name.c_str()), this->x + 10, this->y + 10, 20, WHITE);
}
