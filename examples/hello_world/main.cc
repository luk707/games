#include "raylib-3.0.0-Win64-msvc15/include/raylib.h"

int main(int argc, char* argv[])
{
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Hello, World!");

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello, World!", 190, 200, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
