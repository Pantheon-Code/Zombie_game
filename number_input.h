#pragma once
#include "raylib.h"


class number_input{
    private:
    static const int max_char_num = 4;
    char edit_input[max_char_num] = "\0";
    Rectangle text_box;
    bool mouse_on_text = false;
    int letter_count = 0;
    int key;
    int frame_counter = 0;
    public:
    number_input(Rectangle text_box);
    char * get_edit_input();
    void delete_text();
    void update();
    void draw();
};