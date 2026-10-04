#include "attacks.h"
#include <iterator>

attacks::attacks(inventory * inventory1){
    this->weapon_input = new text_input(Rectangle{(float)this->x, (float)this->y, 185, 20});
    this->equip_button = new button(x + 200, y, 30, 15, GREEN, "Equip", 20);
    this->unequip_button = new button(x + 245, y, 30, 15, GREEN, "UnEquip", 20);
    this->inventory1 = inventory1;
}

void attacks::update(){
    this->weapon_input->update();
    if(this->equip_button->update(GetMousePosition())){
        this->equip_weapon();
        cout << "YOOOO";
    }
    if(this->unequip_button->update(GetMousePosition())){
        this->unequip_weapon();
        cout << "YOOOO";
    }
    for(int i = 0; i < 3; i++){
        if(this->item_list[i]){
            weapon * weapon1 = dynamic_cast<weapon*>(this->item_list[i]->item_stored);
            if (weapon1) {
                weapon1->update(this->inventory1->get_item_head(), this->inventory1);
            }
        }
    }
}

item_node * attacks::delete_weapon(string weapon_to_equip){
    cout << "YOOOOsss";
    if(!this->inventory1->get_item_head()) return nullptr;
    item_node * dummy_ptr1 = nullptr;
    item_node * dummy_ptr2 = this->inventory1->get_item_head();
    if(dummy_ptr2->item_stored->get_name() == weapon_to_equip && dummy_ptr2->item_stored->get_item_type() == "weapon"){
        int deleted_height = dummy_ptr2->item_stored->get_height();
        this->inventory1->change_head(dummy_ptr2->next_item);
        if(!dummy_ptr2->next_item) this->inventory1->change_tail(dummy_ptr2->next_item);
        this->inventory1->shift_items(deleted_height + 5, dummy_ptr2->next_item);
        dummy_ptr2->next_item = nullptr;
        return dummy_ptr2;
    }
    dummy_ptr1 = dummy_ptr2;
    dummy_ptr2 = dummy_ptr2->next_item;
    while(dummy_ptr2){
        if(dummy_ptr2->item_stored->get_name() == weapon_to_equip && dummy_ptr2->item_stored->get_item_type() == "weapon"){
            int deleted_height = dummy_ptr2->item_stored->get_height() + 5;
            dummy_ptr1->next_item = dummy_ptr2->next_item;
            this->inventory1->shift_items(deleted_height, dummy_ptr1->next_item);
            if(dummy_ptr2 == this->inventory1->get_item_tail()) this->inventory1->change_tail(dummy_ptr1);
            dummy_ptr2->next_item = nullptr;
            return dummy_ptr2;
        }
        else{
            dummy_ptr1 = dummy_ptr2;
            dummy_ptr2 = dummy_ptr2->next_item;
        }
    }
    return nullptr;

}


void attacks::equip_weapon(){
    string weapon_to_equip = this->weapon_input->get_edit_input();
        for(int i = 0; i < 3; i++){
            if(!this->item_list[i]){
                this->item_list[i] = delete_weapon(weapon_to_equip);
                if(this->item_list[i]){
                    this->item_list[i]->item_stored->change_position(this->x, i * 25 + 400);
                    this->item_list[i]->item_stored->get_in_inventory();
                }
                break;
            }
        }
    
}

void attacks::unequip_weapon(){
    string weapon_to_unequip = this->weapon_input->get_edit_input();
    for(int i = 0; i < 3; i++){
        if(this->item_list[i]){
            if(this->item_list[i]->item_stored->get_name() == weapon_to_unequip){
                this->item_list[i]->item_stored->get_out_inventory();
                this->add_weapon(this->item_list[i]);
                this->item_list[i] = nullptr;
                break;
            }
        }
    }
}

void attacks::add_weapon(item_node * weapon){
    weapon->item_stored->change_position(15, this->inventory1->get_next_item_position());
    this->inventory1->change_next_item_position( this->inventory1->get_next_item_position() + weapon->item_stored->get_height() + 5);
    if(!this->inventory1->get_item_head()){
        this->inventory1->change_head(weapon);
        this->inventory1->change_tail(weapon);
    }
    else{
    this->inventory1->get_item_tail()->next_item = weapon;
    this->inventory1->change_tail(this->inventory1->get_item_tail()->next_item);
    }
}

// weapon * attacks::get_recently_equiped(){
//     //cout << this->recently_equiped->get_deleted();
//     return recently_equiped;
// }



void attacks::draw(){
    for(item_node * item_node1: this->item_list){
        if(item_node1){
            weapon * weapon1 = dynamic_cast<weapon*>(item_node1->item_stored);
            if (weapon1) {
                weapon1->draw();
            }
        }
    }
    this->weapon_input->draw();
    this->equip_button->draw();
    this->unequip_button->draw();
    DrawText(TextFormat("Weapon Name: "), this->x, this->y - 20, 15, WHITE);
    DrawText(TextFormat("Attacks"), this->x, this->y - 50, 15, WHITE);
}