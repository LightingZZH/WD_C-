#ifndef __WOW2_H__
#define __WOW2_H__

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class Warrior
{
public:
    Warrior(int number, int hp)
    : _number(number)
    , _hp(hp)
    {}

private:
    int _number;
    int _hp;
};

class Dragon
: public Warrior
{
public:
    Dragon(int number, int hp, string weapon, double morale)
    : Warrior(number, hp)
    , _weapon(weapon)
    , _morale(morale)
    {}
    
    void display()
    {
        cout<<"It has a "<<_weapon<<",and it's morale is ";
        printf("%.2f\n",_morale);
    }

private:
    string _weapon;
    double _morale; //士气值
};

class Ninja
: public Warrior
{
public:
    Ninja(int number, int hp, string weapon1, string weapon2)
    : Warrior(number, hp)
    , _weapon1(weapon1)
    , _weapon2(weapon2)
    {}

    void display()
    {
        cout<<"It has a "<<_weapon1<<" and a "<<_weapon2<<endl;
    }

private:
    string _weapon1;
    string _weapon2;
};

class Iceman
: public Warrior
{
public:
    Iceman(int number, int hp, string weapon)
    : Warrior(number, hp)
    , _weapon(weapon)
    {}

    void display()
    {
        cout<<"It has a "<<_weapon<<endl;
    }
    
private:
    string _weapon;
};

class Lion
: public Warrior
{
public:
    Lion(int number, int hp, int loyalty)
    : Warrior(number, hp)
    , _loyalty(loyalty)
    {}

    void display()
    {
        cout<<"It's loyalty is "<<_loyalty<<endl;
    }

private:
    int _loyalty;
};

class Wolf
: public Warrior
{
public:
    Wolf(int number, int hp)
    : Warrior(number, hp) 
    {}
};

class Headquarter
{
public:
    Headquarter(int hp,string color,int dragonHp,int ninjaHp,int icemanHp,int lionHP,int wolfHp)
    : _hp(hp)
    , _color(color)
    , _time(0)
    , _dragon(0)
    , _ninja(0)
    , _iceman(0)
    , _lion(0)
    , _wolf(0)
    , _flag(-2)
    , _dragonHp(dragonHp)
    , _ninjaHp(ninjaHp)
    , _icemanHp(icemanHp)
    , _lionHp(lionHP)
    , _wolfHp(wolfHp)
    {cout<<"Headquarter(int,string)"<<endl;}
    
    void CreateDragon();
    void CreateNinja();
    void CreateIceman();
    void CreateLion();
    void CreateWolf();

    void Create();
    int getFlag() {return _flag;}

private:
    int _hp;
    string _color;
    int _time;
    int _dragon;
    int _ninja;
    int _iceman;
    int _lion;
    int _wolf;
    int _flag;
    int _dragonHp;
    int _ninjaHp;
    int _icemanHp;
    int _lionHp;
    int _wolfHp;
};

#endif
