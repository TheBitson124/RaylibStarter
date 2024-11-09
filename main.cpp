#include <iostream>
#include "Poks.hpp"
#include "moves.hpp"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <queue>

using namespace std;
int main()
{
    const int screenWidth = 1400;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "GigantMony");



    SetTargetFPS(60);
    while (!WindowShouldClose())
    {


        BeginDrawing();
        ClearBackground(SKYBLUE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

