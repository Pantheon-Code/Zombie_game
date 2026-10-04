#include "player.h"
#include "health_editor.h"

player::player(){
    for(int i = 0; i < abilities_vec.size(); i++){
        stats_editor * new_stat = new stats_editor(i * 150 + this->x, 40, this->abilities_vec[i]);
        this->stats.push_back(new_stat);
    }
    for(int j = 0; j < health_vec.size(); j++){
        health_editor * new_health = new health_editor(j * 220 + this->x, 110, this->health_vec[j]);
        this->health.push_back(new_health);
    }

}

void player::update(){
    for(int i = 0; i < this->stats.size(); i++){
        this->stats[i]->update();
    }
    for(int j = 0; j < this->health.size(); j++){
        this->health[j]->update();
    }

}

void player::draw(){
    for(int i = 0; i < this->stats.size(); i++){
        this->stats[i]->draw();
    }
    for(int j = 0; j < this->health.size(); j++){
        this->health[j]->draw();
    }
}