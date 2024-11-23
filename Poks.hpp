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
        Poks(string name,int hp, int ad, int def,Elements el, const char *path,function<void(Poks &, Poks &, string &)> special);

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
        inline bool check_if_dead(){
            return _hp <= 0;
        }
        bool attack(Poks& target, string& out_string);
        void defend(string& out_string);
        void special(Poks& target, string& out_string);
        pair<int,int> calculate_attack_dmg(Poks &target);

        inline void change_ad(int change){
            _ad += change;
        }
        inline void change_def(int change){
            _def += change;
        }
        inline void change_hp(int change){
            _hp += change;
        }
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
        function<void(Poks &, Poks &, string &)> special_fun;

        Texture2D _texture;
        void draw_hp_bar(float x, float y);
};

const int TEXTURE_WIDTH = 350;
const int TEXTURE_HEIGHT = 350;

Poks::Poks(string name, int hp, int ad, int def,Elements el,const char *path,function<void(Poks &, Poks &, string &)> special )
:_name(name)
{
    _base_hp = hp;
    _base_ad = ad;
    _base_def = def;
    _element = el;

    _hp = hp;
    _ad = ad;
    _def = def;

    special_fun = special;
    Image image = LoadImage(path);
    ImageResize(&image,TEXTURE_WIDTH,TEXTURE_HEIGHT);
    _texture = LoadTextureFromImage(image);

    UnloadImage(image);
}
void Poks::render(float x, float y){
    DrawTexture(_texture,x,y,WHITE);
    DrawText(_name.c_str(), x + TEXTURE_WIDTH /2 - 30, y + TEXTURE_HEIGHT + 20, 30, BLACK);

    DrawText(TextFormat("ATTACK %i",this->_ad),x - 140, y + TEXTURE_HEIGHT/2 -20,20,BLACK);
    DrawText(TextFormat("DEFENCE %i",this->_def),x - 150, y + TEXTURE_HEIGHT/2 +20,20,BLACK);
    draw_hp_bar(x,y);
}
bool Poks::attack(Poks& target, string& out_string){
    int base{};
    int bonus{};
    tie(base,bonus) = calculate_attack_dmg(target);

    int total = base + bonus;
    target.take_damage(total);
    out_string = this->get_name() + " attacked " + target.get_name()  + " for : " + to_string(total)
    +" with bonus of " + to_string(bonus);
    return target.check_if_dead();
}
void Poks::defend(string& out_string){
    _def += _base_def/2;
    out_string = this->get_name() + " defends for " + to_string(_base_def/2);
}

void Poks::special(Poks& target, string& out_string){
    if(!_used_special){
        this->special_fun(*this,target,out_string);
        _used_special = true;
    }
    else{
         out_string = this->get_name() + " used special already";
    }
}
void Poks::draw_hp_bar(float x,float y){
    float const x_anchor = x + 10;
    float const y_anchor = y - 50;

    float const height = 40;
    float const border_width = 2;
    Rectangle border{x_anchor,y_anchor ,TEXTURE_WIDTH - 10,height};
    DrawRectangleLinesEx(border,border_width,BLACK);

    const float fill = (float)_hp/(float)_base_hp;

    DrawRectangle(x_anchor + border_width,y_anchor + border_width, fill * (TEXTURE_WIDTH - 10 -2 *border_width),height - 2*border_width, GREEN);
}
pair<int,int> Poks::calculate_attack_dmg(Poks &target){
    int bonus{};
    auto dif = target._element - this->_element;
    switch (abs(dif))
    {
    case 1:
        bonus = dif > 0 ? this->_ad *0.5f : this->_ad *-0.5f;
        break;
    case Elements::last - 1:
        bonus = dif > 0 ? this->_ad *-0.5f :this->_ad *0.5f;
        break;
    default:
        bonus = 0;
        break;
    }
    return make_pair(this->_ad,bonus);
}