#include <iostream>


#define SAFE_DELETE(ptr)        if (ptr) { delete ptr; ptr = NULL; }   
#define SAFE_DELETE_ARR(ptr)    if (ptr) { delete [] ptr; ptr = NULL; }   


struct stListNode
{
public:
    int data;
    stListNode* pNext;

    stListNode() : data(0), pNext(NULL){}
};

void insertData(stListNode* pList, int data, int pos=0)
{
    if (pList)
    {
        stListNode* pLastNode = pList;
        stListNode* pCurNode = pList->pNext;
        while (pCurNode) 
        {            
            pLastNode = pCurNode;
            pCurNode = pCurNode->pNext;
        }
        
        stListNode* pNewNode = new stListNode();
        pNewNode->data = data;        
        pLastNode->pNext = pNewNode;
    }
}

void deleteData(stListNode* pList, int data)
{
    if (pList)
    {
        stListNode* pLastNode = pList;
        stListNode* pCurNode = pList->pNext;
        while (pCurNode) 
        {
            if (pCurNode->data == data)
            {
                pLastNode->pNext = pCurNode->pNext;
                SAFE_DELETE(pCurNode);

                break;
            }

            pLastNode = pCurNode;
            pCurNode = pCurNode->pNext;
        }
    }
}

void deleteList(stListNode*& pList)
{
    for (stListNode* pCurNode = pList; NULL != pCurNode; )
    {
        if (pCurNode)
        {            
            stListNode* pNext = pCurNode->pNext;
            SAFE_DELETE(pCurNode);
            pCurNode = pNext;
        }
        else
        {
            break;
        }
    }

    pList = NULL;   
}

void printList(stListNode* pList)
{
    if (pList)
    {
        for (stListNode* pCurNode = pList; NULL != pCurNode; pCurNode = pCurNode->pNext)
        {
            std::cout << "Node:" << pCurNode->data << " --> ";
        }
    }   

    std::cout << "NULL" << std::endl;
}



int main (int argc, char *argv[])
{   
    stListNode* pHead = new stListNode;
    printList(pHead);

    insertData(pHead, 10);
    insertData(pHead, 32);
    insertData(pHead, 423);
    insertData(pHead, 97);
    
    printList(pHead);



    deleteList(pHead);

    printList(pHead);

    return 0;
}
