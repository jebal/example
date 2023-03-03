#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <deque>
#include <list>
#include <set>
#include <algorithm>

#include "calc_dis_func.h"


typedef std::map<std::string, std::deque<std::string>> RelaGraphMap;
typedef std::map<int, std::map<int, int>>              AddressMap;


// 广度优先搜索算法
void breadth_first_search(const RelaGraphMap& mapRela, const std::string& target)
{
    std::deque<std::string> dqTarget, dqChecked;
    RelaGraphMap::const_iterator it = mapRela.find("you");    
    if (it != mapRela.end())
    {
        dqTarget = it->second;

        //
        while (!dqTarget.empty())
        {            
            const std::string& curFriend = dqTarget.front();
            if (!std::count(dqChecked.begin(), dqChecked.end(), curFriend))
            {
                if (curFriend == target)
                {
                    std::cout << "target " << target << " finded!" << std::endl;
                    return;
                }
                else
                {
                    dqChecked.push_back(curFriend);

                    //
                    RelaGraphMap::const_iterator itTmp = mapRela.find(curFriend);    
                    if (itTmp != mapRela.end())
                    {
                        dqTarget.insert(dqTarget.end(), itTmp->second.begin(), itTmp->second.end());
                    }

                    std::cout << "via fiend: " << curFriend << std::endl;
                }
            }

            dqTarget.pop_front();
        }
    }

    return;
}

int getMinCostID(std::map<int, int>& mapOpen, std::set<int>& setHandled, int& weight)
{
    weight = 9999999;
    int minID = 0;
    for (const auto item : mapOpen)
    {
        if (setHandled.end() == setHandled.find(item.first))
        {
            if (item.second < weight)
            {
                weight = item.second;
                minID = item.first;
            }
        }
    }

    return minID;
}

void printIntMap(const std::map<int, int>& mapInt)
{
    std::cout << "map begin -------------" << std::endl;
    
    for (const auto item : mapInt)
    {
        std::cout << "key: " << item.first << "  value: " << item.second << std::endl;
    }

    std::cout << "map end -------------" << std::endl;
}

// dijkstra
void dijkstra(const AddressMap& mapAddr, int startID, int endID)
{
    std::map<int, int> mapOpen, mapPath;
    std::set<int> setHandled;

    AddressMap::const_iterator it = mapAddr.find(startID);
    if (mapAddr.end() != it)
    {
        mapOpen.insert(it->second.begin(), it->second.end());
        for (const auto& item : it->second)
        {
            mapPath[item.first] = startID;
        }
    }

    int weight = 0;
    int curAddrID = getMinCostID(mapOpen, setHandled, weight);
    
    while (curAddrID) 
    {
        it = mapAddr.find(curAddrID);
        if (mapAddr.end() != it)
        {
            for (const auto& item : it->second)
            {
                std::map<int, int>::iterator itNode = mapOpen.find(item.first);
                if (itNode != mapOpen.end())
                {
                    if (item.second + weight < itNode->second)
                    {
                        itNode->second = item.second + weight;
                        mapPath[item.first] = curAddrID;                    

                        std::cout << "cur address id: " <<  item.first << " father id: " << curAddrID << std::endl;
                    }
                    else
                    {
                        std::cout << "delete cur address id: " << curAddrID << std::endl;
                    }
                }
                else
                {
                    mapOpen.insert({item.first, item.second + weight}); 
                    mapPath[item.first] = curAddrID;
                }                
            }
        }

        //printIntMap(mapOpen);        
        setHandled.insert(curAddrID);
       
        curAddrID = getMinCostID(mapOpen, setHandled, weight);    


        //std::cout << "cur address id: " << curAddrID << std::endl;
    }

    printIntMap(mapPath);

    //
    for (int node = endID; node != startID; )
    {
        std::map<int, int>::const_iterator it = mapPath.find(node);
        if (mapPath.end() != it)
        {
            std::cout << node << "-->";
            node = it->second;
        }
        else
        {
            break;            
        }
    }

    std::cout << startID;
}

//////////////////////////////////////////////////////////////////////////////

// astar

// 图信息
int graph_data[GRAPH_SIZE] = {
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0
};

void printGraphPath(int graph_data[GRAPH_SIZE])
{
    std::cout << "begin ----------------------" << std::endl;
    for (int i = 0; i < GRAPH_HEIGHT; ++ i)
    {
        for (int j = 0; j < GRAPH_WIDTH; ++ j)
        {
            std::cout << std::setw(4) << std::setfill(' ') << graph_data[i*GRAPH_WIDTH + j];
        }

        std::cout << std::endl;
    }
    std::cout << "end ----------------------" << std::endl;
}

