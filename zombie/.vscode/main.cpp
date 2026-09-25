#include "raylib.h"
#include <iostream>
#include "player.h"
//#include "change_player_menu.h"
#include "inventory.h"
#include "attacks.h"
//g++ *.cpp -lraylib -framework IOKit -framework Cocoa -framework OpenGL
using namespace std;

int main(){
    int screen_width = 1350;
    int screen_height = 750;
    int target_fps = 60;

    InitWindow(screen_width, screen_height, "Zombie Game");

    SetTargetFPS(60);
    Vector2 mouse_position;
    int bro[] = {1,1,1,1,1,1};
    int yo[] = {1,1,1,1,1,1};
    player player1(bro, yo, 10, 10);
    attacks attacks1;
    inventory inventory1(50, 5, &attacks1);
    attacks1.set_inventory(&inventory1);
    // change_player_menu change_player_menu1;
    while(WindowShouldClose() == false){
        mouse_position = GetMousePosition();
        BeginDrawing();
        ClearBackground(BLACK);
        // change_player_menu1.update();
        inventory1.update();
        player1.update();
        attacks1.update();
        player1.draw();
        inventory1.draw();
        attacks1.draw();
        // change_player_menu1.draw();
        EndDrawing();
    }

    CloseWindow();
}