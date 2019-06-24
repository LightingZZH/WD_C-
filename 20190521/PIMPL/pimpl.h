#ifndef __PIMPL_H__
#define __PIMPL_H__

class Line
{
public:
    Line(int,int,int,int);
    ~Line();

    void printLine() const;

    class LineImpl; //类的前向声明
private:
    LineImpl *_pImpl;
};

#endif
