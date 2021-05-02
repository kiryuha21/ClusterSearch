#include "../include/Dbscan.h"

Dbscan::Dbscan(field& field) : field_for_search(field.get_cloud_arr()) { }

void Dbscan::find(double EPS, const int cluster_min_size) {
    bool unchecked_points_exist = true;
    while (unchecked_points_exist) {
        for (point& i : field_for_search) {
            unchecked_points_exist = false;
            if (i.get_label() == 0) {
                unchecked_points_exist = true;
                find_neighbours(i, EPS);
                if (points_queue.empty()) {
                    i.set_label(-1);
                } else {
                    while (!points_queue.empty()) {
                        point temp = points_queue.front();
                        points_queue.pop();
                        find_neighbours(temp, EPS);
                    }
                    write_to_final_field(cluster_min_size);
                }
            }
        }
    }
}

void Dbscan::write_to_final_field(int cluster_min_size) {
    size_t count = 0;
    for (point& j : field_for_search) {
        if (j.get_label() == 2) {
            ++count;
        }
        if (count == cluster_min_size) {
            for (point& i : field_for_search) {
                if (i.get_label() == 2) {
                    i.set_label(label_for_marking);
                    final_field.push_back(i);
                }
            }
            ++label_for_marking;
            break;
        }
    }
    if (count < cluster_min_size) {
        for (point& i : field_for_search) {
            if (i.get_label() == 2) {
                i.set_label(-1);
            }
        }
    }
}

void Dbscan::find_neighbours(point& start_point, const double EPS) {
    for (point& i : field_for_search) {
        double distance = sqrt(pow(i.get_x() - start_point.get_x(), 2) + pow(i.get_y() - start_point.get_y(),2));
        if (distance < EPS) {
            if (distance == 0) {
                i.set_label(2);
            }
            if (i.get_label() == 0) {
                i.set_label(1);
                points_queue.push(i);
            }
        }
    }
}

vector<point>& Dbscan::get_final_field() {
    return final_field;
}