#pragma once
#include <string>
#include "raylib.h"

using namespace std;
class item{
    protected:
    int space;
    string name;
    bool in_inventory = true;
    int x, y;
    int width = 100, height;
    string item_type = "item";
    Color color = GREEN;
    public:
    item(int x, int y, int space, string name);
    string get_name();
    int get_height();
    int get_space();
    void get_in_inventory();
    void get_out_inventory();
    virtual void change_position(int x, int y);
    string get_item_type();
    virtual void shift(int y);
    virtual void draw();
};