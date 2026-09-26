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
    Color color = GREEN;
    public:
    item(int x, int y, int space, string name);
    string get_name();
    int get_height();
    bool get_in_inventory();
    int get_space();
    void shift(int y);
    void draw();
};