void printNodeList(const OPEN_LIST& validNodeList)
{
    std::cout << "valide list ----------------------" << std::endl;
    OPEN_LIST::const_iterator it = validNodeList.begin();
    OPEN_LIST::const_iterator itEnd = validNodeList.end();
    for ( ; it != itEnd; ++ it)
    {
        std::cout << it->pNode << "-->" << it->cost << "   ";
    }
    std::cout << "end ----------------------" << std::endl;
}


void pushOpenList(OPEN_LIST& validNodeList, PathNode* pNode, int cost)
{
    if (NULL == pNode)
    {
        return;
    }

    OpenListNode node(pNode, cost);
    if (!validNodeList.empty())
    {
        OPEN_LIST::iterator it = validNodeList.begin();
        OPEN_LIST::iterator itEnd = validNodeList.end();
        for ( ; it != itEnd; ++ it)
        {
            if (cost < it->cost)
            {
                validNodeList.insert(it, node);
                break;
            }
        }
    }
    else
    {
        validNodeList.push_back(node);  
    }    
}

PathNode *popOpenList(OPEN_LIST& validNodeList)
{
    PathNode *ret = NULL;
    if (!validNodeList.empty())
    {
        ret = validNodeList.front().pNode;
        validNodeList.pop_front();
    }

    return ret;
}

bool isBlock(const Point& pos)
{
    int index = pos.getIndex();
    if (index < GRAPH_SIZE)
    {
        return graph_data[index];
    }
    
    return false;
}

// A星搜索算法
void astar_search(const Point& startPos, const Point& endPos)
{
    // 缓存开销
    int disMap[GRAPH_SIZE];
    std::fill_n(disMap, GRAPH_SIZE, MAX_DWORD_SIZE);

    // 记录路径点数据(这里将会存放最终结果，路径点回溯)
    PathNode pathNodeData[GRAPH_SIZE * 8 + 1];

    // 起始点
    PathNode* pCurNode = &pathNodeData[GRAPH_SIZE*8];
    pCurNode->pos = startPos;
    pCurNode->father = NULL;
    pCurNode->cost = 0;

    // 有效节点列表（待检测的节点，按开销小到大排序，每次取开销最小节点）
    OPEN_LIST listValidNode;
    pushOpenList(listValidNode, pCurNode, pCurNode->cost + euclidian(startPos, endPos));
   
    int findedCnt = 0;
	//无论如何,循环超过MaxNum次则放弃
	while (findedCnt < GRAPH_SIZE)
    {
        pCurNode = popOpenList(listValidNode);
		if (NULL == pCurNode)
		{
			//目标点不可达
			return;
		}

		if (pCurNode->pos == endPos)
		{
			//找到到达目的地的路径
			break;
		}

        // 该点的8个方向
        for (int i = 0; i < 8; ++ i)
		{
            Point tempPos = pCurNode->pos;
            tempPos.x += adjust[i].x;
            tempPos.y += adjust[i].y;
			            
            if (!isBlock(tempPos))
			{
                bool bCanWalk = true;

				//对路径进行回溯
				PathNode *p = pCurNode;
				while (p)
				{
					if (p->pos == tempPos)
					{
						//发现坐标点已经在回溯路径中，不能向前走(检查是否在close table)
						bCanWalk = false;
						break;
					}
					p = p->father;
				}

				//如果路径回溯成功，表示这个点是可行走的
				if (bCanWalk)
				{
					int cost = pCurNode->cost + STEP;
					int index = tempPos.getIndex();
					if (index >= 0 && index < GRAPH_SIZE && cost < disMap[index])
					{
						//这条路径比上次计算的路径还要短，需要加入到最短路径队列中
						disMap[index] = cost;
						
                        PathNode *pNewNode = &pathNodeData[findedCnt * 8 + i];
						pNewNode->pos = tempPos;
						pNewNode->cost = cost;
						pNewNode->father = pCurNode;

                        pushOpenList(listValidNode, pNewNode, pNewNode->cost + euclidian(tempPos, endPos));		

                        std::cout << "push list: (" << tempPos.x << ", " << tempPos.y << ") cost:" << cost << std::endl;
					}
				}
			}
		}

        printNodeList(listValidNode);

		++ findedCnt;
	}

	if (findedCnt < GRAPH_SIZE)
	{
        graph_data[startPos.getIndex()] = 7;
        graph_data[endPos.getIndex()] = 7;

		//最终路径在PointHead中,但只走一步
		while (pCurNode)
		{
			//倒数第二个节点
			if (pCurNode->father)
			{
                int index = pCurNode->pos.getIndex();
                if (GRAPH_SIZE <= index)
                {
                    std::cout << "====== Array out of bounds error =======" << std::endl;
                    break;
                }

                graph_data[index] = 7;				
			}
            else
            {
                break;    
            }

			pCurNode = pCurNode->father;
		}

        printGraphPath(graph_data);
	}
}


