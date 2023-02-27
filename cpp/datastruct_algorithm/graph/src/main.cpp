#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <list>
#include <set>
#include <algorithm>


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


// A星搜索算法
void astar_search()
{
    
}


int main(int argc, const char** argv) 
{
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

    return 0;
}