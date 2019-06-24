#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GameTime
{
public:
    static GameTime * getInstance();
    static void destroy();

    size_t getTime() const;
    void showTime() const;
    void updateTime();
    void initTime();

private:
    static GameTime * _pInstance;
    size_t _hour;
    size_t _min;

};


GameTime * GameTime::getInstance()
{
    if(_pInstance == nullptr){
        _pInstance = new GameTime();
        atexit(destroy);
    }
    return _pInstance;

}


void GameTime::destroy()
{
    if(_pInstance)
        delete _pInstance;

}

size_t GameTime::getTime() const
{
    return _hour*60 + _min;

}


void GameTime::updateTime()
{
    _min += 10;
    if(_min == 60){
        ++_hour;
        _min -= 60;

    }

}

void GameTime::initTime()
{
    _min = 0;
    _hour = 0;

}

void GameTime::showTime() const
{
    printf("%03lu:%02lu ", _hour, _min);

}

GameTime * GameTime::_pInstance = getInstance();

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
    {   return _num;     }

    int getATK()
    {   return _atk;     }

    Color getColor()
    {   return _color;   }

    WarriorType getType()
    {   return _type;    }

    int getStep()
    {   return _step;    }

    int getKill()
    {   return _kill;    }

    int printElement()
    {
        return _element;

    }

    void putElement();

    int getArrive()
    {   return _arrive;  }

    void setWin() { _win = 1;  }
    void resetWin() { _win = 0;  }
    int getWin() { return _win;  }

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
    {   return _num;     }

    int getElement()
    {   return _element;     }

    Color getFlag()
    {   return _flag;    }

    void produce()
    {
        _element += 10;
    }

    void resetCnt()
    {
        _redCnt = 0;
        _blueCnt = 0;
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
    {   _element = 0;    }

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
        else if(fighter->_hp<=0 && backfighter->_hp>0){
            backfighter->getElement();
            backfighter->setWin();
            if(backfighter->getColor()==RED) setRedCnt();
            else setBlueCnt();
        }
        else resetCnt();
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

    Color getColor() { return _color;  }
    void setRed()  {    _color = RED;    }
    void setBlue() {    _color = BLUE;   }
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
    {   setRed();    }

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
    {   setBlue();    }

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

void Warrior::getElement()
{
    _element = _city->getElement();
    _city->initElement();
    GameTime::getInstance()->showTime();
    cout<<toString(_color)<<" "<<toString(_type)<<" "
        <<_num<<" earned "<<_element<<" elements for his headquarter"<<endl;

}

void Warrior::putElement()
{
    _myHead->_hp += _element;
    _element = 0;

}

void Warrior::forward()
{
    if(_color==RED){
        if(_cityNum==_cityVec.size()){
            _arrive=1;
            _enemyHead->_enemy.push_back(this);

        }else{
            _city = _cityVec[++_cityNum-1];
            _city->_RedWarrior = this;
        }
    }else{
        if(_cityNum==1){
            _arrive=1;
            _enemyHead->_enemy.push_back(this);

        }else{
            _city = _cityVec[--_cityNum-1];
            _city->_BlueWarrior = this;
        }
    }
    if(_type==ICEMAN){
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
    }
}

void Headquarter::reward()
{
    for(auto it=_warriorVec.begin(); it!=_warriorVec.end(); ++it){
        if((*it)->getWin()){
            if(_hp >= 8){
                _hp -= 8;
                (*it)->_hp += 8;

            }else break;

        }

    }

}

void Headquarter::createDragon()
{
    if(_hp >= _warriorHp[DRAGON]){
        ++_cnt;
        Warrior* dragon = new Dragon(_warriorHp[DRAGON],_cnt,_warriorATK[DRAGON],DRAGON,_cityVec);
        dragon->_myHead = this;
        _hp -= _warriorHp[DRAGON];
        _warriorVec.push_back(dragon);

        GameTime::getInstance()->showTime();
        cout<<toString(_color)<<" dragon "<<_cnt<<" born"<<endl;

    }

}

void Headquarter::createNinja()
{
    if(_hp >= _warriorHp[NINJA]){
        ++_cnt;
        Warrior* ninja = new Ninja(_warriorHp[NINJA],_cnt,_warriorATK[NINJA],NINJA,_cityVec);
        ninja->_myHead = this;
        _hp -= _warriorHp[NINJA];
        _warriorVec.push_back(ninja);

        GameTime::getInstance()->showTime();
        cout<<toString(_color)<<" ninja "<<_cnt<<" born"<<endl;

    }

}

void Headquarter::createIceman()
{
    if(_hp >= _warriorHp[ICEMAN]){
        ++_cnt;
        Warrior* iceman = new Iceman(_warriorHp[ICEMAN],_cnt,_warriorATK[ICEMAN],ICEMAN,_cityVec);
        iceman->_myHead = this;
        _hp -= _warriorHp[ICEMAN];
        _warriorVec.push_back(iceman);

        GameTime::getInstance()->showTime();
        cout<<toString(_color)<<" iceman "<<_cnt<<" born"<<endl;

    }

}

void Headquarter::createLion()
{
    if(_hp >= _warriorHp[LION]){
        ++_cnt;
        Warrior* lion = new Lion(_warriorHp[LION],_cnt,_warriorATK[LION],LION,_cityVec);
        lion->_myHead = this;
        _hp -= _warriorHp[LION];
        _warriorVec.push_back(lion);

        GameTime::getInstance()->showTime();
        cout<<toString(_color)<<" lion "<<_cnt<<" born"<<endl;

    }

}
void Headquarter::createWolf()
{
    if(_hp >= _warriorHp[WOLF]){
        ++_cnt;
        Warrior* wolf = new Wolf(_warriorHp[WOLF],_cnt,_warriorATK[WOLF],WOLF,_cityVec);
        wolf->_myHead = this;
        _hp -= _warriorHp[WOLF];
        _warriorVec.push_back(wolf);

        GameTime::getInstance()->showTime();
        cout<<toString(_color)<<" wolf "<<_cnt<<" born"<<endl;

    }

}

int main()
{
    int n;
    int x;
    vector<int> Headquarte_hp;
    vector<int> cityNum;
    vector<size_t> endTime;
    vector<vector<int>> warriorHp;
    vector<vector<int>> warriorATK;
    cin>>n;
    for(int i=0;i!=n;++i){
        vector<int> warrior_hp;
        vector<int> warrior_atk;
        cin>>x;
        Headquarte_hp.push_back(x);
        cin>>x;
        cityNum.push_back(x);
        cin>>x;
        endTime.push_back(x);
        for(int j=0;j!=5;++j){
            cin>>x;
            warrior_hp.push_back(x);

        }
        warriorHp.push_back(warrior_hp);
        for(int j=0;j!=5;++j){
            cin>>x;
            warrior_atk.push_back(x);

        }
        warriorATK.push_back(warrior_atk);

    }

    for(int i=0;i!=n;++i){
        cout<<"Case:"<<i+1<<endl;
        GameTime::getInstance()->initTime();
        vector<City*> cityVec;
        for(int j=0; j!=cityNum[i]; ++j){
            cityVec.push_back(new City(j+1));

        }
        Headquarter* redHead = new RedHeadquarter(Headquarte_hp[i],warriorHp[i],warriorATK[i],cityVec);
        Headquarter* blueHead = new BlueHeadquarter(Headquarte_hp[i],warriorHp[i],warriorATK[i],cityVec);
        while(GameTime::getInstance()->getTime() <= endTime[i]){
            //00
            redHead->createWarrior();
            redHead->setEnemy(blueHead);
            blueHead->createWarrior();
            blueHead->setEnemy(redHead);
            GameTime::getInstance()->updateTime();
            //GameTime::getInstance()->showTime();
            //10
            for(auto it=redHead->_warriorVec.begin(); it!=redHead->_warriorVec.end(); ++it){
                (*it)->forward();
            }
            for(auto it=blueHead->_warriorVec.begin(); it!=blueHead->_warriorVec.end(); ++it){
                (*it)->forward();
            }
            for(auto it=cityVec.begin(); it!=cityVec.end(); ++it){
                (*it)->mached();
            }
            redHead->arrive();
            if(blueHead->istaken()) break;
            blueHead->arrive();
            if(redHead->istaken()) break;
            GameTime::getInstance()->updateTime();
            //20
            for(auto it=cityVec.begin(); it!=cityVec.end(); ++it){
                (*it)->produce();
            }
            GameTime::getInstance()->updateTime();
            //30
            for(auto it=cityVec.begin(); it!=cityVec.end(); ++it){
                (*it)->putElement1();
            }
            GameTime::getInstance()->updateTime();
            //40
            for(auto it=cityVec.begin(); it!=cityVec.end(); ++it){
                (*it)->fight();//fight/backfight/die/yell
            }
            redHead->reward();
            blueHead->reward();
            for(auto it=cityVec.begin(); it!=cityVec.end(); ++it){
                (*it)->putElement2();
            }
            for(auto it=cityVec.begin(); it!=cityVec.end(); ++it){
                (*it)->raiseFlag();
                (*it)->initWarrior();
            }
            redHead->clearWarrior();
            blueHead->clearWarrior();
            redHead->initWin();
            blueHead->initWin();
            GameTime::getInstance()->updateTime();
            //50
            redHead->reportHp();
            blueHead->reportHp();
            GameTime::getInstance()->updateTime();
        }
    }

    return 0;
}
