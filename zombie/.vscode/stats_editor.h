#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

class number_input;

class button;


using namespace std;
class stats_editor{
    protected:
    button * add_button;
    number_input * stats_input;
    string name;
    int stat = 0;
    int x, y;
    public:
    stats_editor(int x, int y, string name); 
    void update();
    virtual void read_file();
    virtual void change_file();
    virtual void add();
    virtual void add(int stat);
    void draw();
    ~stats_editor();
};