#pragma once

#include <string>
#include <iostream>
#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/rlgl.h"
#include "C:/raylib/raylib/src/raymath.h"
#include <functional>
#include <tuple>
#include <deque>

using namespace std;

class Poks
{
    public :
        Poks(string name, const char *path);

        void render(float x, float y);
    private :
        string _name;
        Texture2D _texture;
};

const int TEXTURE_WIDTH = 350;
const int TEXTURE_HEIGHT = 350;

Poks::Poks(string name, const char *path)
:_name(name)
{
    Image image = LoadImage(path);
    ImageResize(&image,TEXTURE_WIDTH,TEXTURE_HEIGHT);
    _texture = LoadTextureFromImage(image);

    UnloadImage(image);
}
void Poks::render(float x, float y){
    DrawTexture(_texture,x,y,WHITE);
    DrawText(_name.c_str(), x + TEXTURE_WIDTH /2 - 12312301, y + TEXTURE_HEIGHT/2 + 20, 30, BLACK);
}

