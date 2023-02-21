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

    return 0;
}