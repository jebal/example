#ifndef __GRAPH_DATA_TYPE_H__
#define __GRAPH_DATA_TYPE_H__

const int GRAPH_WIDTH = 10;
const int GRAPH_HEIGHT = 10;
const int GRAPH_SIZE = GRAPH_WIDTH * GRAPH_HEIGHT;
const int MAX_DWORD_SIZE = 999999999;
const int STEP = 1;

const int STRAGHT_COST = 2;
const int DIR_COST = 10;
const int K_COST = 1;
const int D_COST = 2;

struct Point
{
    int x;
    int y;

    Point() : x(0), y(0){}
    Point(int posX, int posY) : x(posX), y(posY)
    {
    }

    int getIndex() const
    {
        if (x < 0 || y < 0 || GRAPH_HEIGHT <= y || GRAPH_WIDTH <= x)
        {
            return -1;
        }
        
        return y * GRAPH_WIDTH + x;
    }

    bool operator==(const Point& pt) const
    {
        return (x == pt.x) && (y == pt.y);
    }
};

struct PathNode
{
    Point pos;              // 当前点
    int cost;               // 记录从起始点到该点的开销
    int dir;                // 从父节点过来的方向
    int dirCost;            // 转弯次数的开销
    PathNode* father;       // 父节点

    PathNode() : cost(0), dir(-1), dirCost(0), father(NULL)
    {

    }
};

struct OpenListNode
{
    PathNode* pNode;
    int cost;

    OpenListNode(PathNode* node, int cs) : pNode(node), cost(cs)
    {

    }
};



const Point adjust[8] =
{
    {	1 * STEP,	0 * STEP	},
    {	0 * STEP,	-1 * STEP	},
    {	0 * STEP,	1 * STEP	},
    {	-1 * STEP,	0 * STEP	},
    {	1 * STEP,	-1 * STEP	},
    {	-1 * STEP,	-1 * STEP	},
    {	-1 * STEP,	1 * STEP	},
    {	1 * STEP,	1 * STEP	}
};

typedef std::list<OpenListNode> OPEN_LIST;

#endif