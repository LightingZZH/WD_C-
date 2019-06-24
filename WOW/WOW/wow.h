#ifndef __WOW_H__
#define __WOW_H__

#include "GameTime.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum Color{
    RED,
    BLUE,
    NONE
};

enum WarriorType{
    DRAGON,
    NINJA,
    ICEMAN,
    LION,
    WOLF
};

inline string toString(Color color)
{
    return (color == RED) ? string("red") : string("blue");
}

inline string toString(WarriorType type)
{
    switch(type)
    {
        case DRAGON:    return "dragon";
        case NINJA:     return "ninja";
        case ICEMAN:    return "iceman";
        case LION:      return "lion";
        case WOLF:      return "wolf";
        default:        return string();
    }
}

class Headquarter;
class City;
class Warrior
{
public:
    Warrior(int hp, int num, int atk, WarriorType type, vector<City*> cityVec)
    : _hp(hp)
    , _atk(atk)
    , _color(NONE)
    , _num(num)
    , _element(0)
    , _type(type)
    , _city(nullptr)
    , _step(0)
    , _kill(0)
    , _win(0)
    , _arrive(0)
    , _cityVec(cityVec)
    {}

    int getNum()
    {   return _num;    }

    int getATK()
    {   return _atk;    }

    Color getColor()
    {   return _color;  }

    WarriorType getType()
    {   return _type;   }

    int getStep()
    {   return _step;   }

    int getKill()
    {   return _kill;   }

    int printElement()
    {
        return _element;
    }

    void putElement();

    int getArrive()
    {   return _arrive; }

    void setWin() { _win = 1; }
    void resetWin() { _win = 0; }
    int getWin() { return _win; }

    void getElement();
    void forward();    

    virtual void marched() = 0;
    virtual void fight() = 0;
    virtual void backFight() = 0;
    virtual void die() = 0;
    virtual void yell() = 0;

    int _hp;
    int _atk;
    Color _color;
    Headquarter* _enemyHead;
    Headquarter* _myHead;
    size_t _cityNum;
protected:
    int _num;
    int _element;
    WarriorType _type;
    City *_city;
    int _step;
    int _kill;
    int _win;
    int _arrive;
    vector<City*> _cityVec;
};

class City
{
friend void Warrior::getElement();
public:
    City(int num)
    : _RedWarrior(nullptr)
    , _BlueWarrior(nullptr)
    , _num(num)
    , _element(0)
    , _flag(NONE)
    , _redCnt(0)
    , _blueCnt(0)
    {}

    int getNum()
    {   return _num;    }

    int getElement()
    {   return _element;    }

    Color getFlag()
    {   return _flag;   }

    void produce()
    {
        _element += 10;
    }

    void setRedCnt()
    {
        ++_redCnt;
        _blueCnt = 0;
        if(_redCnt == 2) _flag = RED;
    }

    void setBlueCnt()
    {
        ++_blueCnt;
        _redCnt = 0;
        if(_blueCnt == 2) _flag = BLUE;
    }

    void raiseFlag()
    {
        if(_redCnt==2 ||_blueCnt==2){
            GameTime::getInstance()->showTime();
            cout<< toString(_flag) << " flag raised in city "<< _num << endl;
        }
    }

    void initWarrior()
    {
        _RedWarrior = nullptr;
        _BlueWarrior = nullptr;
    }

    void initElement()
    {   _element = 0;   }
    
    void putElement1()
    {
        if(_RedWarrior && !_BlueWarrior){
             _RedWarrior->getElement();
             _RedWarrior->putElement();
        }
        if(!_RedWarrior && _BlueWarrior){
            _BlueWarrior->getElement();
            _BlueWarrior->putElement();
        } 
    }

    void putElement2()
    {
        if(_RedWarrior && _RedWarrior->getWin()){
            _RedWarrior->putElement();
            _RedWarrior->resetWin();
        }
        if(_BlueWarrior && _BlueWarrior->getWin()){
            _BlueWarrior->putElement();
            _BlueWarrior->resetWin();
        }
    }

    void mached()
    {
        if(_RedWarrior) _RedWarrior->marched();
        if(_BlueWarrior) _BlueWarrior->marched();
    }

    void fight()
    {
        if(!_RedWarrior || !_BlueWarrior) return;
        Warrior *fighter, *backfighter;
        if(_flag == NONE){
            if(_num%2){
                fighter = _RedWarrior;
                backfighter = _BlueWarrior;
            }else{
                fighter = _BlueWarrior;
                backfighter = _RedWarrior;
            }
        }else if(_flag == RED){
           fighter = _RedWarrior;
           backfighter = _BlueWarrior;
        }else{
            fighter = _BlueWarrior;
            backfighter = _RedWarrior;
        }
        fighter->fight();
        if(backfighter->_hp>0) backfighter->backFight();
        fighter->die();
        backfighter->die();
        fighter->yell();
        if(fighter->_hp>0 && backfighter->_hp<=0){
            fighter->getElement();
            fighter->setWin();
            if(fighter->getColor()==RED) setRedCnt();
            else setBlueCnt();
        }
        if(fighter->_hp<=0 && backfighter->_hp>0){
            backfighter->getElement();
            backfighter->setWin();
            if(backfighter->getColor()==RED) setRedCnt();
            else setBlueCnt();
        } 
    }

