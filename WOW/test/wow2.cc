#include "wow2.h"
void Headquarter::CreateDragon()
{
    int n = _time+1;
    _hp -= _dragonHp;
    ++_dragon;
    string weapon;
    int ret = n%3;
    if(ret==0) weapon="sword";
    else if(ret==1) weapon="bomb";
    else weapon="arrow";
    double morale = 1.0*_hp/3;
    Dragon dragon(n,_dragonHp,weapon,morale);
    printf("%03d %s dragon %d born with strength %d,%d dragon in %s headquarter\n",_time,_color.c_str(),n,_dragonHp,_dragon,_color.c_str());
    dragon.display();
    _time = n;
}

void Headquarter::CreateNinja()
{
    int n = _time+1;
    _hp -= _ninjaHp;
    ++_ninja;
    string weapon1;
    string weapon2;
    int ret1 = n%3;
    int ret2 = (n+1)%3;
    if(ret1==0) weapon1="sword";
    else if(ret1==1) weapon1="bomb";
    else weapon1="arrow";
    if(ret2==0) weapon2="sword";
    else weapon2="bomb";
    if(ret2==2) weapon2="arrow";
    Ninja ninja(n,_ninjaHp,weapon1,weapon2);
    printf("%03d %s ninja %d born with strength %d,%d ninja in %s headquarter\n",_time,_color.c_str(),n,_ninjaHp,_ninja,_color.c_str());
    ninja.display();
    _time = n; 
}
 
void Headquarter::CreateIceman()
{
    int n = _time+1;
    _hp -= _icemanHp;
    ++_iceman;
    string weapon;
    int ret = n%3;
    if(ret==0) weapon="sword";
    else if(ret==1) weapon="bomb";
    else weapon="arrow";
    Iceman iceman(n,_icemanHp,weapon);
    printf("%03d %s iceman %d born with strength %d,%d iceman in %s headquarter\n",_time,_color.c_str(),n,_icemanHp,_iceman,_color.c_str());
    iceman.display();
    _time = n;
}

void Headquarter::CreateLion()
{    
    int n = _time+1;
    _hp -= _lionHp;
    ++_lion;
    int loyalty = _hp;
    Lion lion(n,_lionHp,loyalty);
    printf("%03d %s lion %d born with strength %d,%d lion in %s headquarter\n",_time,_color.c_str(),n,_lionHp,_lion,_color.c_str());
    lion.display();
    _time = n;
}

void Headquarter::CreateWolf()
{
    int n = _time+1;
    _hp -= _wolfHp;
    ++_wolf;
    Wolf wolf(n,_wolfHp);
    printf("%03d %s wolf %d born with strength %d,%d wolf in %s headquarter\n",_time,_color.c_str(),n,_wolfHp,_wolf,_color.c_str());
    _time = n;
}

void Headquarter::Create()
{
    if(_flag==-3) return;
    if(_color=="red"){
        if(_flag!=-1){
            int ret;
            if(_flag!=-2) ret = _flag;
            else ret = _time % 5;
            switch(ret)
            {
                case 0 :
                    if(_hp < _icemanHp){
                        if(_hp >= _lionHp) _flag = 1;
                        else if(_hp >= _wolfHp) _flag = 2;
                        else if(_hp >= _ninjaHp) _flag = 3;
                        else if(_hp >= _dragonHp) _flag = 4;
                        else _flag = -1;
                    }else{
                        CreateIceman();
                        _flag = -2;
                    }break;
                case 1 : 
                    if(_hp < _lionHp){
                        if(_hp >= _wolfHp) _flag = 2;
                        else if(_hp >= _ninjaHp) _flag = 3;
                        else if(_hp >= _dragonHp) _flag = 4;
                        else if(_hp >= _icemanHp) _flag = 0;
                        else _flag = -1;
                    }else{
                        CreateLion();
                        _flag = -2;
                    }break;
                case 2 : 
                    if(_hp < _wolfHp){
                        if(_hp >= _ninjaHp) _flag = 3;
                        else if(_hp >= _dragonHp) _flag = 4;
                        else if(_hp >= _icemanHp) _flag = 0;
                        else if(_hp >= _lionHp) _flag = 1;
                        else _flag = -1;
                    }else{
                        CreateWolf();
                        _flag = -2;
                    }break;
                case 3 :
                    if(_hp < _ninjaHp){
                        if(_hp >= _dragonHp) _flag = 4;
                        else if(_hp >= _icemanHp) _flag = 0;
                        else if(_hp >= _lionHp) _flag = 1;
                        else if(_hp >= _wolfHp) _flag = 2;
                        else _flag = -1;
                    }else{
                        CreateNinja();
                        _flag = -2;
                    }break;
                case 4 : 
                    if(_hp < _dragonHp){
                        if(_hp >= _icemanHp) _flag = 0;
                        else if(_hp >= _lionHp) _flag = 1;
                        else if(_hp >= _wolfHp) _flag = 2;
                        else if(_hp >= _ninjaHp) _flag = 3;
                        else _flag = -1;
                    }else{
                        CreateDragon();
                        _flag = -2;
                    }break;
            }
            if(_flag==-1){
                printf("%03d %s headquarter stops making warriors\n",_time,_color.c_str());
                _flag = -3;
            }
        }
    }

    else if(_color=="blue"){
        if(_flag!=-1){
            int ret;
            if(_flag!=-2) ret = _flag;
            else ret = _time % 5;
            switch(ret)
            {
                case 0 :
                    if(_hp < _lionHp){
                        if(_hp >= _dragonHp) _flag = 1;
                        else if(_hp >= _ninjaHp) _flag = 2;
                        else if(_hp >= _icemanHp) _flag = 3;
                        else if(_hp >= _wolfHp) _flag = 4;
                        else _flag = -1;
                    }else{
                        CreateLion(); 
                        _flag = -2;
                    }break;
                case 1 : 
                    if(_hp < _dragonHp){
                        if(_hp >= _ninjaHp) _flag = 2;
                        else if(_hp >= _icemanHp) _flag = 3;
                        else if(_hp >= _wolfHp) _flag = 4;
                        else if(_hp >= _lionHp) _flag = 0;
                        else _flag = -1;
                    }else{
                        CreateDragon();
                        _flag = -2;
                    }break;
                case 2 : 
                    if(_hp < _ninjaHp){
                        if(_hp >= _icemanHp) _flag = 3;
                        else if(_hp >= _wolfHp) _flag = 4;
                        else if(_hp >= _lionHp) _flag = 0;
                        else if(_hp >= _dragonHp) _flag = 1;
                        else _flag = -1;
                    }else{
                        CreateNinja();
                        _flag = -2;
                    }break;
                case 3 :
                    if(_hp < _icemanHp){
                        if(_hp >= _wolfHp) _flag = 4;
                        else if(_hp >= _lionHp) _flag = 0;
                        else if(_hp >= _dragonHp) _flag = 1;
                        else if(_hp >= _ninjaHp) _flag = 2;
                        else _flag = -1;
                    }else{
                        CreateIceman();
                        _flag = -2;
                    }break;
                case 4 : 
                    if(_hp < _wolfHp){
                        if(_hp >= _lionHp) _flag = 0;
                        else if(_hp >= _dragonHp) _flag = 1;
                        else if(_hp >= _ninjaHp) _flag = 2;
                        else if(_hp >= _icemanHp) _flag = 3;
                        else _flag = -1;
                    }else{
                        CreateWolf();
                        _flag = -2;
                    }break;
            }
            if(_flag==-1){
                printf("%03d %s headquarter stops making warriors\n",_time,_color.c_str());
                _flag = -3;
            }
        }
    }
}
