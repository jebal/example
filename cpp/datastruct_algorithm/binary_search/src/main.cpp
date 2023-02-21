#include <iostream>
#include <vector>

static int s_search_cnt;

int binary_search(const std::vector<int>& vData, int leftPos, int rightPos, int searchData)
{
    ++ s_search_cnt;

    std::cout << "search_cnt: " << s_search_cnt \
              << " find data:" << searchData \
              << " left:" <<  leftPos << " right:" << rightPos << std::endl;

    int midPos = leftPos + (rightPos - leftPos) / 2;
    if (vData[leftPos] == searchData) { return leftPos; }
    if (vData[midPos] == searchData) { return midPos; }
    if (vData[rightPos] == searchData) { return rightPos; }

    if (vData[leftPos] < searchData && searchData < vData[midPos])
    {
        return binary_search(vData, leftPos, midPos, searchData);
    }
    else if (vData[midPos] < searchData && searchData < vData[rightPos])
    {
        return binary_search(vData, midPos, rightPos, searchData);
    }

    return -1;
}


int main(int argc, const char** argv) 
{    
    std::vector<int> vData;
    for (size_t i = 4; i < 999; i++)
    {
        vData.push_back(i);
    }


    s_search_cnt = 0;
    int searchData = 876;
    int pos = binary_search(vData, 0, vData.size() - 1, searchData);
    std::cout << "find data:" << searchData << " pos:" <<  pos << "   search_cnt: " << s_search_cnt << std::endl;


    return 0;
}