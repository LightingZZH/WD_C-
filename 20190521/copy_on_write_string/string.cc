#include <stdio.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main(void)
{
    string s1 = "hello,world";
    string s2 = s1;//只有发生复制时，才使用同样的空间

    string s3("hello,world1111");
    string s4("hello,world11111");
    string s5("hello,fjaslfjlsdjflkasjflksjalkfjsalkfjlksdjflksjflkjsdlkfjlsdjflksajfklsajflkjslkfjlkjfdlkjfad");
    cout << "s1 = " << s1 << endl
        << "s2 = " << s2 << endl
        << "s3 = " << s3 << endl;
    s3 = s2;

    cout << "sizeof(s1) = " << sizeof(s1) << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    printf("s4's address is %p\n", s4.c_str());
    printf("s5's address is %p\n", s5.c_str());

#if 1
    s1[0] = 'H';//发生写时复制,进行深拷贝,再修改

    cout << "s1 = " << s1 << endl
        << "s2 = " << s2 << endl
        << "s3 = " << s3 << endl;

    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
#endif
    return 0;
}
