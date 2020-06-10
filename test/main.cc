#include <iostream>
#include "raylib-3.0.0-Win64-msvc15/include/raylib.h"
#include "common/math/multiply.hh"

int main(int argc, char* argv[])
{
    char buffer [50];
    int a=5, b=3;
    sprintf(buffer, "%d times %d is %d", a, b, multiply(a, b));


    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib test");

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(buffer, 190, 200, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
