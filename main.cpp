#include <iostream>
#include "Poks.hpp"
#include "moves.hpp"
#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/rlgl.h"
#include "C:/raylib/raylib/src/raymath.h"
#include <queue>

using namespace std;
void draw_gui(int selected_index,deque<string> &output);

void update_output_queue(deque<string> &output, string line);
int main()
{

    const int screenWidth = 1400;
    const int screenHeight = 1000;
    deque<string> console_output(5);

    InitWindow(screenWidth, screenHeight, "GigantMony");

    Poks player("Fire",20,10,5,Elements::Ogien, "resources/fire.png");
    Poks enemy("Water",20,10,5,Elements::Woda, "resources/water.png");

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
        else if(IsKeyPressed(KEY_ENTER)){
            string text{};
            switch(selected_idx){
                case 0:{
                    bool target_dead = player.attack(enemy,text);
                    update_output_queue(console_output,text);
                    if(target_dead){
                        update_output_queue(console_output,enemy.get_name() + " has died ");
                    }
                    break;
                }
                case 1:{
                    player.defend(text);
                    update_output_queue(console_output,text);
                    break;
                }
                case 2:{
                    player.special(enemy,text);
                    update_output_queue(console_output,text);
                    break;
                }
                default: break;
            }
            bool target_dead = enemy.attack(player,text);
            if(target_dead){
                update_output_queue(console_output,player.get_name() + " has died ");
            }
            update_output_queue(console_output,text);
        }
        BeginDrawing();
        ClearBackground(SKYBLUE);
        draw_gui(selected_idx,console_output);

        player.render(screenWidth / 2 - 520, screenHeight / 2 - 220);

        enemy.render(screenWidth / 2 + 150, screenHeight / 2 - 350);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void draw_gui(int selected,deque<string> &output)
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

    int offset = 0;
    for(string line : output){
        DrawText(line.c_str(),920, 920- 25*offset,20 ,BLACK);
        offset++;
    }
}
void update_output_queue(deque<string> &output, string line){
    output.push_back(line);
    if(output.size() > 5){
        output.pop_front();
    }
}