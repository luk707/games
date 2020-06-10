#include "raylib-3.0.0-Win64-msvc15/include/raylib.h"
#include "game_of_life.hh"

int main(int argc, char* argv[])
{
    int screenWidth = 1920;
    int screenHeight = 1080;

    GameOfLife gameOfLife(192, 108);

    InitWindow(screenWidth, screenHeight, "Game of Life");

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        gameOfLife.Update();
        gameOfLife.Render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
