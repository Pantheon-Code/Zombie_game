#pragma once
#include "raylib.h"


class text_input{
    private:
    static const int max_char_num = 15;
    char edit_input[max_char_num] = "\0";
    Rectangle text_box;
    bool mouse_on_text = false;
    int letter_count = 0;
    int key;
    int frame_counter = 0;
    public:
    text_input(Rectangle text_box);
    char * get_edit_input();
    void delete_text();
    void update();
    void draw();
};