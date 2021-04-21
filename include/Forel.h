#pragma once

#include "field.h"

class Forel {
private:
    vector<point> field_for_search;
    vector<point> final_field;
    set<int> last_neighbours_indexes;
    set<int> cluster_indexes;
    int label_for_marking = 5;
    int find_neighbours_count(const point& start_point, double EPS);
    void find_cluster(double EPS);
    void write_and_erase_cluster(size_t cluster_min_size);
public:
    Forel() = default;

    explicit Forel(field& field);

    void find(double EPS, size_t cluster_min_size);

    vector<point>& get_final_field();
};