    Warrior *_RedWarrior;
    Warrior *_BlueWarrior;
private:
    int _num;
    int _element;
    Color _flag;
    int _redCnt;
    int _blueCnt;
};

class Headquarter
{
public:
    Headquarter(int hp, vector<int> warriorHp, vector<int> warriorATK, vector<City*> cityVec)
    : _hp(hp)
    , _cnt(0)
    , _warriorHp(warriorHp)
    , _warriorATK(warriorATK)
    , _cityVec(cityVec)
    {}
    virtual void createWarrior() = 0;
    
    void createDragon();
    void createNinja();
    void createIceman();
    void createLion();
    void createWolf();

    void reward();

    void arrive()
    {
        if(!_warriorVec.size()) return;
        auto it = _warriorVec.begin();
        if((*it)->getArrive()){
            string color;
            if((*it)->getColor()==RED) color="blue";
            else color = "red";
            GameTime::getInstance()->showTime();
            cout<<toString((*it)->getColor())<<" "
                <<toString((*it)->getType())<<" "
                <<(*it)->getNum()<<" reached "
                <<color<<" headquarter with "
                <<(*it)->_hp<<" elements and force "
                <<(*it)->getATK()<<endl;
            _warriorVec.erase(it);
            return ;
        }
    }

    int istaken()
    {
        if(_enemy.size()==2){
            GameTime::getInstance()->showTime();
            cout<<toString(_color)<<" headquarter was taken"<<endl;
            return 1;
        }
        return 0;
    }

    void clearWarrior()
    {
        if(!_warriorVec.size()) return;
        auto it1=_warriorVec.begin();
        if((*it1)->getArrive()) _warriorVec.erase(it1);
        for(auto it=_warriorVec.begin();it!=_warriorVec.end();){
            if((*it)->_hp<=0){
                _warriorVec.erase(it);
            }else ++it;
        }
    }

    void initWin()
    {
        for(auto it=_warriorVec.begin();it!=_warriorVec.end();++it){
            (*it)->resetWin();
        }
    }

    void reportHp()
    {
        GameTime::getInstance()->showTime();
        cout<<_hp<<" elements in "<<toString(_color)<<" headquarter"<<endl;
    }

    Color getColor() { return _color; }
    void setRed()  {    _color = RED;   }
    void setBlue() {    _color = BLUE;  }
    void setEnemy(Headquarter* enemyHead)
    {
        if(_warriorVec.size()){
            auto it = _warriorVec.end()-1;
            (*it)->_enemyHead = enemyHead;
        }
    }

    int _hp;
    vector<Warrior*> _enemy;
    vector<Warrior*> _warriorVec;
    friend void Warrior::forward();
protected:
    int _cnt;
    Color _color;
    vector<int> _warriorHp;
    vector<int> _warriorATK;
    vector<City*> _cityVec;
    vector<WarriorType> redOrder = {ICEMAN, LION, WOLF, NINJA, DRAGON};
    vector<WarriorType> blueOrder = {LION, DRAGON, NINJA, ICEMAN, WOLF};
};

class RedHeadquarter
: public Headquarter
{
public:
    RedHeadquarter(int hp, vector<int> warriorHp, vector<int> warriorATK, vector<City*> cityVec)
    : Headquarter(hp, warriorHp, warriorATK, cityVec)
    {   setRed();   }

    void createWarrior()
    {
        WarriorType type;
        auto it = redOrder.begin()+_cnt%5;
        type = *it;
        switch(type){
            case DRAGON: createDragon(); break; 
            case NINJA : createNinja();  break;
            case ICEMAN: createIceman(); break;
            case LION  : createLion();   break;
            case WOLF  : createWolf();   break;
        }
        if(_warriorVec.size()){
            auto it1 = _warriorVec.end()-1;
            if((*it1)->_color == NONE){
                (*it1)->_cityNum = 0;
                (*it1)->_color = RED;
            } 
        }
    }
};

class BlueHeadquarter
: public Headquarter
{
public:
    BlueHeadquarter(int hp, vector<int> warriorHp, vector<int> warriorATK, vector<City*> cityVec)
    : Headquarter(hp, warriorHp, warriorATK, cityVec)
    {   setBlue();   }

    void createWarrior()
    {
        WarriorType type;
        auto it = blueOrder.begin()+_cnt%5;
        type = *it;
        switch(type){
            case DRAGON: createDragon(); break; 
            case NINJA : createNinja();  break;
            case ICEMAN: createIceman(); break;
            case LION  : createLion();   break;
            case WOLF  : createWolf();   break;
        }
        if(_warriorVec.size()){
            auto it1 = _warriorVec.end()-1;
            if((*it1)->_color == NONE){
                (*it1)->_cityNum = _cityVec.size()+1;
                (*it1)->_color = BLUE;
            }
        }
    }
};
#endif
