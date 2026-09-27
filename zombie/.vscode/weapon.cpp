#include "weapon.h"

weapon::weapon(int x, int y, int space, string name, int attack, int damage) : item(x, y, space, name){
    
    this->attack = attack;
    this->damage = damage;
    this->color = GRAY;
    this->item_type = "weapon";
}


void weapon::change_position(int y){
    this->y = y;
}

void weapon::equip(){
    this->height = 20;
    this->equiped = true;
}

void weapon::unequip(){
    this->equiped = false;
    this->height = 20 * space + 5 * (space - 1);
    if(!this->height) this->height = 20;
}

bool weapon::get_equiped(){
    return equiped;
}

int weapon::get_attack_points(){
    return attack;
}

int weapon::get_damage_points(){
    return damage;
}

void weapon::draw(){
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s" ,this->name.c_str()), this->x + 10, this->y, 20, WHITE);
}