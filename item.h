#pragma once
#include <string>
#include "raylib.h"

using namespace std;
class item{
    protected:
    int space;
    string name;
    int x, y;
    int width = 100, height;
    Color color = GREEN;
    public:
    item();
    item(int x, int y, int space, string name);
    string get_name();
    int get_height();
    void shift(int y);
    void draw();
};