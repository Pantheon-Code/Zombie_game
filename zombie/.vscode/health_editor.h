#pragma once
#include "stats_editor.h"

class health_editor: public stats_editor{
    private:
    int max_health = 0;
    button * add_max_health;
    public:
    health_editor(int x, int y, string name);
    void update();
    void add_max();
    void add() override;
    void add(int stat) override;
    int get_max();
    void draw();
};