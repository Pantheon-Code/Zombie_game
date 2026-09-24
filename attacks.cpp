#include "attacks.h"
#include <iterator>

attacks::attacks() : weapon_name(Rectangle{(float)this->x, (float)this->y, this->width, this->height}){
    for(weapon * & weapon1: this->three_weapons){
        weapon1 = nullptr;
    }
}

void attacks::update(){
    this->weapon_name.update();
}

void attacks::add_weapon(int space, string name, int attack, int damage){
    weapon new_weapon(this->x, next_weapon_position, space, name, attack, damage);
    this->weapons.emplace(new_weapon.get_name(), this->weapons_vec.size());
    cout << new_weapon.get_name();
    cout << this->weapons_vec.size();
    this->weapons_vec.push_back(new_weapon);
    next_weapon_position += 40;
}

void attacks::delete_weapon(string weapon_name){
    if(!this->weapons.count(weapon_name)){
        return;
    }
    for(int i = 0; i < equipable_weapons_amount; i++){
        if(this->three_weapons[i]){
            if(this->three_weapons[i]->get_name() == weapon_name){
                delete this->three_weapons[i];
                this->three_weapons[i] = nullptr;
            }
        }
    }
    this->weapons_vec.erase(this->weapons_vec.begin() + this->weapons[weapon_name]);
    int deleted_weapon_index = this->weapons[weapon_name];
    this->weapons.erase(weapon_name);
    for(int i = deleted_weapon_index; i < this->weapons_vec.size(); i++){
        this->weapons[this->weapons_vec[i].get_name()] = this->weapons[this->weapons_vec[i].get_name()] - 1;
        this->weapons_vec[i].shift(40);
    }
    this->next_weapon_position -= 40;

}

void attacks::equip_weapon(weapon weapon_to_equip){
    for(int i = 0; i < equipable_weapons_amount; i++){
        if(!this->three_weapons[i]){
            this->three_weapons[i] = &weapon_to_equip;
        }
    }
}

void attacks::unequip_weapon(weapon weapon_to_unequip){
    for(int i = 0; i < equipable_weapons_amount; i++){
        if(this->three_weapons[i]->get_name() == weapon_to_unequip.get_name()){

            this->three_weapons[i] = nullptr;
        }
    }
}



void attacks::draw(){
    for(weapon * weapon1 : this->three_weapons){
        if(weapon1) weapon1->draw();
    }

    for(weapon weapon1: this->weapons_vec){
        weapon1.draw();
    }
    this->weapon_name.draw();
}