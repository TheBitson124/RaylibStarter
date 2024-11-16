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

enum Elements{
    Ogien,
    Woda,
    Powietrze,
    Ziemia,
    Piorun,
    last
};

class Poks
{
    public :
        Poks(string name,int hp, int ad, int def,Elements el, const char *path);

        void render(float x, float y);

        inline string get_name(){
            return _name;
        }
        inline int get_hp(){
            return _hp;
        }
        inline void take_damage(int damage){
            if(damage < _def){
                return;
            }
            _hp -= (damage - _def);
        }
        inline void reset(){
            this->_def = this->_base_def;
            this->_hp = this->_base_hp;
            this->_ad = this->_base_ad;
        }

        void attack(Poks& target, string& out_string);
        void defend(string& out_string);
        void special(Poks& target, string& out_string);
    private :
        int _base_hp;
        int _base_ad;
        int _base_def;

        int _hp;
        int _ad;
        int _def;

        bool _is_special;
        bool _used_special;

        string _name;
        Elements _element;

        Texture2D _texture;
};

const int TEXTURE_WIDTH = 350;
const int TEXTURE_HEIGHT = 350;

Poks::Poks(string name, int hp, int ad, int def,Elements el,const char *path)
:_name(name)
{
    _base_hp = hp;
    _base_ad = ad;
    _base_def = def;
    _element = el;

    _hp = hp;
    _ad = ad;
    _def = def;

    Image image = LoadImage(path);
    ImageResize(&image,TEXTURE_WIDTH,TEXTURE_HEIGHT);
    _texture = LoadTextureFromImage(image);

    UnloadImage(image);
}
void Poks::render(float x, float y){
    DrawTexture(_texture,x,y,WHITE);
    DrawText(_name.c_str(), x + TEXTURE_WIDTH /2 - 30, y + TEXTURE_HEIGHT + 20, 30, BLACK);
}
void Poks::attack(Poks& target, string& out_string){
    target.take_damage(_ad);
    out_string = this->get_name() + " attacked " + target.get_name()  + " for : " + to_string(_ad);
}
void Poks::defend(string& out_string){
    _def += _base_def/2;
    out_string = this->get_name() + " defends for " + to_string(_base_def/2);
}

void Poks::special(Poks& target, string& out_string){
    if(!_used_special){
        target.take_damage(_ad * 2);
        out_string = this->get_name() + " used special on " + target.get_name()  + " for : " + to_string(_ad * 2);
        _used_special = true;
    }
    else{
         out_string = this->get_name() + " used special already";
    }
}

