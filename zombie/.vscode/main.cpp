#include "raylib.h"
#include <iostream>
#include "player.h"
//#include "change_player_menu.h"
#include "inventory.h"
#include "attacks.h"
#include "necessities.h"
//g++ *.cpp -lraylib -framework IOKit -framework Cocoa -framework OpenGL
using namespace std;

int main(){
    int screen_width = 1400;
    int screen_height = 775;
    int target_fps = 60;

    InitWindow(screen_width, screen_height, "Zombie Game");

    SetTargetFPS(60);
    Vector2 mouse_position;
    player player1;
    inventory inventory1;
    attacks attacks1(&inventory1);
    necessities necessities1(&inventory1);
    // change_player_menu change_player_menu1;
    while(WindowShouldClose() == false){
        mouse_position = GetMousePosition();
        BeginDrawing();
        ClearBackground(BLACK);
        // change_player_menu1.update();
        inventory1.update();
        player1.update();
        attacks1.update();
        necessities1.update();
        player1.draw();
        inventory1.draw();
        attacks1.draw();
        necessities1.draw();
        // change_player_menu1.draw();
        EndDrawing();
    }
    inventory1.change_file();
    attacks1.close_attacks();

    CloseWindow();
}