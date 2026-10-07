#pragma once
#include "stats_editor.h"
#include <sstream>

class health_editor: public stats_editor{
    private:
    int max_health = 0;
    button * add_max_health;
    public:
    health_editor(int x, int y, string name);
    void update();
    void read_file() override;
    void change_file() override;
    void add_max();
    void add() override;
    void add(int stat) override;
    int get_max();
    void draw();
};