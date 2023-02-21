#include <cstdio>
#include <iostream>

class Test
{

    enum
    {
     //   s_data = 10,
    };

public:
    static int s_data;

};

int Test::s_data = 90;

int& foo(int data)
{
    static int s_data;
    s_data = data;
    return s_data;
}

void printPI()
{
    long a = 10000, b = 0, c = 2800, d, e = 0, f[2801], g;
    for( ; b-c; ) f[b++] = a/5; 
    for( ;d = 0, g = c*2; c-=14, printf("%.4d",e+d/a), e = d%a)
        for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b);

    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    unsigned int modNum = 4;
    unsigned int data = 27;
    unsigned int result = data & (modNum - 1);

    std::cout << "mod: " << data % modNum << "  otherMod:" << result << std::endl;

    if (foo(1) == foo(2))
    {
        std::cout << "foo(1) result: " << foo(1) << "  foo(2) result: " << foo(2) << std::endl;
    }

    int arrData[10] = {21};
    for (int i = 0; i < 10; ++ i)
    {
        std::cout << "[" << i << "]: " << arrData[i] << std::endl;
    }

    int* p = new int[34];
    int* pData = p;
    *pData = 32;
    std::cout << "p[0]=" << p[0] << std::endl;

    printPI();

    std::cout << Test::s_data << std::endl;
    //getchar();
    return 0;
}
