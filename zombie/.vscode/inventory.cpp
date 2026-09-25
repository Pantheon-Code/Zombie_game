#include "inventory.h"

inventory::inventory(int y, int max_item_amount, attacks * attacks1) : 
    item_name(Rectangle{(float)this->x, (float)y, 185.0f, 20.0f}) ,
    item_space(Rectangle{1025.0f, (float)y, 50.0f, 20.0f}), 
    item_amount(Rectangle{1125.0f, (float)y, 50.0f, 20.0f}),
    attack_points(Rectangle{(float)this->x, (float)y + 85, 50.0f, 20.0f}),
    damage_points(Rectangle{(float)this->x + 100, (float)y + 85, 50.0f, 20.0f}),
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
    item_name.update();
    item_space.update();
    item_amount.update();
    attack_points.update();
    damage_points.update();
    if(this->add_item_button.update(GetMousePosition())){
        this->add_item();
    }
    if(this->delete_item_button.update(GetMousePosition())){
        this->delete_item(item_name.get_edit_input());
    }
    if(attacks1->get_recently_equiped()){
        //cout << "YOOOOOOO";
        weapon * to_delete = attacks1->get_recently_equiped();
        if(to_delete->get_deleted()){
            cout << "YOOO";
            //THIS ONE IS ERROR
            to_delete->change_deleted(false);
            delete_item(*to_delete);
            
        }
    }
}

void inventory::add_item(){
    if(this->item_list.count(item_name.get_edit_input())){
        return;
    }
    int item_space_number = atoi(item_space.get_edit_input());
    if(item_space_number && item_space_number + this->space_taken <= this->max_item_amount){
        this->space_taken += item_space_number;
        this->item_list.emplace(this->item_name.get_edit_input(), this->item_list_vec.size());
        if(atoi(this->attack_points.get_edit_input())){
            this->item_list_vec.push_back(attacks1->add_weapon(this->x, this->next_item_spot, item_space_number, 
                this->item_name.get_edit_input(), atoi(this->attack_points.get_edit_input()), 
                atoi(this->damage_points.get_edit_input())));
                cout << "WEAPON: " << ((30 * item_space_number) + (10 * item_space_number));
        }
        else{
            item * item1 = new item(this->x, this->next_item_spot, item_space_number, item_name.get_edit_input());
            this->item_list_vec.push_back(item1);
            cout << "ITEM: " << ((30 * item_space_number) + (10 * item_space_number));
        }
        this->next_item_spot += (30 * item_space_number) + (10 * item_space_number);
        cout << "next item spot: " << next_item_spot;
        item_name.delete_text();
        item_space.delete_text();
        item_amount.delete_text();
        
    }
}


void inventory::delete_item(string item_to_delete){
    if(!this->item_list.count(item_to_delete)){
        return;
    }
    int item_to_delete_index = this->item_list[item_to_delete];
    int item_to_delete_height = this->item_list_vec[this->item_list[item_to_delete]]->get_height();
    this->attacks1->delete_weapon(item_to_delete);
    this->next_item_spot -= item_to_delete_height + 10;
    this->space_taken -= item_to_delete_height / 40 + 1;
    this->item_list_vec.erase(this->item_list_vec.begin() + item_to_delete_index);
    for(int i = item_to_delete_index; i < this->item_list_vec.size(); i++){
        this->item_list[this->item_list_vec[i]->get_name()] = this->item_list[this->item_list_vec[i]->get_name()] - 1;
        this->item_list_vec[i]->shift(item_to_delete_height + 10);
    }
    this->item_list.erase(item_to_delete);
    
}

void inventory::delete_item(weapon weapon_to_delete){
    string item_to_delete = weapon_to_delete.get_name();
    cout << item_to_delete;
    int item_to_delete_index = this->item_list[item_to_delete];
    cout << item_to_delete_index;
    int item_to_delete_height = weapon_to_delete.get_height();
    cout << item_to_delete_height;
    this->next_item_spot -= item_to_delete_height + 10;
    this->space_taken -= item_to_delete_height / 40 + 1;
    this->item_list_vec.erase(this->item_list_vec.begin() + item_to_delete_index);
    for(int i = item_to_delete_index; i < this->item_list_vec.size(); i++){
        this->item_list[this->item_list_vec[i]->get_name()] = this->item_list[this->item_list_vec[i]->get_name()] - 1;
        this->item_list_vec[i]->shift(item_to_delete_height + 10);
    }
    this->item_list.erase(item_to_delete);
    cout << "BROO";
}

void inventory::draw(){
    this->item_amount.draw();
    DrawText(TextFormat("Item Amount: "), 1125, this->y - 25, 15, WHITE);
    this->item_space.draw();
    DrawText(TextFormat("Item Space: "), 1025, this->y - 25, 15, WHITE);
    this->item_name.draw();
    DrawText(TextFormat("Item Name: "), this->x, this->y - 25, 15, WHITE);
    this->attack_points.draw();
    DrawText(TextFormat("Attack Bonus: "), this->x, this->y + 60, 15, WHITE);
    this->damage_points.draw();
    DrawText(TextFormat("Damage Bonus: "), this->x + 100, this->y + 60, 15, WHITE);
    this->add_item_button.draw();
    this->delete_item_button.draw();
    this->add_weapon_button.draw();

    for(item * item1: this->item_list_vec){
        if(item1) item1->draw();
    }


}






