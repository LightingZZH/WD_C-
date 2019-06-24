//#include "wow.h"
#include "warrior.h"

void Warrior::getElement()
{
    _element = _city->getElement();
    _city->initElement();
    GameTime::getInstance()->showTime();
    cout<<toString(_color)<<" "<<toString(_type)<<" "
        <<_num<<" earn "<<_element<<" elements for his headquarter"<<endl;
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
