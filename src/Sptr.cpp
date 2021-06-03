#include "../include/Sptr.h"

Sptr::Sptr(field &field) : field_for_search(field.get_cloud_copy()) { }

void Sptr::find(const double EPS, const size_t cluster_min_size) {
    for (point& i : field_for_search) {
        if (i.get_label() == 0) {
            i.set_label(1);
            find_cluster(i, EPS);  // recursive function to mark points from cluster with "1"
            bool is_cluster = check_amount() > cluster_min_size;
            mark_and_push(is_cluster);
        }
    }
}

void Sptr::find_cluster(const point &start_point, const double EPS) {
    double minimal_distance = numeric_limits<double>::max();
    size_t field_size = field_for_search.size();
    size_t index_of_minimum;
    for (size_t i = 0; i < field_size; ++i) {  // loop to find minimal distance between start point and any other point
        if (field_for_search[i].get_label() == 0) {
            double distance = sqrt(pow(field_for_search[i].get_x() - start_point.get_x(), 2) + pow(field_for_search[i].get_y() - start_point.get_y(), 2));
            if (distance < minimal_distance) {
                minimal_distance = distance;
                index_of_minimum = i;
            }
        }
    }
    if (minimal_distance < EPS) {
        field_for_search[index_of_minimum].set_label(1);  // if distance is less than EPS, point is being added to the temp cluster
        find_cluster(field_for_search[index_of_minimum], EPS);  // recursive function loop, now new found point is a start point
    }
}

void Sptr::mark_and_push(bool is_cluster) {
    if (is_cluster) {
        for (point& i : field_for_search) {
            if (i.get_label() == 1) {
                i.set_label(label_for_marking);
                final_field.push_back(i);
            }
        }
        ++label_for_marking;
    } else {
        for (point& i : field_for_search) {
            if (i.get_label() == 1) {
                i.set_label(-1);
            }
        }
    }
}

int Sptr::check_amount() {
    int count = 0;
    for (point& i : field_for_search) {
        if (i.get_label() == 1) {
            ++count;
        }
    }
    return count;
}

vector<point> & Sptr::get_final_field() {
    return final_field;
}
