#include "inventory.h"
#include "weapon.h"
#include "ammo.h"
#include "food.h"
#include "water.h"

inventory::inventory(){
    this->item_name = new text_input(Rectangle{(float)this->x, (float)this->y, 185, 20});
    int x_placement = this->x + 200;
    for(int i = 0; i < this->number_input_names.size(); i++){
        this->number_input_list.push_back(new number_input(Rectangle{(float)x_placement, (float)this->y, 50, 20}, 
            this->number_input_names[i]));
        x_placement += 65;
    }
    this->add_button = new button(x_placement, y, 30, 15, GREEN, "ADD", 20);
    x_placement += 45;
    this->delete_button = new button(x_placement, y, 30, 15, RED, "DELETE", 20);
    this->read_file();
}

void inventory::update(){
    this->item_name->update();
    for(int i = 0; i < this->number_input_names.size(); i++){
        this->number_input_list[i]->update();
    }
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
        while(getline(myFile, line) && !line.empty()){
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
            else if(item_type == "water"){
                new_item = water::read_file(ss);
            }
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
    unordered_map<string, int> new_item___;
    for(int i = 0; i < this->number_input_names.size(); i++){
        new_item___.emplace(this->number_input_names[i], atoi(this->number_input_list[i]->get_edit_input()));
    }

    if(new_item___["Thirst"]){
        new_item->item_stored = new water(this->x, next_item_position, new_item___["Space"], new_item_name, new_item___["Thirst"]);
    }
    else if(new_item___["Hunger"]){
        new_item->item_stored = new food(this->x, next_item_position, new_item___["Space"], new_item_name, new_item___["Hunger"]);
    }
    else if(new_item___["Amount"]){
        new_item->item_stored = new ammo(this->x, next_item_position, new_item___["Space"], new_item_name, new_item___["Amount"]);
    }
    else if(new_item___["Attack"]){
        new_item->item_stored = new weapon(this->x, next_item_position, new_item___["Space"], new_item_name, new_item___["Attack"], 0);
    }
    else new_item->item_stored = new item(this->x, next_item_position, new_item___["Space"], new_item_name);
    
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
    this->item_name->draw();
    DrawText(TextFormat("Inventory"), this->x, this->y - 40, 15, WHITE);
    for(int i = 0; i < this->number_input_names.size(); i++){
        this->number_input_list[i]->draw();
    }
    this->add_button->draw();
    this->delete_button->draw();
    this->draw_items();
}

inventory::~inventory(){
    delete this->item_name;
    this->item_name = nullptr;
    for(number_input *& number_input1 : number_input_list){
        delete number_input1;
        number_input1 = nullptr;
    }
    delete this->add_button;
    this->add_button = nullptr;
    delete this->delete_button;
    this->delete_button = nullptr;
}





