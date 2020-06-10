#include <random>
#include "raylib-3.0.0-Win64-msvc15/include/raylib.h"
#include "game_of_life.hh"

GameOfLife::GameOfLife(int width, int height)
{
    state = new bool[width * height];
    next_state = new bool[width * height];

    this->width = width;
    this->height = height;

    std::default_random_engine generator;
    std::uniform_int_distribution<> distribution(0, 1);

    for (int i = 0; i < width * height; i++)
    {
        state[i] = distribution(generator);
    }
}

GameOfLife::~GameOfLife()
{
    delete[] state;
    delete[] next_state;
}

void GameOfLife::Update()
{
    for (int i = 0; i < width * height; i++)
    {
        int nc = 0;

        for(int j = 0; j < 9; j++)
        {
            if (j == 4)
            {
                continue;
            }
            int cx = i % width;
            int cy = i / width;
            int dx = (j % 3) - 1;
            int dy = (j / 3) - 1;
            int nx = (cx + dx) % width;
            int ny = (cy + dy) % height;
            int ni = nx + (width * ny);
            if (state[ni])
            {
                nc++;
            }
        }

        if (state[i])
        {
            next_state[i] = nc == 2 || nc == 3;
        }
        else if (nc == 3)
        {
            next_state[i] = true;
        }
        else
        {
            next_state[i] = false;
        }
    }

    bool* temp = state;
    state = next_state;
    next_state = temp;
}

void GameOfLife::Render()
{
    for (int i = 0; i < width * height; i++)
    {
        if (state[i])
        {
            DrawRectangleRec(Rectangle{
                float(i % width) * 10.0f,
                float(i / width) * 10.0f,
                10,
                10
            }, WHITE);
        }
    }
}
