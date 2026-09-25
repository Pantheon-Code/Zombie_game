#include "number_input.h"

number_input::number_input(Rectangle text_box){
    this->text_box = text_box;
}

char * number_input::get_edit_input(){
    return this->edit_input;
}

void number_input::delete_text(){
    this->letter_count = 0;
    this->edit_input[letter_count] = '\0';
}

void number_input::update(){
    if (CheckCollisionPointRec(GetMousePosition(), this->text_box)) this->mouse_on_text = true;
    else this->mouse_on_text = false;
    if(this->mouse_on_text){
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        this->key = GetCharPressed();
        while(this->key){
            if((this->key >= 48) && (this->key <= 57) && (this->letter_count < this->max_char_num)){
                this->edit_input[letter_count] = (char)key;
                this->edit_input[letter_count + 1] = '\0'; // Add null terminator at the end of the string
                this->letter_count++;
            }
            this->key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)){
            this->letter_count--;
            if(this->letter_count < 0) this->letter_count = 0;
            this->edit_input[this->letter_count] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if (this->mouse_on_text) this->frame_counter++;
    else this->frame_counter = 0;
}

void number_input::draw(){
    DrawRectangleRec(this->text_box, LIGHTGRAY);
    if (this->mouse_on_text) DrawRectangleLines((int)this->text_box.x, (int)this->text_box.y, (int)this->text_box.width, (int)this->text_box.height, RED);
    else DrawRectangleLines((int)this->text_box.x, (int)this->text_box.y, (int)this->text_box.width, (int)this->text_box.height, DARKGRAY);

    DrawText(this->edit_input, (int)this->text_box.x + 2, (int)this->text_box.y + 2, 20, MAROON);

    //DrawText(TextFormat("INPUT CHARS: %i/%i", this->letter_count, this->max_char_num), 315, 250, 20, DARKGRAY);

    if (this->mouse_on_text)
    {
        if (this->letter_count < this->max_char_num)
        {
            // Draw blinking underscore char
            if (((this->frame_counter/20)%2) == 0) DrawText("_", (int)this->text_box.x + 2 + MeasureText(this->edit_input, 20), (int)this->text_box.y + 2, 20, MAROON);
        }
       // else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }
}