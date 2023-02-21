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


stListNode* popMinNode(stListNode* pList)
{
    if (NULL == pList)
    {
        return NULL;
    }

    stListNode *pMinNode = pList->pNext;
    stListNode *pLastNode = pList, *pMinLastNode = pList;
    int data = 0;
    for (stListNode* pCurNode = pList->pNext; NULL != pCurNode; pLastNode = pCurNode, pCurNode = pCurNode->pNext)
    {
        if (data < pCurNode->data)
        {
            data = pCurNode->data;
            pMinNode = pCurNode;
            pMinLastNode = pLastNode;  
        }
    }

    // 删除该节点
    if (pMinLastNode && pMinNode)
    {
        pMinLastNode->pNext = pMinNode->pNext;
        pMinNode->pNext = NULL;
    }

    return pMinNode;
}


stListNode* selectSort(stListNode*& pList, bool bDesc=false)
{
    stListNode* pNewListHead = new stListNode;

    //
    stListNode* pMinNode = popMinNode(pList);
    stListNode* pNewListNode = pNewListHead;
    while (pMinNode)
    {       
        if (bDesc)
        {
            pNewListNode->pNext = pMinNode;
            pNewListNode = pMinNode;    
        }
        else
        {
            stListNode* pTmp = pNewListNode->pNext;
            pNewListNode->pNext = pMinNode;
            pMinNode->pNext = pTmp;
        }

        pMinNode = popMinNode(pList);        
    }

    SAFE_DELETE(pList)
   
    return pNewListHead;
}