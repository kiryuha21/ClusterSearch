#pragma once

#include "field.h"

class Dbscan {
private:
    vector<point> field_for_search;
    vector<point> final_field;
    queue<point> points_queue;
    int label_for_marking = 5;
    void find_neighbours(point& start_point, double EPS);
    void write_to_final_field(int cluster_min_size);
public:
    Dbscan() = default;

    void assign_field(field& field);

    vector<point> get_final_field();

    explicit Dbscan(field& field);

    void find(double EPS, int cluster_min_size);

    void show_final_field();
};