int main(int argc, const char** argv) 
{   

    /*
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0    
    */
    astar_search(Point(1, 1), Point(7, 9));
    //printGraphPath(graph_data);

//     PathNode pathNodeData[GRAPH_SIZE * 8 + 1];

//     OPEN_LIST validNodeList;
//     PathNode *pNewNode = &pathNodeData[1 * 8 + 1];
//     pNewNode->pos = Point(2, 3);
//     pNewNode->cost = 32;
//     pNewNode->father = NULL;
//     pushOpenList(validNodeList, pNewNode, pNewNode->cost + 43);
//     printNodeList(validNodeList);

//     pNewNode = &pathNodeData[1 * 8 + 2];
//     pNewNode->pos = Point(3, 4);
//     pNewNode->cost = 2;
//     pNewNode->father = NULL;
//     pushOpenList(validNodeList, pNewNode, pNewNode->cost + 12);
// printNodeList(validNodeList);
//     pNewNode = &pathNodeData[1 * 8 + 3];
//     pNewNode->pos = Point(4, 5);
//     pNewNode->cost = 3;
//     pNewNode->father = NULL;
//     pushOpenList(validNodeList, pNewNode, pNewNode->cost + 12);

//     printNodeList(validNodeList);

    // validNodeList.pop_front();

    // printNodeList(validNodeList);

/*
    RelaGraphMap mapRelaGraph;

    std::deque<std::string> dqFriend;
    dqFriend.push_back("alice");
    dqFriend.push_back("bob");
    dqFriend.push_back("claire");
    mapRelaGraph.insert({"you", dqFriend});

    dqFriend.clear();
    dqFriend.push_back("anuj");
    dqFriend.push_back("peggy");
    mapRelaGraph.insert({"bob", dqFriend});

    dqFriend.clear();
    dqFriend.push_back("peggy");
    mapRelaGraph.insert({"alice", dqFriend});

    dqFriend.clear();
    dqFriend.push_back("thom");
    dqFriend.push_back("jonny");
    mapRelaGraph.insert({"claire", dqFriend});

    dqFriend.clear();
    mapRelaGraph.insert({"anuj", dqFriend});
    mapRelaGraph.insert({"peggy", dqFriend});
    mapRelaGraph.insert({"peggy", dqFriend});
    mapRelaGraph.insert({"jonny", dqFriend});

    breadth_first_search(mapRelaGraph, "claire");

    //
    AddressMap mapAddr;

    // id --> weight
    std::map<int, int> mapNborWeight;    
    mapNborWeight.insert({222, 5});
    mapNborWeight.insert({333, 0});
    mapAddr.insert({111, mapNborWeight});

    mapNborWeight.clear();
    mapNborWeight.insert({444, 15});
    mapNborWeight.insert({555, 20});
    mapAddr.insert({222, mapNborWeight});

    mapNborWeight.clear();
    mapNborWeight.insert({444, 30});
    mapNborWeight.insert({555, 35});
    mapAddr.insert({333, mapNborWeight});

    mapNborWeight.clear();
    mapNborWeight.insert({666, 20});
    mapNborWeight.insert({777, 10});
    mapAddr.insert({444, mapNborWeight});

    mapNborWeight.clear();
    mapNborWeight.insert({666, 10});
    mapNborWeight.insert({777, 5});
    mapAddr.insert({555, mapNborWeight});

    mapNborWeight.clear();
    mapNborWeight.insert({888, 5});
    mapAddr.insert({666, mapNborWeight});

    mapNborWeight.clear();
    mapNborWeight.insert({888, 10});
    mapAddr.insert({777, mapNborWeight});

    dijkstra(mapAddr, 111, 888);
*/
    return 0;
}
