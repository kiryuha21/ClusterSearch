#pragma once

#include "field.h"

class Dbscan {
private:
    set<int> label_set;
    vector<point> field_for_search;
    vector<point> final_field;
    queue<point> points_queue;
    int label_for_marking = 5;
    void find_neighbours(point& start_point, double EPS);
    void destroy_little_clusters(int cluster_min_size);
public:
    Dbscan() = default;

    void assign_field(field& field);

    explicit Dbscan(field& field);

    void find(double EPS, int cluster_min_size);

    void show_final_field();
};

