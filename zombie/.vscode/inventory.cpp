#include "inventory.h"
#include "weapon.h"
#include "ammo.h"
#include "food.h"
#include "water.h"

inventory::inventory(){
    this->item_name = new text_input(Rectangle{(float)this->x, (float)this->y, 185, 20});
    this->item_space = new number_input(Rectangle{(float)this->x + 200, (float)this->y, 50, 20});
    this->attack_roll = new number_input(Rectangle{(float)this->x + 265, (float)this->y, 50, 20});
    this->amount = new number_input(Rectangle{(float)this->x + 330, (float)this->y, 50, 20});
    this->hunger_restored = new number_input(Rectangle{(float)this->x + 395, (float)this->y, 50, 20});
    this->thirst_quenched = new number_input(Rectangle{(float)this->x + 460, (float)this->y, 50, 20});
    this->add_button = new button(x + 525, y, 30, 15, GREEN, "ADD", 20);
    this->delete_button = new button(x + 570, y, 30, 15, RED, "DELETE", 20);
    this->read_file();
}

void inventory::update(){
    this->item_name->update();
    this->item_space->update();
    this->attack_roll->update();
    this->amount->update();
    this->hunger_restored->update();
    this->thirst_quenched->update();
    if(this->add_button->update(GetMousePosition())){
        this->add_item();
    }
    if(this->delete_button->update(GetMousePosition())){
        this->delete_item();
    }
}

void inventory::read_file(){
    ifstream myFile(this->inventory_file);
    if(myFile.is_open()){
        string line;
        while(getline(myFile, line)){
            stringstream ss(line);
            string item_type;
            getline(ss, item_type, ',');
            item * new_item;
            if(item_type == "item"){
                new_item = item::read_file(ss);
            }
            else if(item_type == "weapon"){
                new_item = weapon::read_file(ss);
            }
            else if(item_type == "ammo"){
                new_item = ammo::read_file(ss);
            }
            else if(item_type == "food"){
                new_item = food::read_file(ss);
            }
            else new_item = water::read_file(ss);
            item_node * new_item_node = new item_node;
            new_item_node->item_stored = new_item;
            this->add_item(new_item_node);
        }
    }
}

void inventory::change_file(){
    item_node * dummy_node = this->item_head;
    ofstream myFile(this->inventory_file);
    if(myFile.is_open()){
        while(dummy_node){
            item * dummy_item = dummy_node->item_stored;
            dummy_item->change_file(myFile);
            dummy_node = dummy_node->next_item;
        }
        
    }
    myFile.close();
}

void inventory::add_item(){
    item_node * new_item = new item_node;
    string new_item_name = this->item_name->get_edit_input();
    int new_item_space = atoi(this->item_space->get_edit_input());
    int new_item_attack = atoi(this->attack_roll->get_edit_input());
    int new_item_amount = atoi(this->amount->get_edit_input());
    int new_item_hunger_restored = atoi(this->hunger_restored->get_edit_input());
    int new_item_thirst_quenched = atoi(this->thirst_quenched->get_edit_input());

    if(new_item_thirst_quenched){
        new_item->item_stored = new water(this->x, next_item_position, new_item_space, new_item_name, new_item_thirst_quenched);
    }
    else if(new_item_hunger_restored){
        new_item->item_stored = new food(this->x, next_item_position, new_item_space, new_item_name, new_item_hunger_restored);
    }
    else if(new_item_amount){
        new_item->item_stored = new ammo(this->x, next_item_position, new_item_space, new_item_name, new_item_amount);
    }
    else if(new_item_attack){
        new_item->item_stored = new weapon(this->x, next_item_position, new_item_space, new_item_name, new_item_attack, 0);
    }
    else new_item->item_stored = new item(this->x, next_item_position, new_item_space, new_item_name);
    
    next_item_position += new_item->item_stored->get_height() + 5;
    if(!this->item_head){
        this->item_head = new_item;
        this->item_tail = new_item;
    }
    else{
    this->item_tail->next_item = new_item;
    this->item_tail = this->item_tail->next_item;
    }
}

