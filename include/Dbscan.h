#pragma once

#include "field.h"
#include <queue>
#include <utility>

class Dbscan {
private:
    vector<point> field_for_search;
    queue<point> points_queue;
    void find_neighbours(point& start_point, double EPS);
    int label_for_marking = 5;
public:
    Dbscan() = default;

    void assign_field(field& field);

    explicit Dbscan(field& field);

    void find(double EPS);
};

