#include "ammo.h"

ammo::ammo(int x, int y, int space, string name, int amount) : item(x, y, space, name){
    this->amount = amount;
    this->color = ORANGE;
    this->item_type = "ammo";
    string text_to_measure = this->name + ": Amouny: " + to_string(this->amount) + "  ";
    this->width = MeasureText(text_to_measure.c_str(), 20);
}

int ammo::get_amount(){
    return this->amount;
}

void ammo::draw(){
    DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    DrawText(TextFormat("%s: Amount: %i" ,this->name.c_str(), this->amount), this->x, this->y, 20, WHITE);
}

void ammo::change_file(ofstream & myFile){
    myFile << this->item_type << ',' << this->name << ',' << this->space << ',' << this->amount << '\n';
}

ammo * ammo::read_file(stringstream & ss){
    string name;
    getline(ss, name, ',');
    string space;
    getline(ss, space, ',');
    string amount;
    getline(ss, amount, ',');
    ammo * new_ammo = new ammo(0, 0, stoi(space), name, stoi(amount));
    return new_ammo;
}