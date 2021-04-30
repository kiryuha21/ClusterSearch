#include "../include/Sptr.h"

Sptr::Sptr(field &field) : field_for_search(field.get_cloud_arr()) { }

void Sptr::find(const double EPS, const size_t cluster_min_size) {
    for (point& i : field_for_search) {
        if (i.get_label() == 0) {
            temp_cluster.push_back(i);
            find_cluster(i, EPS);
            if (temp_cluster.size() > cluster_min_size) {
                mark_cluster(temp_cluster);
                final_field.insert(final_field.end(), temp_cluster.begin(), temp_cluster.end());
                ++label_for_marking;
            }
            temp_cluster.clear();
        }
    }
}

void Sptr::find_cluster(const point &start_point, const double EPS) {
    double minimal_distance = numeric_limits<double>::max();
    size_t field_size = field_for_search.size();
    size_t index_of_minimum;
    for (size_t i = 0; i < field_size; ++i) {
        double distance = sqrt(pow(field_for_search[i].get_x() - start_point.get_x(), 2) + pow(field_for_search[i].get_y() - start_point.get_y(),2));
        if (distance < minimal_distance && distance != 0 && field_for_search[i].get_label() == 0) {
            minimal_distance = distance;
            index_of_minimum = i;
        }
    }
     if (minimal_distance < EPS) {
         field_for_search[index_of_minimum].set_label(1);
         temp_cluster.push_back(field_for_search[index_of_minimum]);
         find_cluster(field_for_search[index_of_minimum], EPS);
    }
}

void Sptr::mark_cluster(vector<point> &cluster) const {
    for (point& i : cluster) {
        i.set_label(label_for_marking);
    }
}

vector<point> & Sptr::get_final_field() {
    return final_field;
}