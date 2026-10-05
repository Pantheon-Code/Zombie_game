#include "necessities.h"
#include "health_editor.h"
#include "inventory.h"

necessities::necessities(inventory * inventory1){
    this->hunger = new health_editor(this->x, this->y, "hunger");
    this->thirst = new health_editor(this->x, this->y + 60, "thirst");
    this->inventory1 = inventory1;
}

void necessities::update(){
    this->hunger->update();
    this->thirst->update();
    item_node * dummy_ptr = inventory1->get_item_head();
    while(dummy_ptr){
        item_node * next_dummy_ptr = dummy_ptr->next_item;
        if(dummy_ptr->item_stored->get_item_type() == "food"){
            food * dummy_food = dynamic_cast<food*>(dummy_ptr->item_stored);
            if(dummy_food->pressed()){
                this->hunger->add(dummy_food->get_hunger_restored());
                this->consume(dummy_ptr->item_stored);
                delete dummy_food;
                dummy_food = nullptr;
                delete dummy_ptr;
                dummy_ptr = nullptr;
                return;
            }
            
        }
        else if(dummy_ptr->item_stored->get_item_type() == "water"){
            water * dummy_water = dynamic_cast<water*>(dummy_ptr->item_stored);
            if(dummy_water->pressed()){
                this->thirst->add(dummy_water->get_thirst_quenched());
                this->consume(dummy_ptr->item_stored);
                delete dummy_water;
                dummy_water = nullptr;
                delete dummy_ptr;
                dummy_ptr = nullptr;
                return;
            }
            
        }
        dummy_ptr = next_dummy_ptr;
    }
}

void necessities::consume(item * to_consume){
    if(!inventory1->get_item_head()) return;
    item_node * dummy_ptr1 = nullptr;
    item_node * dummy_ptr2 = inventory1->get_item_head();
    if(dummy_ptr2->item_stored == to_consume){
        int deleted_height = dummy_ptr2->item_stored->get_height();
        inventory1->change_head(dummy_ptr2->next_item);
        if(!dummy_ptr2->next_item) inventory1->change_tail(dummy_ptr2->next_item);
        inventory1->shift_items(deleted_height + 5, dummy_ptr2->next_item);
        dummy_ptr2->next_item = nullptr;
        return;
    }
    dummy_ptr1 = dummy_ptr2;
    dummy_ptr2 = dummy_ptr2->next_item;
    while(dummy_ptr2){
        if(dummy_ptr2->item_stored == to_consume){
            int deleted_height = dummy_ptr2->item_stored->get_height() + 5;
            dummy_ptr1->next_item = dummy_ptr2->next_item;
            inventory1->shift_items(deleted_height, dummy_ptr1->next_item);
            if(dummy_ptr2 == inventory1->get_item_tail()) inventory1->change_tail(dummy_ptr1);
            dummy_ptr2->next_item = nullptr;
            return;
        }
        else{
            dummy_ptr1 = dummy_ptr2;
            dummy_ptr2 = dummy_ptr2->next_item;
        }
    }
}

void necessities::draw(){
    this->hunger->draw();
    this->thirst->draw();
}