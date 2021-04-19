#include "cloud.h"

cloud::cloud() : x_center(0), y_center(0)  {//default constructor
    cloud_data.resize(0);
}

void cloud::set_label(int lb) {//group label
    for (point i : this->cloud_data) {
        i.set_label(lb);
    }
}

vector <double> cloud::create_norm(int number_of_points, double minval, double maxval) {//norm gisto
    vector <double> normal_array(number_of_points); // Create a vector of predefined size
    if (minval > maxval) {
        swap(minval, maxval);
    }
    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    default_random_engine e(seed);
    normal_distribution<> rng_machine((maxval - minval) / 2, (maxval - minval) / 12);
    for (int i = 0; i < number_of_points; ++i) {
        normal_array[i] = rng_machine(e);
    }
    return normal_array;
}

void cloud::fill_cloud(int points_count, double x_start, double x_end, double y_start, double y_end) {
    cloud_data.resize(points_count);
    this->x_center = (x_end - x_start) / 2;
    this->y_center = (y_end - y_start) / 2;
    vector <double> x_arr = create_norm(points_count, x_start, x_end);
    vector <double> y_arr = create_norm(points_count, y_start, y_end);
    for (int i = 0; i < points_count; ++i) {
        cloud_data[i].set_x(x_arr[i]);
        cloud_data[i].set_y(y_arr[i]);
        cloud_data[i].set_label(0);
    }
}

void cloud::move_x(double delta_x) {
    for (point i : cloud_data) {
        i.add_x(delta_x);
    }
}

void cloud::move_y(double delta_y) {
    for (point i : cloud_data) {
        i.add_y(delta_y);
    }
}

void cloud::angle_cloud_center_turn(double angle) {
    for (point i : cloud_data) {
        double new_x = x_center + cos(angle) * (i.get_x() - x_center) - sin(angle) * (i.get_y() - y_center);
        double new_y = y_center + sin(angle) * (i.get_x() - x_center) - cos(angle) * (i.get_y() - y_center);
        i.set_x(new_x);
        i.set_y(new_y);
    }
}

void cloud::angle_start_point_turn(double angle) {
    for (point i : cloud_data) {
        double new_x = cos(angle) * (i.get_x()) - sin(angle) * (i.get_y());
        double new_y = sin(angle) * (i.get_x()) - cos(angle) * (i.get_y());
        i.set_x(new_x);
        i.set_y(new_y);
    }
}

vector <point> cloud::get_cloud() {
    return cloud_data;
}

size_t cloud::get_cloud_data_size() {
    return this->cloud_data.size();
}

void cloud::show_cloud() {
    for (size_t i = 0; i < cloud_data.size(); ++i) {
        cout << i + 1 << "\t" << cloud_data[i].get_x() << "\t\t" << cloud_data[i].get_y() << "\t\t" << cloud_data[i].get_label() << endl;
    }
    if (cloud_data.empty()) {
        cout << "empty cloud\n";
    }
}

bool cloud::is_empty() {
    if (cloud_data.empty()) {
        return true;
    }
    return false;
}
