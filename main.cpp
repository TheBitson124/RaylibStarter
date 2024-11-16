#include <iostream>
#include "Poks.hpp"
#include "moves.hpp"
#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/rlgl.h"
#include "C:/raylib/raylib/src/raymath.h"
#include <queue>

using namespace std;
void draw_gui(int selected_index);

int main()
{

    const int screenWidth = 1400;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "GigantMony");

    Poks player("Fire", "resources/fire.png");
    Poks enemy("Water", "resources/water.png");

    int selected_idx{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_UP))
        {
            selected_idx--;
            selected_idx = selected_idx < 0 ? 2 : selected_idx;
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            selected_idx++;
            selected_idx = selected_idx > 2 ? 0 : selected_idx;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        draw_gui(selected_idx);

        player.render(screenWidth / 2 - 520, screenHeight / 2 - 220);

        enemy.render(screenWidth / 2 + 150, screenHeight / 2 - 350);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void draw_gui(int selected)
{
    Rectangle menu{-2, 810, 900, 310};
    DrawRectangleLinesEx(menu, 4, BLACK);

    DrawText("Attack", 15, 850, 30, BLACK);
    DrawText("Defend", 15, 900, 30, BLACK);
    DrawText("Special attack", 15, 950, 30, BLACK);

    Rectangle selection{10, 830 + selected * 50, 400, 60};
    DrawRectangleLinesEx(selection, 4, BLACK);

    Rectangle console{906, 810, 600, 310};
    DrawRectangleLinesEx(console, 4, BLACK);
}