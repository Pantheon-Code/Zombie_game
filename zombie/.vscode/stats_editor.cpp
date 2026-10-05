#include "stats_editor.h"
#include "button.h"
#include "number_input.h"

stats_editor::stats_editor(int x, int y, string name){
    this->x = x;
    this->y = y;
    this->name = name;
    this->stats_input = new number_input(Rectangle{(float)this->x, (float)this->y, 50.0f, 20.0f});
    this->add_button = new button(x + 60, y, 30, 15, GREEN, "ADD", 20);
}

void stats_editor::update(){
    this->stats_input->update();
    if(this->add_button->update(GetMousePosition())){
        this->add();
    }
}

void stats_editor::add(){
    int num_to_add = atoi(this->stats_input->get_edit_input());
    this->stat += num_to_add;
}

void stats_editor::add(int stat){
    this->stat += stat;
}

void stats_editor::draw(){
    DrawText(TextFormat("%s: %i", this->name.c_str(), this->stat), this->x, this->y - 20, 15, WHITE);
    this->stats_input->draw();
    this->add_button->draw();
    
}
