#include "player.h"

player::player(int health[6], int abilities[6], int max_hunger, int max_thirst) : 
hunger_input(Rectangle{20.0f, 445.0f, 50.0f, 20.0f}), thirst_input(Rectangle{260.0f, 445.0f, 50.0f, 20.0f}),
hunger_buttons(button(90, 445, 20, 20, GREEN, "Add", 20), button(120, 445, 20, 20, RED, "Subtract", 20)),
thirst_buttons(button(330, 445, 20, 20, GREEN, "Add", 20), button(360, 445, 20, 20, RED, "Subtract", 20)){
    for(int i = 0; i < this->health_vec.size(); i++){
        this->health.insert({this->health_vec[i], {health[i], health[i]}});
        
        number_input text_input1(Rectangle{(float)(i % 3) * 240 + 20, (float)240 + (50 * (i / 3)), 50, 20});
        button add_button((i % 3) * 240 + 90, 240 + (50 * (i / 3)), 20, 20, GREEN, "Add", 20);
        button subtract_button((i % 3) * 240 + 120, 240 + (50 * (i / 3)), 20, 20, RED, "Subract", 20);
        this->health_input.push_back(text_input1);
        add_button.onClick = [this, i](){this->change_health(this->health_vec[i], atoi(this->health_input[i].get_edit_input()));};
        subtract_button.onClick = [this, i](){this->change_health(this->health_vec[i], -atoi(this->health_input[i].get_edit_input()));};
        this->health_buttons.push_back({add_button, subtract_button});
    }
    for(int j = 0; j < this->abilities_vec.size(); j++){
        this->abilities.insert({this->abilities_vec[j], abilities[j]});
        number_input text_input1(Rectangle{(float)(j % 3) * 240 + 20, (float)45 + (50 * (j / 3)), 50, 20});
        button add_button((j % 3) * 240 + 90, 45 + (50 * (j / 3)),  20, 20, GREEN, "Add", 20);
        button subtract_button((j % 3) * 240 + 120, 45 + (50 * (j / 3)), 20, 20, RED, "Subract", 20);
        this->abilities_input.push_back(text_input1);
        add_button.onClick = [this, j](){this->change_abilities(this->abilities_vec[j], atoi(this->abilities_input[j].get_edit_input()));};
        subtract_button.onClick = [this, j](){this->change_abilities(this->abilities_vec[j], -atoi(this->abilities_input[j].get_edit_input()));};
        this->abilities_buttons.push_back({add_button, subtract_button});
        
    }
    this->max_hunger = this->hunger = max_hunger;
    hunger_buttons.first.onClick = [this](){this->change_hunger(atoi(this->hunger_input.get_edit_input()));};
    hunger_buttons.second.onClick = [this](){this->change_hunger(-atoi(this->hunger_input.get_edit_input()));};
    
    this->max_thirst = this->thirst = max_thirst;
    thirst_buttons.first.onClick = [this](){this->change_thirst(atoi(this->thirst_input.get_edit_input()));};
    thirst_buttons.second.onClick = [this](){this->change_thirst(-atoi(this->thirst_input.get_edit_input()));};
    
    
}

void player::update(){
    for(int i = 0; i < this->health_input.size(); i++){
        this->health_input[i].update();
        if(this->health_buttons[i].first.update(GetMousePosition())){
            this->health_buttons[i].first.click();
        }
        if(this->health_buttons[i].second.update(GetMousePosition())){
            this->health_buttons[i].second.click();
        }
    }
    for(int j = 0; j < this->abilities_input.size(); j++){
        this->abilities_input[j].update();
        if(this->abilities_buttons[j].first.update(GetMousePosition())){
            this->abilities_buttons[j].first.click();
        }
        if(this->abilities_buttons[j].second.update(GetMousePosition())){
            this->abilities_buttons[j].second.click();
        }
    }
    this->hunger_input.update();
    this->thirst_input.update();
    if(this->hunger_buttons.first.update(GetMousePosition())){
        this->hunger_buttons.first.click();
    }
    if(this->hunger_buttons.second.update(GetMousePosition())){
        this->hunger_buttons.second.click();
    }
    if(this->thirst_buttons.first.update(GetMousePosition())){
        this->thirst_buttons.first.click();
    }
    if(this->thirst_buttons.second.update(GetMousePosition())){
        this->thirst_buttons.second.click();
    }

}

void player::change_health(string health_location, int health_change_amount){
    this->health[health_location].first = this->health[health_location].first + health_change_amount;

}

void player::change_abilities(string ability_to_change, int ability_change_amount){
    this->abilities[ability_to_change] = this->abilities[ability_to_change] + ability_change_amount;
}

void player::change_hunger(int hunger_change){
    this->hunger += hunger_change;
}

void player::change_thirst(int thirst_change){
    this->thirst += thirst_change;
}


void player::draw(){
    for(int i = 0; i < this->abilities_vec.size(); i++){
        DrawText(TextFormat("%s : %i" ,this->abilities_vec[i].c_str() ,
            this->abilities[this->abilities_vec[i]]), (i % 3) * 240 + 20, 20 + (50 * (i / 3)), 15, WHITE);
        this->abilities_input[i].draw();
        this->abilities_buttons[i].first.draw();
        this->abilities_buttons[i].second.draw();
    }
    for(int j = 0; j < this->health_vec.size(); j++){
        DrawText(TextFormat("%s : %i / %i" ,this->health_vec[j].c_str() ,
            this->health[this->health_vec[j]].first, this->health[this->health_vec[j]].second), 
            (j % 3) * 240 + 20, 220 + (50 * (j / 3)), 15, WHITE);
        this->health_input[j].draw();
        this->health_buttons[j].first.draw();
        this->health_buttons[j].second.draw();
    }
    DrawText(TextFormat("max_hunger : %i / %i" , this->hunger, this->max_hunger), 20, 420, 15, WHITE);
    this->hunger_input.draw();
    this->hunger_buttons.first.draw();
    this->hunger_buttons.second.draw();
    DrawText(TextFormat("max_thirst : %i / %i" , this->thirst, this->max_thirst), 260, 420, 15, WHITE);
    this->thirst_input.draw();
    this->thirst_buttons.first.draw();
    this->thirst_buttons.second.draw();
}