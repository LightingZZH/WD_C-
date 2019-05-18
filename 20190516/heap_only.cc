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

    void * operator new(size_t sz)
    {
        void *ret=malloc(sz);
        cout<<"void * operator new(size_t)"<<endl;
        return ret;
    }

    void operator delete(void * ret)
    {
        cout<<"void * operator delete(void *)"<<endl;
        free(ret);
    }

    void print() const
    {
        cout<<"name: "<<_name<<endl
            <<"id  : "<<_id<<endl;
    }

    void destroy()
    {
        delete this;
    }

private:
    ~Student()
    {
        delete [] _name;
        cout<<"~Student()"<<endl;
    }
    char * _name;
    int _id;
};

int main()
{
    Student *pstu=new Student("Mike",100);
    pstu->print();
    pstu->destroy();

   // Student stu("Mary",101);//error
    return 0;
}

