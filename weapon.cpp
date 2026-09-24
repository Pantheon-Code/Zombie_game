#include "weapon.h"

weapon::weapon(int x, int y, int space, string name, int attack, int damage) : item(x, y, space, name){
    
    this->attack = attack;
    this->damage = damage;
    this->height = 30;
    this->color = GRAY;
}

void weapon::draw(){
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s" ,this->name.c_str()), this->x + 10, this->y + 10, 20, WHITE);
}