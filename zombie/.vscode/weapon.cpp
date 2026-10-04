#include "weapon.h"
#include "inventory.h"
#include "ammo.h"

weapon::weapon(int x, int y, int space, string name, int attack, int damage) : item(x, y, space, name){
    
    this->attack = attack;
    this->damage = damage;
    this->color = GRAY;
    this->item_type = "weapon";
}

void weapon::update(item_node * item_head, inventory * inventory1){
    if(this->shoot && this->shoot->update(GetMousePosition())){
        this->ammo_amount--;
        if(this->ammo_amount <= 0){
            item_node * ammo_node = (this->reload(item_head, inventory1));
            if(ammo_node){
                cout << "HELLO";
                ammo * new_ammo = dynamic_cast<ammo*>(ammo_node->item_stored);
                this->ammo_amount += new_ammo->get_amount();
            }
            delete ammo_node;
        }
    }
}

item_node * weapon::reload(item_node * item_head, inventory * inventory1){
    if(!inventory1->get_item_head()) return nullptr;
    item_node * dummy_ptr1 = nullptr;
    item_node * dummy_ptr2 = inventory1->get_item_head();
    if(dummy_ptr2->item_stored->get_name() == this->ammo_type && dummy_ptr2->item_stored->get_item_type() == "ammo"){
        int deleted_height = dummy_ptr2->item_stored->get_height();
        inventory1->change_head(dummy_ptr2->next_item);
        if(!dummy_ptr2->next_item) inventory1->change_tail(dummy_ptr2->next_item);
        inventory1->shift_items(deleted_height + 5, dummy_ptr2->next_item);
        dummy_ptr2->next_item = nullptr;
        return dummy_ptr2;
    }
    dummy_ptr1 = dummy_ptr2;
    dummy_ptr2 = dummy_ptr2->next_item;
    while(dummy_ptr2){
        if(dummy_ptr2->item_stored->get_name() == this->ammo_type && dummy_ptr2->item_stored->get_item_type() == "ammo"){
            int deleted_height = dummy_ptr2->item_stored->get_height() + 5;
            dummy_ptr1->next_item = dummy_ptr2->next_item;
            inventory1->shift_items(deleted_height, dummy_ptr1->next_item);
            if(dummy_ptr2 == inventory1->get_item_tail()) inventory1->change_tail(dummy_ptr1);
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
void weapon::change_position(int x, int y){
    item::change_position(x, y);
    delete this->shoot;
    this->shoot = new button(this->x + 115, y, 30, 15, BLUE, "SHOOT", 20);
}
// void weapon::change_inventory(){
//     this->height = 30;
// }

// void weapon::change_deleted(bool new_deleted){
//     this->deleted = new_deleted;
// }

// bool weapon::get_deleted(){
//     return deleted;
// }

void weapon::draw(){
    item::draw();
    if(!this->in_inventory) this->shoot->draw();
    // DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    // DrawText(TextFormat("%s" ,this->name.c_str()), this->x, this->y + 10, 20, WHITE);
    DrawText(TextFormat("%s: %i" ,this->ammo_type.c_str(), this->ammo_amount), this->x + this->width - 10, this->y + 10, 20, WHITE);

}