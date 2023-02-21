#include <iostream>
#include <vector>
#include <algorithm>

unsigned int euclid(unsigned int a, unsigned int b)
{   
    unsigned int minValue = std::min(a, b);
    unsigned int modValue = std::max(a, b) % minValue;
    if (0 == modValue)
    {
        return minValue;
    }            
    else
    {
        return euclid(minValue, modValue);
    }
    
    return 1;
}


int main(int argc, const char** argv) 
{   
    /*
     欧几里得算法（求两个数的最大公约数）
     定理：两个整数的最大公约数等于其中较小的那个数和两数相除余数的最大公约数
     两数的最大公约数求法:
        给定两数 a, b        
        while (true)
        {
            modValue = mod(max(a, b), min(a, b))
            if (0 == modValue)
                return min(a, b);
            else
            {
                a = min(a, b);
                b = modValue;
            }                
        }               
    */        
    std::cout << "euclid:" << euclid(82246808, 8344) << std::endl;

    return 0;
}