void inventory::add_item(item_node * new_item){
    new_item->item_stored->change_position(this->x, this->next_item_position);
    
    next_item_position += new_item->item_stored->get_height() + 5;
    if(!this->item_head){
        this->item_head = new_item;
        this->item_tail = new_item;
    }
    else{
    this->item_tail->next_item = new_item;
    this->item_tail = this->item_tail->next_item;
    }
}

void inventory::delete_item(){
    if(!this->item_head) return;
    string new_item_name = this->item_name->get_edit_input();
    item_node * dummy_ptr1 = nullptr;
    item_node * dummy_ptr2 = this->item_head;
    if(this->item_head->item_stored->get_name() == new_item_name){
        int deleted_height = this->item_head->item_stored->get_height();
        this->item_head = this->item_head->next_item;
        if(!this->item_head) this->item_tail = this->item_head;
        this->shift_items(deleted_height + 5, this->item_head);
        delete dummy_ptr2;
        return;
    }
    dummy_ptr1 = dummy_ptr2;
    dummy_ptr2 = this->item_head->next_item;
    while(dummy_ptr2){
        if(dummy_ptr2->item_stored->get_name() == new_item_name){
            int deleted_height = dummy_ptr2->item_stored->get_height() + 5;
            dummy_ptr1->next_item = dummy_ptr2->next_item;
            this->shift_items(deleted_height, dummy_ptr1->next_item);
            if(dummy_ptr2 == this->item_tail) this->item_tail = dummy_ptr1;
            delete dummy_ptr2;
            dummy_ptr2 = nullptr;
            return;
        }
        else{
            dummy_ptr1 = dummy_ptr2;
            dummy_ptr2 = dummy_ptr2->next_item;
        }
    }

}

void inventory::shift_items(int item_height, item_node * dummy_ptr1){
    item_node * dummy_ptr = dummy_ptr1;
    this->next_item_position -= item_height;
    while(dummy_ptr){
        dummy_ptr->item_stored->shift(item_height);
        dummy_ptr = dummy_ptr->next_item;
    }
}


void inventory::draw_items(){
    item_node * dummy_ptr = this->item_head;
    while(dummy_ptr){
        dummy_ptr->item_stored->draw();
        dummy_ptr = dummy_ptr->next_item;
    }
    

}

void inventory::change_tail(item_node * new_tail){
    this->item_tail = new_tail;
}


void inventory::change_head(item_node * new_head){
    this->item_head = new_head;
}

void inventory::change_next_item_position(int next_item_position){
    this->next_item_position = next_item_position;
}

item_node * inventory::get_item_head(){
    return this->item_head;
}

item_node * inventory::get_item_tail(){
    return this->item_tail;
}

int inventory::get_next_item_position(){
    return this->next_item_position;
}

void inventory::draw(){
    DrawText(TextFormat("Weapon Name"), this->x, this->y - 20, 15, WHITE);
    DrawText(TextFormat("Space"), this->x + 200, this->y - 20, 15, WHITE);
    DrawText(TextFormat("Attack"), this->x + 265, this->y - 20, 15, WHITE);
    DrawText(TextFormat("Amount"), this->x + 325, this->y - 20, 15, WHITE);
    DrawText(TextFormat("Hunger"), this->x + 395, this->y - 20, 15, WHITE);
    DrawText(TextFormat("Thirst"), this->x + 460, this->y - 20, 15, WHITE);
    DrawText(TextFormat("Inventory"), this->x, this->y - 50, 15, WHITE);
    this->item_name->draw();
    this->item_space->draw();
    this->attack_roll->draw();
    this->amount->draw();
    this->hunger_restored->draw();
    this->thirst_quenched->draw();
    this->add_button->draw();
    this->delete_button->draw();
    this->draw_items();
}

inventory::~inventory(){
    delete this->item_name;
    this->item_name = nullptr;
    delete this->item_space;
    this->item_space = nullptr;
    delete this->attack_roll;
    this->attack_roll = nullptr;
    delete this->amount;
    this->amount = nullptr;
    delete this->hunger_restored;
    this->hunger_restored = nullptr;
    delete this->thirst_quenched;
    this->thirst_quenched = nullptr;
    delete this->add_button;
    this->add_button = nullptr;
    delete this->delete_button;
    this->delete_button = nullptr;
}





