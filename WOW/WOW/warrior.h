#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "wow.h"

class Dragon
: public Warrior
{
public:
    Dragon(int hp, int num, int atk, WarriorType type, vector<City*> cityVec)
    : Warrior(hp, num, atk, type, cityVec)
    {}

    void marched()
    {
        GameTime::getInstance()->showTime();
        ++_step;
        cout<<toString(_color)<<" dragon "
            <<_num<<" marched to city "<<_city->getNum()<<" "
            <<"with "<<_hp<<" elements and force "<<_atk<<endl;
    }

    void fight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" dragon "
                <<_num<<" attacked "<<toString(warrior->getColor())<<" "
                <<toString(warrior->getType())<<" "<<warrior->getNum()
                <<" in city "<<_city->getNum()<<" with "<<_hp
                <<" elements and force "<<_atk<<endl;
        }
    }

    void backFight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk/2;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" dragon "
                <<_num<<" fought back against "<<toString(warrior->getColor())
                <<" "<<toString(warrior->getType())<<" "
                <<warrior->getNum()<<" in city "<<_city->getNum()
                <<endl;
        }
    }

    void die()
    {
        if(_hp <= 0){
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" dragon "
                <<_num<<" was killed in city "<<_city->getNum()<<endl;
        }
    }

    void yell()
    {
        if(_hp > 0){
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" dragon "<<_num
                <<" yelled in city "<<_city->getNum()<<endl;
        }
    }
};

class Ninja
: public Warrior
{
public:
    Ninja(int hp, int num, int atk, WarriorType type, vector<City*> cityVec)
    : Warrior(hp, num, atk, type, cityVec)
    {}

    void marched()
    {
        GameTime::getInstance()->showTime();
        ++_step;
        cout<<toString(_color)<<" ninja "
            <<_num<<" marched to city "<<_city->getNum()<<" "
            <<"with "<<_hp<<" elements and force "<<_atk<<endl;
    }

    void fight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" ninja "
                <<_num<<" attacked "<<toString(warrior->getColor())<<" "
                <<toString(warrior->getType())<<" "<<warrior->getNum()
                <<" in city "<<_city->getNum()<<" with "<<_hp
                <<" elements and force "<<_atk<<endl;
        }
    }

    void die()
    {
        if(_hp <= 0){
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" ninja "
                <<_num<<" was killed in city "<<_city->getNum()<<endl;
        }
    }

    void backFight() {}
    void yell() {}
};

class Iceman
: public Warrior
{
public:
    Iceman(int hp, int num, int atk, WarriorType type, vector<City*> cityVec)
    : Warrior(hp, num, atk, type, cityVec)
    {}

    void marched()
    {
        GameTime::getInstance()->showTime();
        ++_step;
        if(_step%2 == 0){
            if(_hp > 9){
                _hp -= 9;
                _atk += 20;
            }else{
                _hp = 1;
                _atk += 20;
            }
        }
        cout<<toString(_color)<<" iceman "
            <<_num<<" marched to city "<<_city->getNum()<<" "
            <<"with "<<_hp<<" elements and force "<<_atk<<endl;
    }

    void fight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" iceman "
                <<_num<<" attacked "<<toString(warrior->getColor())<<" "
                <<toString(warrior->getType())<<" "<<warrior->getNum()
                <<" in city "<<_city->getNum()<<" with "<<_hp
                <<" elements and force "<<_atk<<endl;
        }
    }

    void backFight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk/2;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" iceman "
                <<_num<<" fought back against "<<toString(warrior->getColor())
                <<" "<<toString(warrior->getType())<<" "
                <<warrior->getNum()<<" in city "<<_city->getNum()
                <<endl;
        }
    }

    void die()
    {
        if(_hp <= 0){
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" iceman "
                <<_num<<" was killed in city "<<_city->getNum()<<endl;
        }
    }

    void yell() {}
};

class Lion
: public Warrior
{
public:
    Lion(int hp, int num, int atk, WarriorType type, vector<City*> cityVec)
    : Warrior(hp, num, atk, type, cityVec)
    , _hp1(hp)
    {}

    void marched()
    {
        GameTime::getInstance()->showTime();
        ++_step;
        cout<<toString(_color)<<" lion "
            <<_num<<" marched to city "<<_city->getNum()<<" "
            <<"with "<<_hp<<" elements and force "<<_atk<<endl;
    }

    void fight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" lion "
                <<_num<<" attacked "<<toString(warrior->getColor())<<" "
                <<toString(warrior->getType())<<" "<<warrior->getNum()
                <<" in city "<<_city->getNum()<<" with "<<_hp
                <<" elements and force "<<_atk<<endl;
        }
    }

    void backFight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk/2;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" lion "
                <<_num<<" fought back against "<<toString(warrior->getColor())
                <<" "<<toString(warrior->getType())<<" "
                <<warrior->getNum()<<" in city "<<_city->getNum()
                <<endl;
        }
    }

    void die()
    {
        if(_hp > 0){
            _hp1 = _hp;
        }else{
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" lion "
                <<_num<<" was killed in city "<<_city->getNum()<<endl;

            Warrior *warrior;
            if(_color == RED) warrior = _city->_BlueWarrior;
            else warrior = _city->_RedWarrior;
            if(warrior->getType()==WOLF && warrior->getKill()%2==0){
                warrior->_hp *= 2;
                warrior->_atk *= 2;
            }
            warrior->_hp += _hp1;
        }
    }

    void yell() {}

private:
    int _hp1;
};

class Wolf
: public Warrior
{
public:
    Wolf(int hp, int num, int atk, WarriorType type, vector<City*> cityVec)
    : Warrior(hp, num, atk, type, cityVec)
    {}

    void marched()
    {
        GameTime::getInstance()->showTime();
        
        ++_step;
        cout<<toString(_color)<<" wolf "
            <<_num<<" marched to city "<<_city->getNum()<<" "
            <<"with "<<_hp<<" elements and force "<<_atk<<endl;
    }

    void fight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" wolf "
                <<_num<<" attacked "<<toString(warrior->getColor())<<" "
                <<toString(warrior->getType())<<" "<<warrior->getNum()
                <<" in city "<<_city->getNum()<<" with "<<_hp
                <<" elements and force "<<_atk<<endl;
            if(warrior->_hp <= 0){
               ++_kill;
               if(_kill%2 == 0 && warrior->getType() != LION){
                    _hp *= 2;
                    _atk *= 2;
               }
            }
        }
    }

    void backFight()
    {
        Warrior *warrior;
        if(_color == RED) warrior = _city->_BlueWarrior;
        else warrior = _city->_RedWarrior;
        if(warrior != nullptr){
            warrior->_hp -= _atk/2;
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" wolf "
                <<_num<<" fought back against "<<toString(warrior->getColor())
                <<" "<<toString(warrior->getType())<<" "
                <<warrior->getNum()<<" in city "<<_city->getNum()
                <<endl;
        }
    }

    void die()
    {
        if(_hp <= 0){
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" wolf "
                <<_num<<" was killed in city "<<_city->getNum()<<endl;
        }
    }

    void yell() {}
};
#endif
