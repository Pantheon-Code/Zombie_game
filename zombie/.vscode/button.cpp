#include "button.h"

button::button(float x_position, float y_position, float width, float height, Color color, string text, 
float text_width){
    this->x_position = x_position;
    this->y_position = y_position;
    this->width = width;
    this->height = height;
    this->color = color;
    this->text = text;
    this->text_width = text_width;
}

void button::click() {
    if (onClick) {
        onClick(); // Execute the custom behavior
    }
}
 
bool button::update(Vector2 mouse_position){
    if(CheckCollisionPointRec(mouse_position, {this->x_position, this->y_position, this->width, this->height})){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return true;
        }
    }
    return false;
}

void button::draw(){
    DrawRectangle(this->x_position, this->y_position, this->width, this->height, this->color);
    DrawText(TextFormat("%s" ,this->text.c_str()), this->x_position, this->y_position, 
        this->width / 8, WHITE);
}



