#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <list>
#include <set>
#include <algorithm>




void printIntMap(const std::map<int, int>& mapInt)
{
    std::cout << "map begin -------------" << std::endl;
    
    for (const auto item : mapInt)
    {
        std::cout << "key: " << item.first << "  value: " << item.second << std::endl;
    }

    std::cout << "map end -------------" << std::endl;
}

void printStringSet(const std::set<std::string>& setString)
{
    std::cout << "set begin -------------" << std::endl;
    
    for (const auto item : setString)
    {
        std::cout << item << std::endl;
    }

    std::cout << "set end -------------" << std::endl;
}



void greedy(const std::map<std::string, std::set<std::string>>& mapState, std::set<std::string>& setNeed)
{
    std::set<std::string> setFinal;
    while (!setNeed.empty())
    {
        std::set<std::string> setBestCovered;
        std::string bestState;

        for (const auto& state : mapState)
        {
            std::set<std::string> setCovered;
            std::set_intersection(setNeed.begin(), setNeed.end(), state.second.begin(), state.second.end(), inserter(setCovered, setCovered.begin()));

            if (setCovered.size() > setBestCovered.size())
            {
                setBestCovered = setCovered;
                bestState = state.first;
            }
        }

        std::set<std::string> setCutCovered;
        std::set_difference(setNeed.begin(), setNeed.end(), setBestCovered.begin(), setBestCovered.end(), inserter(setCutCovered, setCutCovered.begin()));
        setNeed = setCutCovered;
        setFinal.insert(bestState);
    }

    printStringSet(setFinal);
}


int main(int argc, const char** argv) 
{
    std::map<std::string, std::set<std::string>> mapState;
    
    /*
    stations["kone"]  =  set(["id",  "nv",  "ut"])
    stations["ktwo"]  =  set(["wa",  "id",  "mt"])
    stations["kthree"]  =  set(["or",  "nv",  "ca"])
    stations["kfour"]  =  set(["nv",  "ut"])
    stations["kfive"]  =  set(["ca",  "az"])

    */

    std::set<std::string> setCovered;
    setCovered.insert("id");
    setCovered.insert("nv");
    setCovered.insert("ut");
    mapState.insert({"kone", setCovered});
    
    setCovered.clear();
    setCovered.insert("wa");
    setCovered.insert("id");
    setCovered.insert("mt");
    mapState.insert({"ktwo", setCovered});

    setCovered.clear();
    setCovered.insert("or");
    setCovered.insert("nv");
    setCovered.insert("ca");
    mapState.insert({"kthree", setCovered});

    setCovered.clear();
    setCovered.insert("nv");
    setCovered.insert("ut");
    mapState.insert({"kfour", setCovered});

    setCovered.clear();
    setCovered.insert("ca");
    setCovered.insert("az");
    mapState.insert({"kfive", setCovered});

    std::set<std::string> setNeed;
    setNeed.insert("mt");
    setNeed.insert("wa");
    setNeed.insert("or");
    setNeed.insert("id");
    setNeed.insert("nv");
    setNeed.insert("ut");
    setNeed.insert("ca");
    setNeed.insert("az");
    greedy(mapState, setNeed);


    return 0;
}
