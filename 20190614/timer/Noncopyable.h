#ifndef __NONCOPYABLE
#define __NONCOPYABLE

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;
};

#endif
