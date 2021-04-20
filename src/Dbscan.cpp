#include "../include/Dbscan.h"

Dbscan::Dbscan(field& field) : field_for_search(field.get_cloud_arr()) { }

void Dbscan::assign_field(field &field) {
    this->field_for_search = field.get_cloud_arr();
}

void Dbscan::find(double EPS, const size_t cluster_min_size) {
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
                    for (point& j : field_for_search) {
                        if (j.get_label() == 2) {
                            j.set_label(label_for_marking);
                        }
                    }
                    label_set.insert(label_for_marking);
                    ++label_for_marking;
                }
            }
        }
    }
    destroy_little_clusters(cluster_min_size);
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

void Dbscan::destroy_little_clusters(const int cluster_min_size) {
    for (int i : label_set) {
        size_t count = 0;
        for (const point& j : field_for_search) {
            if (j.get_label() == i) {
                ++count;
            }
            if (count == cluster_min_size) {
                for (const point& k : field_for_search) {
                    if (k.get_label() == i) {
                        final_field.push_back(k);
                    }
                }
                break;
            }
        }
    }
}

void Dbscan::show_final_field() {
    for (const point& i : final_field) {
        cout << i.get_x() << "\t" << i.get_y() << "\t" << i.get_label() << endl;
    }
}