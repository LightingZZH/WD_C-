#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <memory>
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::unique_ptr;

class Observer;
class Subject
{
public:
    virtual void attach(Observer *) = 0;
    virtual void detach(Observer *) = 0;
    virtual void notify() = 0;

    virtual ~Subject() {}
};

class Observer
{
public:
    virtual void update() = 0;
    //virtual void update(Subject *) = 0; //拉模式    即观察者主动获取
    //virtual void update(const string & msg) = 0;    //推模式
    virtual string name() const = 0;

    virtual ~Observer() {}
};

class Ring
: public Subject
{
public:
    void attach(Observer *ob)
    {
        auto it = find(_ob.begin(), _ob.end(), ob);
        if(it == _ob.end()){
            _ob.push_back(ob);
        }
    }

    void detach(Observer *ob)
    {
        auto it = find(_ob.begin(), _ob.end(), ob);
        if(it != _ob.end()){
            _ob.erase(it);
        }
    }

    void alarm()
    {   notify();   }

    void notify()
    {
        for(auto & c : _ob){
            c->update();
        }
    }
private:
    list<Observer *> _ob;
};

class Baby
: public Observer
{
public:
    Baby(const string & name)
    : _name(name)
    {}

    string name() const {   return _name;   }

    void update()
    {
        ::srand(::clock());
        int random = ::rand()%100;
        if(random < 70){
            cout<<"Baby "<<_name<<" is crying"<<endl;
        }else{
            cout<<"Baby "<<_name<<" is sleeping"<<endl;
        }
    }

private:
    string _name;
};

class Nurse
: public Observer
{
public:
    Nurse(const string & name)
    : _name(name)
    {}

    string name() const { return _name;   }

    void update()
    {
        ::srand(::clock());
        int random = ::rand()%100;
        if(random < 70){
            cout<<"Nurse "<<_name<<" will open the door"<<endl;
        }else{
            cout<<"Nures"<<_name<<" is sleeping"<<endl;
        }
    }

private:
    string _name;
};

class Guest
{
public:
    Guest(const string & name)
    : _name(name)
    {}

    void knock(Ring & ring)
    {
        cout<<"Guest "<<_name<<" knocking the door"<<endl;
        ring.alarm();
    }

private:
    string _name;
};

int main()
{
    Ring ring;
    unique_ptr<Observer> baby1(new Baby("1111"));
    unique_ptr<Observer> baby2(new Baby("2222"));
    unique_ptr<Observer> nurse1(new Nurse("33"));
    unique_ptr<Observer> nurse2(new Nurse("44"));

    ring.attach(baby1.get());
    ring.attach(baby2.get());
    ring.attach(nurse1.get());
    ring.attach(nurse2.get());
    
    Guest guest("xx");
    guest.knock(ring);

    cout<<"-------------"<<endl;
    ring.detach(nurse1.get());
    guest.knock(ring);

    return 0;
}

