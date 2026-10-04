#include "health_editor.h"
#include "button.h"
#include "number_input.h"

health_editor::health_editor(int x, int y, string name) : 
stats_editor(x, y, name){
    this->add_max_health = new button(x + 105, y, 30, 15, GREEN, "ADD MAX HEALTH", 20);
}
void health_editor::update(){
    stats_editor::update();
    if(this->add_max_health->update(GetMousePosition())){
        this->add_max();
    }
}
void health_editor::add_max(){
    int max_to_add = atoi(this->stats_input->get_edit_input());
    this->max_health += max_to_add;
}
void health_editor::draw(){
    DrawText(TextFormat("%s: %i/%i", this->name.c_str(), this->max_health, this->stat), this->x, this->y - 20, 15, WHITE);
    this->stats_input->draw();
    this->add_button->draw();
    this->add_max_health->draw();
}