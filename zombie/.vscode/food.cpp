#include "food.h" 
#include "button.h"

food::food(int x, int y, int space, string name, int hunger_restored) : item(x, y, space, name){
    this->hunger_restored = hunger_restored;
    this->color = GREEN;
    this->item_type = "food";
    this->eat = new button(this->x + this->width + 15, this->y, 50.0f, 20.0f, GREEN, "Eat", 20.0f);
}

bool food::pressed(){
    return this->eat->update(GetMousePosition());
}

int food::get_hunger_restored(){
    return this->hunger_restored;
}

void food::shift(int y){
    item::shift(y);
    delete this->eat;
    this->eat = new button(this->x + this->width + 15, this->y, 50.0f, 20.0f, GREEN, "Eat", 20.0f);
}

void food::change_position(int x, int y){
    item::change_position(x,y);
    delete this->eat;
    this->eat = new button(this->x + this->width + 15, this->y, 50.0f, 20.0f, GREEN, "Eat", 20.0f);
}

void food::draw(){
    this->eat->draw();
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s: HR: %i" ,this->name.c_str(), this->hunger_restored), this->x, this->y, 20, WHITE);
}

void food::change_file(ofstream & myFile){
    myFile << this->item_type << ',' << this->name << ',' << this->space << ',' << this->hunger_restored << '\n';
}

food * food::read_file(stringstream & ss){
    string name;
    getline(ss, name, ',');
    string space;
    getline(ss, space, ',');
    string hunger_restored;
    getline(ss, hunger_restored, ',');
    food * new_food = new food(0, 0, stoi(space), name, stoi(hunger_restored));
    return new_food;
}