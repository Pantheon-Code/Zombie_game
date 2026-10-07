#include "stats_editor.h"
#include "button.h"
#include "number_input.h"

stats_editor::stats_editor(int x, int y, string name){
    this->x = x;
    this->y = y;
    this->name = name;
    this->stats_input = new number_input(Rectangle{(float)this->x, (float)this->y, 50.0f, 20.0f});
    this->add_button = new button(x + 60, y, 30, 15, GREEN, "ADD", 20);
    this->read_file();
}

void stats_editor::update(){
    this->stats_input->update();
    if(this->add_button->update(GetMousePosition())){
        this->add();
    }
}

void stats_editor::read_file(){
    ifstream myFile("csv_files/" + this->name + ".csv");
    if(myFile.is_open()){
        string line;
        getline(myFile, line);
        stringstream ss(line);
        string stat_line;
        getline(ss, stat_line, ',');
        this->stat = stoi(stat_line);
    }
    
    myFile.close();
}

void stats_editor::change_file(){
    ofstream myFile("csv_files/" + this->name + ".csv");
    if(myFile.is_open()){
        myFile << this->stat << endl;
    }
    
    myFile.close();

}

void stats_editor::add(){
    int num_to_add = atoi(this->stats_input->get_edit_input());
    this->stat += num_to_add;
    this->change_file();
}

void stats_editor::add(int stat){
    this->stat += stat;
    this->change_file();
}

void stats_editor::draw(){
    DrawText(TextFormat("%s: %i", this->name.c_str(), this->stat), this->x, this->y - 20, 15, WHITE);
    this->stats_input->draw();
    this->add_button->draw();
    
}

stats_editor::~stats_editor(){
    delete this->stats_input;
    this->stats_input = nullptr;
    delete this->add_button;
    this->add_button = 0;
}