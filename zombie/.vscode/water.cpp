#include "water.h" 
#include "button.h"

water::water(int x, int y, int space, string name, int thirst_quenched) : item(x, y, space, name){
    this->thirst_quenched = thirst_quenched;
    this->color = BLUE;
    this->item_type = "water";
    this->drink = new button(this->x + this->width + 15, this->y, 50.0f, 20.0f, BLUE, "Drink", 20.0f);
}

bool water::pressed(){
    return this->drink->update(GetMousePosition());
}

int water::get_thirst_quenched(){
    return this->thirst_quenched;
}

void water::shift(int y){
    item::shift(y);
    delete this->drink;
    this->drink = new button(this->x + this->width + 15, this->y, 50.0f, 20.0f, GREEN, "Drink", 20.0f);
}

void water::draw(){
    this->drink->draw();
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s: HR: %i" ,this->name.c_str(), this->thirst_quenched), this->x, this->y, 20, WHITE);
}