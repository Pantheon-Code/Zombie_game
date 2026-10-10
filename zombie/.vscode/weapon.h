#pragma once
#include "button.h"
#include <iostream>
#include "item.h"

class item_node;
class inventory;

class weapon : public item{
    private:
        int attack, damage;
        int ammo_amount = 0;
        button * shoot;
        string ammo_type;
    public:
        weapon(int x, int y, int space, string name, int attack, int damage, string ammo_type);
        void change_position(int x, int y) override;
        // void change_deleted(bool new_deleted);
        // bool get_deleted();
        void update(item_node * item_head, inventory * inventory1);
        item_node * reload(item_node * item_head, inventory * inventory1);
        void set_ammo(int ammo_amount);
        void change_inventory();
        int get_attack();
        int get_damage();
        void draw() override;
        virtual void change_file(ofstream & myFile) override;
        static weapon * read_file(stringstream & ss);
};