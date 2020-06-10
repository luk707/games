#pragma once

class GameOfLife
{
private:
    bool* state;
    bool* next_state;
    int width;
    int height;
public:
    GameOfLife(int width, int height);
    ~GameOfLife();
    void Update();
    void Render();
};
