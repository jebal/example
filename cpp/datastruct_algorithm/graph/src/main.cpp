#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <string.h>
#include <deque>
#include <list>
#include <set>
#include <algorithm>
#include <sstream>

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
int GRAPH_DATA[GRAPH_SIZE] = {
    0, 0, 0, 0, 9, 0, 0, 0, 9, 0,
    0, 0, 9, 0, 9, 0, 0, 0, 9, 0,
    0, 0, 9, 0, 9, 0, 0, 0, 9, 0,
    0, 0, 9, 0, 9, 0, 0, 0, 0, 0,
    0, 0, 9, 0, 9, 0, 9, 0, 0, 0,
    0, 0, 0, 0, 9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 9, 9, 0, 0,
    0, 0, 0, 9, 0, 0, 9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 9, 0, 0, 0
};

void printGraphPath(int graph_data[GRAPH_SIZE])
{    
    for (int i = 0; i < GRAPH_HEIGHT; ++ i)
    {
        for (int j = 0; j < GRAPH_WIDTH; ++ j)
        {
            if (0 == graph_data[i*GRAPH_WIDTH + j])// 可行点
            {
                std::cout << std::setw(4) << std::setfill(' ') << '*';
            }
            else if (1 == graph_data[i*GRAPH_WIDTH + j])// 起点
            {
                std::cout << std::setw(4) << std::setfill(' ') << '>';
            }
            else if (2 == graph_data[i*GRAPH_WIDTH + j])// 经过点
            {
                std::cout << std::setw(4) << std::setfill(' ') << '>';
            }
            else if (3 == graph_data[i*GRAPH_WIDTH + j])// 终点
            {
                std::cout << std::setw(4) << std::setfill(' ') << '>';
            }
            else if (9 == graph_data[i*GRAPH_WIDTH + j])// 阻挡点
            {
                std::cout << std::setw(4) << std::setfill(' ') << 'X';
            }
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printNodeList(const OPEN_LIST& validNodeList)
{
    std::cout << "valide list ------- ";
    OPEN_LIST::const_iterator it = validNodeList.begin();
    OPEN_LIST::const_iterator itEnd = validNodeList.end();
    for ( ; it != itEnd; ++ it)
    {
        std::cout << "(" << it->pNode->pos.x << ", " << it->pNode->pos.y << "):" << it->cost << " --> ";
    }
    std::cout << std::endl;
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
                return;
            }
        }
    }
    
    validNodeList.push_back(node);
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
        return GRAPH_DATA[index];
    }
    
    return false;
}

