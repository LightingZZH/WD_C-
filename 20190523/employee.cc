#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Person
{
public:
    Person(string name, int age)
    : _name(name)
    , _age(age)
    {
        cout<<"Person(string, int)"<<endl;
    }

    void display()
    {
        cout<<"name : "<<_name<<endl;
        cout<<"age : "<<_age<<endl;
    }

private:
    string _name;
    int _age;
};

class Employee
: public Person
{
public:
    Employee(string name,int age, string department, double salary)
    : Person(name, age)
    , _department(department)
    , _salary(salary)
    {
        cout<<"Employee(string, double)"<<endl;
    }

    double getSalary()
    {
        return _salary;
    }

    void display()
    {
        Person::display();
        cout<<"department : "<<_department<<endl;
        cout<<"salary : "<<_salary<<endl;
    }

private:
    string _department;
    double _salary;
};

int main()
{
    Employee e1("Bran",20,"111",100);
    Employee e2("Sana",23,"222",300);
    Employee e3("Arya",21,"333",150);

    e1.display();
    cout<<"-----------"<<endl;
    e2.display();
    cout<<"-----------"<<endl;
    e3.display();
    cout<<"-----------"<<endl;

    cout<<"Average : "<<(e1.getSalary()+e2.getSalary()+e3.getSalary())/3<<endl;
    return 0;
}

