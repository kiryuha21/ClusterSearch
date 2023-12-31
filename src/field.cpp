#include "../include/field.h"

field::field()
{
    cloud_arr.resize(0);
}

void field::add_cloud(cloud& to_add) {
    vector<point> temp = to_add.get_cloud();
    cloud_arr.reserve(cloud_arr.size() + temp.size());
    cloud_arr.insert(cloud_arr.end(), temp.begin(), temp.end());
}

void field::show_field() {
    for (size_t i = 0; i < cloud_arr.size(); ++i) {
        cout << i + 1 << "\t" << cloud_arr[i].get_x() << "\t\t" << cloud_arr[i].get_y() << "\t\t" << cloud_arr[i].get_label() << endl;
    }
    if (cloud_arr.empty()) {
        cout << "empty field\n";
    }
}

vector<point>& field::get_cloud_arr() {
    return cloud_arr;
}

vector<point> field::get_cloud_copy() {
    return cloud_arr;
}

void field::set_label(const int label) {
    for (point& i : cloud_arr) {
        i.set_label(label);
    }
    //transform(cloud_arr.begin(), cloud_arr.end(), cloud_arr.begin(), [label](point& i) { i.set_label(label); });
}

void field::read_from_file(ifstream& fs) {
    vector <point> temp;
    double x, y;
    int label;
    while (!fs.eof()) {
        fs >> x >> y >> label;
        temp.emplace_back(x, y, label);
    }
    field temp_field;
    this->cloud_arr = temp;
}

void field::write_to_file(ofstream& fs) {
    size_t cloud_arr_size = cloud_arr.size();
    for (size_t i = 0; i < cloud_arr_size - 1; ++i) {
        fs << cloud_arr[i].get_x() << " " << cloud_arr[i].get_y() << " " << cloud_arr[i].get_label() << endl;
    }
    fs << cloud_arr[cloud_arr_size - 1].get_x() << " " << cloud_arr[cloud_arr_size - 1].get_y() << " " << cloud_arr[cloud_arr_size - 1].get_label();
}
