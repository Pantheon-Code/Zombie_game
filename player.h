#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "number_input.h"
#include "button.h"
#include "raylib.h"

using namespace std;

class player{
    private:
    vector<string> health_vec = {"head_health", "body_health", "left_leg_health", "right_leg_health", 
        "left_arm_health", "right_arm_health"};
    unordered_map<string, pair<int, int>> health;
    vector<number_input> health_input;
    vector<pair<button, button>> health_buttons;
    vector<string> abilities_vec = {"charisma", "strength", "constitution", "dexterity", "intelligence", "wisdeom"};
    unordered_map<string, int> abilities;
    vector<number_input> abilities_input;
    vector<pair<button, button>> abilities_buttons;
    int hunger, max_hunger, thirst, max_thirst;
    number_input hunger_input;
    pair<button, button> hunger_buttons;
    number_input thirst_input;
    pair<button, button> thirst_buttons;
    public:
    player(int health[6], int abilities[6], int max_hunger, int max_thirst);
    void update();
    void change_health(string health_location, int health_change_amount);
    void change_abilities(string ability_to_change, int ability_change_amount);
    void change_hunger(int hunger_change);
    void change_thirst(int thirst_change);
    void draw();
};