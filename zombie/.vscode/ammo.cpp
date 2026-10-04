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