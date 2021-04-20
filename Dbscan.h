#pragma once

#include "field.h"
#include <queue>
#include <utility>

class Dbscan {
private:
    field field_for_search;
    queue<point> points_queue;
    void find_neighbours(point& start_point, const double EPS);
    int label_for_marking = 5;
public:
    Dbscan(field field);

    void find(const double EPS);
};

