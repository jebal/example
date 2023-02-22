#include <iostream>
#include <vector>

#include "linked_list.h"

int main(int argc, const char** argv) 
{    
    stListNode* pList = new stListNode;
    printList(pList);

    insertData(pList, 10);
    insertData(pList, 32);
    insertData(pList, 423);
    insertData(pList, 97);
    
    printList(pList);


    stListNode* pNewList = selectSort(pList);
    printList(pList);
    printList(pNewList);

    deleteList(pList);

    std::vector<int> vData;
    vData.push_back(890);
    vData.push_back(90);
    vData.push_back(992);
    vData.push_back(8);
    vData.push_back(80);
    vData.push_back(8000);
    vData.push_back(210);
    vData.push_back(90);
    vData.push_back(4342);
    vData.push_back(43);
    vData.push_back(-9);

    printVec(vData);

    quikeSort(vData);
    
    printVec(vData);

    return 0;
}