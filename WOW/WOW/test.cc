//#include "wow.h"
#include "warrior.h"

int main()
{
    //int Headquarte_hp = 99;
    //int cityNum = 2;
    //size_t time = 1000;
    //vector<int> warrior_hp = {10,20,50,50,30};
    //vector<int> warrior_atk = {20,50,50,50,50};
    //vector<City*> cityVec;

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
        cout<<"case:"<<i+1<<endl;
        GameTime::getInstance()->initTime();
        vector<City*> cityVec;
        for(int j=0; j!=cityNum[i]; ++j){
            cityVec.push_back(new City(j+1));
        }
        Headquarter* redHead = new RedHeadquarter(Headquarte_hp[i],warriorHp[i],warriorATK[i],cityVec);
        Headquarter* blueHead = new BlueHeadquarter(Headquarte_hp[i],warriorHp[i],warriorATK[i],cityVec);
        while(GameTime::getInstance()->getTime() <= endTime[i]){
            //00
            //cout<<"1"<<endl;
            redHead->createWarrior();
            //cout<<"2"<<endl;
            redHead->setEnemy(blueHead);
            //cout<<"3"<<endl;
            blueHead->createWarrior();
            //cout<<"4"<<endl;
            blueHead->setEnemy(redHead);
            //cout<<"5"<<endl;
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

