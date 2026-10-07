#include "health_editor.h"
#include "button.h"
#include "number_input.h"

health_editor::health_editor(int x, int y, string name) : 
stats_editor(x, y, name){
    this->add_max_health = new button(x + 105, y, 30, 15, GREEN, "ADD MAX HEALTH", 20);
    this->read_file();
}


void health_editor::update(){
    stats_editor::update();
    if(this->add_max_health->update(GetMousePosition())){
        this->add_max();
    }
}

void health_editor::read_file(){
    ifstream myFile("csv_files/" + this->name + ".csv");

    if(myFile.is_open()){
        string line;
        getline(myFile, line);
        stringstream ss(line);
        string health_line;
        getline(ss, health_line, ',');
        this->max_health = stoi(health_line);
        string stat_line;
        getline(ss, stat_line, ',');
        this->stat = stoi(stat_line);

    }
    
    myFile.close();
}

void health_editor::change_file(){
    ofstream myFile("csv_files/" + this->name + ".csv");
    if(myFile.is_open()){
        myFile << this->max_health << ',' << this->stat << endl;
    }
    myFile.close();

    
}

void health_editor::add_max(){
    int max_to_add = atoi(this->stats_input->get_edit_input());
    this->max_health += max_to_add;
    this->change_file();
}

void health_editor::add(){
    stats_editor::add();
    if(this->stat > this->max_health){
        this->stat -= this->stat - this->max_health;
    }
    this->change_file();
}

void health_editor::add(int stat){
    this->stat += stat;
    if(this->stat > this->max_health){
        this->stat -= this->stat - this->max_health;
    }
    this->change_file();
}

int health_editor::get_max(){
    return this->max_health;
}

void health_editor::draw(){
    DrawText(TextFormat("%s: %i/%i", this->name.c_str(), this->max_health, this->stat), this->x, this->y - 20, 15, WHITE);
    this->stats_input->draw();
    this->add_button->draw();
    this->add_max_health->draw();
}