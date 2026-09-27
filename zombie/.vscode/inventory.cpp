#include "inventory.h"
#include "attacks.h"


inventory::inventory(int y, int max_item_amount, attacks * attacks1) : 
    item_name_input(Rectangle{(float)this->x, (float)y, 185.0f, 20.0f}) ,
    item_space_input(Rectangle{1025.0f, (float)y, 50.0f, 20.0f}), 
    item_amount_input(Rectangle{1125.0f, (float)y, 50.0f, 20.0f}),
    attack_points_input(Rectangle{(float)this->x, (float)y + 85, 50.0f, 20.0f}),
    damage_points_input(Rectangle{(float)this->x + 100, (float)y + 85, 50.0f, 20.0f}),
    add_item_button(this->x, y + 30, 20, 20, GREEN, "add item", 20),
    delete_item_button(this->x + 80, y + 30, 20, 20, GREEN, "delete item", 20),
    add_weapon_button(this->x + 160, y + 30, 20, 20, GREEN, "add food", 20){
    this->y = y;
    this->max_item_amount = max_item_amount;
    this->height = 100 * max_item_amount;
    this->next_item_spot = this->y + 130;
    this->attacks1 = attacks1;
}

void inventory::update(){
    item_name_input.update();
    item_space_input.update();
    item_amount_input.update();
    attack_points_input.update();
    damage_points_input.update();
    if(this->add_item_button.update(GetMousePosition())){
        this->add_item();
    }
    if(this->delete_item_button.update(GetMousePosition())){
        this->delete_item(item_name_input.get_edit_input());
    }

}

void inventory::add_item(){
    if(this->item_map.count(item_name_input.get_edit_input())){
        return;
    }
    int item_space = atoi(item_space_input.get_edit_input());
    string item_name = item_name_input.get_edit_input();
    int attack_points = atoi(this->attack_points_input.get_edit_input());
    int damage_points = atoi(this->damage_points_input.get_edit_input());
    if(item_space && item_space + this->space_taken <= this->max_item_amount){
        this->space_taken += item_space;
        this->item_map.emplace(item_name, this->item_vec.size());
        if(attack_points){
            weapon * weapon1 = new weapon(this->x, next_item_spot, item_space, item_name, attack_points, damage_points);
            this->weapon_map.emplace(item_name, this->weapon_vec.size());
            this->weapon_vec.push_back(weapon1); 
            this->item_vec.push_back(weapon1);
        }
        else{
            item * item1 = new item(this->x, this->next_item_spot, item_space, item_name_input.get_edit_input());
            this->item_vec.push_back(item1);
        }
        this->next_item_spot += (20 * item_space) + (5 * item_space);
        item_name_input.delete_text();
        item_space_input.delete_text();
        item_amount_input.delete_text();
        attack_points_input.delete_text();
        damage_points_input.delete_text();
        
    }
}

void inventory::add_back_item(string item_to_add_back){
    int item_space = this->weapon_vec[this->weapon_map[item_to_add_back]]->get_space();

    string item_name = this->weapon_vec[this->weapon_map[item_to_add_back]]->get_name();
  
    if(item_space && item_space + this->space_taken <= this->max_item_amount){
  
        this->space_taken += item_space;
        this->item_map.emplace(item_name, this->item_vec.size());
      
        this->item_vec.push_back(this->weapon_vec[this->weapon_map[item_to_add_back]]);
        this->item_vec.back()->shift(this->item_vec.back()->get_y() - next_item_spot);
  
        this->next_item_spot += (20 * item_space) + (5 * item_space);

    }
}

void inventory::delete_item(string item_to_delete){
    if(!this->item_map.count(item_to_delete)){
        return;
    }
    int item_to_delete_index = this->item_map[item_to_delete];
    int item_to_delete_height = this->item_vec[this->item_map[item_to_delete]]->get_height();
    if(this->weapon_map.count(item_to_delete)){
        this->weapon_vec.erase(this->weapon_vec.begin() + item_to_delete_index);
        for(int i = item_to_delete_index; i < this->weapon_vec.size(); i++){
            this->weapon_map[this->weapon_vec[i]->get_name()] = this->weapon_map[this->weapon_vec[i]->get_name()] - 1;
            this->weapon_vec[i]->shift(item_to_delete_height + 5);
        }
        this->weapon_map.erase(item_to_delete);
    }
    this->next_item_spot -= item_to_delete_height + 5;
    this->space_taken -= item_to_delete_height / 25 + 1;
    delete this->item_vec[item_to_delete_index];
    this->item_vec.erase(this->item_vec.begin() + item_to_delete_index);
    for(int i = item_to_delete_index; i < this->item_vec.size(); i++){
        this->item_map[this->item_vec[i]->get_name()] = this->item_map[this->item_vec[i]->get_name()] - 1;
        this->item_vec[i]->shift(item_to_delete_height + 5);
    }
    this->item_map.erase(item_to_delete);
    
}

void inventory::remove_item(string item_to_remove){
    int item_to_delete_index = this->item_map[item_to_remove];
    int item_to_delete_height = this->item_vec[this->item_map[item_to_remove]]->get_height();
    this->next_item_spot -= item_to_delete_height + 5;
    this->space_taken -= item_to_delete_height / 25 + 1;
    this->item_vec.erase(this->item_vec.begin() + item_to_delete_index);
    for(int i = item_to_delete_index; i < this->item_vec.size(); i++){
        this->item_map[this->item_vec[i]->get_name()] = this->item_map[this->item_vec[i]->get_name()] - 1;
        this->item_vec[i]->shift(item_to_delete_height + 5);
    }
    this->item_map.erase(item_to_remove);
}

vector<weapon *> * inventory::get_weapon_vec(){
    return &this->weapon_vec;
}

unordered_map<string, int> * inventory::get_weapon_map(){
    return &this->weapon_map;
}

void inventory::draw(){
    this->item_amount_input.draw();
    DrawText(TextFormat("Item Amount: "), 1125, this->y - 25, 15, WHITE);
    this->item_space_input.draw();
    DrawText(TextFormat("Item Space: "), 1025, this->y - 25, 15, WHITE);
    this->item_name_input.draw();
    DrawText(TextFormat("Item Name: "), this->x, this->y - 25, 15, WHITE);
    this->attack_points_input.draw();
    DrawText(TextFormat("Attack Bonus: "), this->x, this->y + 60, 15, WHITE);
    this->damage_points_input.draw();
    DrawText(TextFormat("Damage Bonus: "), this->x + 100, this->y + 60, 15, WHITE);
    this->add_item_button.draw();
    this->delete_item_button.draw();
    this->add_weapon_button.draw();

    for(item * item1: this->item_vec){
        item1->get_name();
        if(item1) item1->draw();
    }


}

inventory::~inventory(){

    this->item_vec.clear();

}




