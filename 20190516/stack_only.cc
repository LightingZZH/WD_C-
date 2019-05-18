#include <string.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Student
{
public:
    Student(const char *name,int id)
    : _name(new char[strlen(name)+1]())
    , _id(id)
    {
        cout<<"Student(const char *,int)"<<endl;
        strcpy(_name,name);
    }

    void print() const
    {
        cout<<"name: "<<_name<<endl
            <<"id:   "<<_id<<endl;
    }

    ~Student()
    {
        delete [] _name;
        cout<<"~Student()"<<endl;
    }

private:
    void * operator new(size_t sz);
    void operator delete(void * ret);

    char * _name;
    int _id;
};

int main()
{
    //Student *pstu=new Student("Mike",100);//error

    Student stu("Mary",101);
    stu.print();

    return 0;
}

