#include "ammo.h"

ammo::ammo(int x, int y, int space, string name, int amount) : item(x, y, space, name){
    this->amount = amount;
    this->color = ORANGE;
    this->item_type = "ammo";
}

int ammo::get_amount(){
    return this->amount;
}

void ammo::draw(){
    item::draw();
    DrawText(TextFormat("Amount: %i", this->amount), this->x + this->width - 10, this->y + 10, 20, WHITE);
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