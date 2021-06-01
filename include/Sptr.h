#pragma once

#include "field.h"
#include <limits>

class Sptr {
private:
    vector<point> field_for_search;
    vector<point> final_field;
    int label_for_marking = 5;
    void find_cluster(const point& start_point, double EPS);
    void mark_and_push(bool is_cluster);
    int check_amount();
public:
    Sptr() = default;

    explicit Sptr(field& field);

    void find(double EPS, size_t cluster_min_size);

    vector<point>& get_final_field();
};

