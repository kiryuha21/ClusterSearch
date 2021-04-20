#include "Dbscan.h"

Dbscan::Dbscan(field field) : field_for_search(move(field)) { }

void Dbscan::find(const double EPS) {
    bool unchecked_points_exist = true;
    vector<point> field_arr = this->field_for_search.get_cloud_arr();
    while (unchecked_points_exist) {
        for (point& i : field_arr) {
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
                    for (point& j : field_arr) {
                        if (j.get_label() == 3) {
                            j.set_label(label_for_marking);
                        }
                    }
                    ++label_for_marking;
                }
            }
        }
    }
}

void Dbscan::find_neighbours(point &start_point, const double EPS) {
    start_point.set_label(3);
    vector<point> temp_cloud_arr = field_for_search.get_cloud_arr();
    for (point i : temp_cloud_arr) {
        if (sqrt(pow(i.get_x() - start_point.get_x(), 2) + pow(i.get_y() - start_point.get_y(),2)) < EPS) {
            if (i.get_label() == 0) {
                i.set_label(2);
                points_queue.push(i);
            }
        }
    }
}