#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "raylib.h"

using namespace std;

class stats_editor;

class health_editor;

class player{
    private:
    int x = 15;
    vector<string> health_vec = {"head_health", "body_health", "left_leg_health", "right_leg_health", 
        "left_arm_health", "right_arm_health"};
    vector<string> abilities_vec = {"charisma", "strength", "constitution", "dexterity", "intelligence",
         "wisdom"};
    vector<stats_editor *> stats;
    vector<health_editor *> health;
    public:
    player();
    void update();
    void draw();
};