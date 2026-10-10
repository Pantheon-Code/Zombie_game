#pragma once
#include "item.h"
#include <iostream>
#include <fstream>
#include <sstream>

class ammo: public item{
    private:
        int amount = 0;
    public:
        ammo(int x, int y, int space, string name, int amount);
        int get_amount();
        void draw() override;
        virtual void change_file(ofstream & myFile) override;
        static ammo * read_file(stringstream & ss);

};