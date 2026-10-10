#include "water.h" 
#include "button.h"

water::water(int x, int y, int space, string name, int thirst_quenched) : item(x, y, space, name){
    this->thirst_quenched = thirst_quenched;
    this->color = BLUE;
    this->item_type = "water";
    this->drink = new button(this->x + this->width + 15, this->y, 50.0f, 20.0f, BLUE, "Drink", 20.0f);
    string text_to_measure = this->name + ": TQ: " + to_string(this->thirst_quenched) + "  ";
    this->width = MeasureText(text_to_measure.c_str(), 20);
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
    this->drink = new button((float)this->x + this->width + 15, this->y, 50.0f, 20.0f, BLUE, "Drink", 20.0f);
}

void water::change_position(int x, int y){
    cout << "HEYY";
    item::change_position(x,y);
    delete this->drink;
    this->drink = new button((float)this->x + this->width + 15, this->y, 50.0f, 20.0f, BLUE, "Drink", 20.0f);
}

void water::draw(){
    this->drink->draw();
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s: TQ: %i" ,this->name.c_str(), this->thirst_quenched), this->x, this->y, 20, WHITE);
}

void water::change_file(ofstream & myFile){
    myFile << this->item_type << ',' << this->name + ',' << this->space << ',' << this->thirst_quenched << '\n';
}

water * water::read_file(stringstream & ss){
    string name;
    getline(ss, name, ',');
    string space;
    getline(ss, space, ',');
    string thirst_quenched;
    getline(ss, thirst_quenched, ',');
    water * new_water = new water(0, 0, stoi(space), name, stoi(thirst_quenched));
    return new_water;
}