#include "attacks.h"
#include <iterator>
#include "inventory.h"

attacks::attacks() : weapon_name(Rectangle{(float)this->x, (float)this->y, this->width, this->height}),
equip_weapon_button(this->x + this->width + 20, this->y, 20, 20, GREEN, "Equip Weapon", 20),
unequip_weapon_button(this->x + this->width + 50, this->y, 20, 20, GREEN, "Equip Weapon", 20){
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
    if(this->unequip_weapon_button.update(GetMousePosition())){
        this->unequip_weapon();
    }
}

void attacks::equip_weapon(){
    cout << "HERE?";
    string weapon_to_equip = this->weapon_name.get_edit_input();
    cout << weapon_to_equip;
    if(this->inventory1->get_weapon_map()->count(weapon_to_equip)){
        cout << "HELLO?";
        for(int i = 0; i < equipable_weapons_amount; i++){
            if(!this->three_weapons[i] && !((*this->inventory1->get_weapon_vec())[(*this->inventory1->get_weapon_map())[weapon_to_equip]]->get_equiped())){
                cout << "YOOO";
                inventory1->remove_item(weapon_to_equip);
                this->three_weapons[i] = (*this->inventory1->get_weapon_vec())[(*this->inventory1->get_weapon_map())[weapon_to_equip]];
                this->three_weapons[i]->change_position(this->y + 50 + (i * 25));
                this->three_weapons[i]->equip();
                break;
            }
        }
    }
}

void attacks::unequip_weapon(){

    if(this->inventory1->get_weapon_map()->count(this->weapon_name.get_edit_input())){
      
        for(int i = 0; i < equipable_weapons_amount; i++){
       
            if(this->three_weapons[i] && this->three_weapons[i]->get_name() == this->weapon_name.get_edit_input()){
                this->three_weapons[i]->unequip();
                this->inventory1->add_back_item(this->weapon_name.get_edit_input());
           
                this->three_weapons[i] = nullptr; 
            }
        }
    }
}

void attacks::delete_weapon(string weapon_name){
    int item_to_delete_index = this->weapon_map[weapon_name];
    this->weapon_vec.erase(this->weapon_vec.begin() + item_to_delete_index);
    for(int i = item_to_delete_index; i < this->weapon_vec.size(); i++){
        this->weapon_map[this->weapon_vec[i]->get_name()] = this->weapon_map[this->weapon_vec[i]->get_name()] - 1;
    }
    this->weapon_map.erase(weapon_name);
}


void attacks::draw(){
    for(weapon * weapon1 : this->three_weapons){
        if(weapon1) weapon1->draw();
    }

    this->weapon_name.draw();
    this->equip_weapon_button.draw();
    this->unequip_weapon_button.draw();
    DrawText(TextFormat("Weapon Name: "), this->x, this->y - 20, 15, WHITE);
}

attacks::~attacks(){
    for(weapon * &weapon1: this->three_weapons){
        delete weapon1;
        weapon1 = nullptr;
    }
}