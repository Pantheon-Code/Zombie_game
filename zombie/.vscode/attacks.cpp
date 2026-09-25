#include "attacks.h"
#include <iterator>
#include "inventory.h"

attacks::attacks() : weapon_name(Rectangle{(float)this->x, (float)this->y, this->width, this->height}),
equip_weapon_button(this->x + this->width + 20, this->y, 20, 20, GREEN, "Equip Weapon", 20),
dequip_weapon_button(this->x + this->width + 50, this->y, 20, 20, GREEN, "Equip Weapon", 20){
    for(weapon * & weapon1: this->three_weapons){
        weapon1 = nullptr;
    }
}

void attacks::set_inventory(inventory * inventory1){
    this->inventory1 = inventory1;
}

void attacks::update(){
    this->weapon_name.update();
    if(this->equip_weapon_button.update(GetMousePosition())){
        this->equip_weapon();
    }
}

weapon * attacks::add_weapon(int x, int y, int space, string name, int attack, int damage){
    weapon * new_weapon = new weapon(x, y, space, name, attack, damage);
    this->weapons.emplace(new_weapon->get_name(), this->weapons_vec.size());
    this->weapons_vec.push_back(new_weapon);
    return new_weapon;
}

void attacks::delete_weapon(string weapon_name){
    if(!this->weapons.count(weapon_name)){
        return;
    }
    delete this->weapons_vec[this->weapons[weapon_name]];
    this->weapons_vec[this->weapons[weapon_name]] = nullptr;
    this->weapons_vec.erase(this->weapons_vec.begin() + this->weapons[weapon_name]);
    int deleted_weapon_index = this->weapons[weapon_name];
    this->weapons.erase(weapon_name);
    for(int i = deleted_weapon_index; i < this->weapons_vec.size(); i++){
        this->weapons[this->weapons_vec[i]->get_name()] = this->weapons[this->weapons_vec[i]->get_name()] - 1;
    }

}

void attacks::equip_weapon(){
    string weapon_to_equip = this->weapon_name.get_edit_input();
    if(this->weapons.count(weapon_to_equip)){
        for(int i = 0; i < equipable_weapons_amount; i++){
            if(!this->three_weapons[i]){
                weapon recently_equiped(*this->weapons_vec[this->weapons[weapon_to_equip]]);
                this->three_weapons[i] = new weapon(*this->weapons_vec[this->weapons[weapon_to_equip]]);
                this->three_weapons[i]->change_position(this->y + 50 + (i * 40));
                this->three_weapons[i]->change_inventory();
                delete_weapon(weapon_to_equip);
                this->inventory1->delete_item(recently_equiped);
                break;
            }
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

    // for(weapon weapon1: this->weapons_vec){
    //     weapon1.draw();
    // }
    this->weapon_name.draw();
    this->equip_weapon_button.draw();
    DrawText(TextFormat("Weapon Name: "), this->x, this->y - 20, 15, WHITE);
}