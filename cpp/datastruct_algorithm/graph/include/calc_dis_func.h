
#ifndef __CALC_DIS_FUNC_H__
#define __CALC_DIS_FUNC_H__

#include <cmath>
#include <algorithm>
#include "graph_data_type.h"

int manhattan(const Point& p1, const Point& p2)
{
    return std::max(abs(p1.x - p2.x), abs(p1.y - p2.y)) * STRAGHT_COST;
}

int euclidian(const Point& p1, const Point& p2)
{
    int dx = abs(p1.x - p2.x);
    int dy = abs(p1.y - p2.y);
    return sqrt((dx * dx) + (dy * dy)) * STRAGHT_COST;
}

int heuristic(const Point& p1, const Point& p2)
{
    int dx = abs(p1.x - p2.x);
    int dy = abs(p1.y - p2.y);
    return sqrt(dx * dx + dy * dy) * D_COST;
}


// int diagonal(const Point& p1, const Point& p2)
// {
//     int dx = abs(p1.x - p2.x);
//     int dy = abs(p1.y - p2.y);
//     int diag = std::min(dx, dy);
//     int straight = dx + dy;
//     return diag * STRAGHT_COST + (str)
// }

typedef int (*calc_cost_func)(const Point& p1, const Point& p2);
    

#endif