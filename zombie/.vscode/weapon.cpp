#include "weapon.h"

weapon::weapon(int x, int y, int space, string name, int attack, int damage) : item(x, y, space, name){
    
    this->attack = attack;
    this->damage = damage;
    this->color = GRAY;
}


weapon::weapon(const weapon &weapon_to_copy): 
item(weapon_to_copy.x, weapon_to_copy.y, weapon_to_copy.space, weapon_to_copy.name){
    this->attack = weapon_to_copy.attack;
    this->damage = weapon_to_copy.damage;
    this->height = weapon_to_copy.height;
    this->color = weapon_to_copy.color;
}

void weapon::change_position(int y){
    this->y = y;
}

void weapon::change_inventory(){
    this->height = 20;
}

void weapon::shoot(){
    this->ammo_amount -= this->max_ammo_per_shot;
    if(this->ammo_amount <= 0){
        
    }
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