// A星搜索算法
void astar_search(const Point& startPos, const Point& endPos, calc_cost_func cost_func, bool bDirCost=false)
{
    int graph_data[GRAPH_SIZE];
    memcpy(graph_data, GRAPH_DATA, sizeof(int) * GRAPH_SIZE);

    // 缓存开销
    int disMap[GRAPH_SIZE];
    std::fill_n(disMap, GRAPH_SIZE, MAX_DWORD_SIZE);

    // 记录路径点数据(这里将会存放最终结果，路径点回溯)
    const int PathNodeSize = GRAPH_SIZE * 8 + 1;
    PathNode pathNodeData[PathNodeSize];

    // 起始点
    PathNode* pCurNode = &pathNodeData[GRAPH_SIZE*8];
    pCurNode->pos = startPos;
    pCurNode->father = NULL;
    pCurNode->dir = -1;
    pCurNode->cost = 0;
    
    // 有效节点列表（待检测的节点，按开销小到大排序，每次取开销最小节点）
    OPEN_LIST listValidNode;
    pushOpenList(listValidNode, pCurNode, pCurNode->cost + cost_func(startPos, endPos));

    std::set<int> setChecked;
   
    int findedCnt = 0;
	//无论如何,循环超过MaxNum次则放弃
	while (findedCnt < GRAPH_SIZE)
    {
        pCurNode = popOpenList(listValidNode);
		if (NULL == pCurNode)
		{
			//目标点不可达
        //    std::cout << "Node NULL" << std::endl;
			break;
		}

        int posIndex = pCurNode->pos.getIndex();
        if (setChecked.find(posIndex) != setChecked.end())
        {
         //   std::cout << "Node checked (" << pCurNode->pos .x << ", " << pCurNode->pos .y << ")" << std::endl;
            continue;
        }
        
        setChecked.insert(posIndex);

        //
		if (pCurNode->pos == endPos)
		{
		//	std::cout << "arrived! (" << pCurNode->pos .x << ", " << pCurNode->pos .y << ")" << std::endl;
			break;
		}

      //  std::cout << "pop node (" << pCurNode->pos .x << ", " << pCurNode->pos .y << ")" << std::endl;

        // 该点的8个方向
        for (int i = 0; i < 8; ++ i)
		{
            Point tempPos = pCurNode->pos;
            tempPos.x += adjust[i].x;
            tempPos.y += adjust[i].y;
			            
            int roundPosIndex = tempPos.getIndex();
            if (-1 == roundPosIndex)
            {           
             //   std::cout << "(" << tempPos.x << ", " << tempPos.y << ") pos error" << std::endl;     
                continue;
            }
            
            if (setChecked.find(roundPosIndex) != setChecked.end())
            {
             //   std::cout << "(" << tempPos.x << ", " << tempPos.y << ") pos checked" << std::endl;     
                continue;
            }

            if (!isBlock(tempPos))
			{
                //bool bCanWalk = true;

                // 每一个可行点，都获得一个转弯次数的开销
                // int changeDirCost = 0;
                // if (bDirCost)
                // {
                //     //对路径进行回溯
                //     PathNode *p = pCurNode;
                //     while (p)
                //     {
                //         if (p->father)
                //         {
                //             if (p->dir != p->father->dir)    
                //             {
                //                 changeDirCost += DIR_COST;
                //             }
                //         }
                        
                //         p = p->father;
                //     }
                // }

				//如果路径回溯成功，表示这个点是可行走的
				//if (bCanWalk)
				{
					int cost = pCurNode->cost + STEP;
					if (0 <= roundPosIndex && roundPosIndex < GRAPH_SIZE && cost < disMap[roundPosIndex])
					{	
                        disMap[roundPosIndex] = cost;

                        //
                        int findedIndex = findedCnt * 8 + i;
                        if (findedIndex < PathNodeSize)
                        {
                            PathNode *pNewNode = &pathNodeData[findedIndex];
                            pNewNode->pos = tempPos;
                            pNewNode->cost = cost;
                            pNewNode->father = pCurNode;
                            pNewNode->dir = i;

                            if (bDirCost && pCurNode->dir != i)
                            {                                
                                pNewNode->dirCost = pCurNode->dirCost + DIR_COST; 
                            }
                            
                            int totalCost = pNewNode->cost + cost_func(tempPos, endPos) + pNewNode->dirCost;
                            pushOpenList(listValidNode, pNewNode, totalCost);	

                         //   std::cout << "push list: (" << tempPos.x << ", " << tempPos.y << ") cost:" << cost << " totalCost:"<< totalCost << " findedIndex:" << findedIndex << std::endl;

                         //   printNodeList(listValidNode);
                        }
                        else
                        {
                         //   std::cout << "path index error (" << tempPos.x << ", " << tempPos.y << ") cost:" << cost << std::endl;
                        }
					}
                    else
                    {
                     //   std::cout << "(" << tempPos.x << ", " << tempPos.y << ") cost:" << cost << " last cost:" << disMap[roundPosIndex] << " pos error" << std::endl;
                    }
				}
			}
            else
            {
             //   std::cout << "(" << tempPos.x << ", " << tempPos.y << ") pos block " << std::endl;
            }
		}

       // printNodeList(listValidNode);
       // std::cout << "==================\r\n" << std::endl;

		++ findedCnt;
	}

	if (findedCnt < GRAPH_SIZE)
	{
        graph_data[startPos.getIndex()] = 1;
        graph_data[endPos.getIndex()] = 3;

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

                graph_data[index] = 2;				
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
        0, 0, 0, 0, 1, 1, 0, 0, 1, 0,
        0, 0, 1, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 1, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0    
           
        manhattan  euclidian  heuristic
        calc_cost_func = euclidian;
    */
    Point startPos = Point(1, 1), endPos = Point(7, 9);

    std::cout << "manhattan: ---- " << std::endl;
    astar_search(startPos, endPos, manhattan);
    std::cout << "manhattan with dir: ---- " << std::endl;
    astar_search(startPos, endPos, manhattan, true);

    // std::cout << "euclidian:" << std::endl;
    // astar_search(startPos, endPos, euclidian);
    // std::cout << "euclidian with dir: ---- " << std::endl;
    // astar_search(startPos, endPos, euclidian, true);
    
    // std::cout << "heuristic:" << std::endl;
    // astar_search(startPos, endPos, heuristic);
    // std::cout << "heuristic with dir:" << std::endl;
    // astar_search(startPos, endPos, heuristic, true);

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
