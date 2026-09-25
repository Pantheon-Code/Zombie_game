#pragma once

#include <iostream>
#include "raylib.h"
#include <iostream>

using namespace std;

class button{
    public:
        float x_position;
        float y_position;
        float width;
        float height;
        Color color;
        string text = "";
        float text_width;
        function<void()> onClick;
        button(float x_position, float y_position, float width, float height, Color color, string text, 
            float text_width);
        void click();
        bool update(Vector2 mouse_position);
        void draw();
};