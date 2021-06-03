#include "../include/Forel.h"

Forel::Forel(field &field) : field_for_search(field.get_cloud_arr()) { }

void Forel::find(const double EPS, const size_t cluster_min_size) {
    while (!field_for_search.empty()) {
        narrowing_started = false;
        find_with_narrow(EPS);
        write_and_erase_cluster(cluster_min_size);
    }
}

void Forel::find_with_narrow(double EPS) {
    find_cluster(EPS);
    narrowing_started = true;
    point center;
    point new_center = find_mass_center();
    do {
        center = new_center;
        EPS *= 0.95;
        find_cluster(EPS);
        new_center = find_mass_center();
    } while (center != new_center);
}

void Forel::find_cluster(const double EPS) {
    int mass_center_neighbours = -1;
    for (point& i : field_for_search) {
        int neighbours_count = find_neighbours_count(i, EPS);
        if (neighbours_count > mass_center_neighbours) {
            mass_center_neighbours = neighbours_count;
            cluster_indexes = last_neighbours_indexes;
        }
    }
}

point Forel::find_mass_center() {
    point center;
    for (const auto& i : cluster_indexes) {
        center.add_x(field_for_search[i].get_x());
        center.add_y(field_for_search[i].get_y());
    }
    center.set_x(center.get_x() / (double)cluster_indexes.size());
    center.set_y(center.get_y() / (double)cluster_indexes.size());
    return center;
}

int Forel::find_neighbours_count(const point& start_point, const double EPS) {
    int count = 0;
    if (narrowing_started) {
        last_neighbours_indexes.clear();
        for (const int& i : cluster_indexes) {
            double distance = sqrt(pow(field_for_search[i].get_x() - start_point.get_x(), 2) + pow(field_for_search[i].get_y() - start_point.get_y(),2));
            if (distance < EPS) {
                ++count;
                last_neighbours_indexes.insert(i);
            }
        }
    } else {
        int field_size = field_for_search.size();
        last_neighbours_indexes.clear();
        for (int i = 0; i < field_size; ++i) {
            double distance = sqrt(pow(field_for_search[i].get_x() - start_point.get_x(), 2) + pow(field_for_search[i].get_y() - start_point.get_y(), 2));
            if (distance < EPS) {
                ++count;
                last_neighbours_indexes.insert(i);
            }
        }
    }
    return count - 1;
}

void Forel::write_and_erase_cluster(const size_t cluster_min_size) {
    int field_size = field_for_search.size();
    int delete_count = 0;
    bool correct_cluster_size = cluster_indexes.size() >= cluster_min_size;
    for (int i = 0; i < field_size; ++i) {
        if (cluster_indexes.find(i) != cluster_indexes.end()) {
            if (correct_cluster_size) {
                field_for_search[i - delete_count].set_label(label_for_marking);
                final_field.push_back(field_for_search[i - delete_count]);
            }
            field_for_search.erase(field_for_search.begin() + i - delete_count);
            ++delete_count;
        }
    }
    if (correct_cluster_size) {
        ++label_for_marking;
    }
    cluster_indexes.clear();
}

vector<point> & Forel::get_final_field() {
    return final_field;
}
