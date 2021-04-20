#include "/home/kiryuha21/CLionProjects/clusters/include/field.h"

field::field()
{
    cloud_arr.resize(0);
}

void field::add_cloud(cloud& to_add) {
    vector<point> temp = to_add.get_cloud();
    cloud_arr.reserve(cloud_arr.size() + temp.size());
    for (const point& i : temp) {
        cloud_arr.push_back(i);
    }
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

void field::set_label(const int label) {
    for (point i : cloud_arr) {
        i.set_label(label);
    }
}

void field::read_from_file(ifstream& fs) {
    vector <point> temp;
    double x, y;
    int label;
    while (fs >> x >> y >> label) {
        point temp_point(x, y, label);
        temp.push_back(temp_point);
    }
    field temp_field;
    this->cloud_arr = temp;
}

void field::write_to_file(ofstream& fs) {
    for (point i : this->cloud_arr) {
        fs << i.get_x() << " " << i.get_y() << " " << i.get_label() << endl;
    }
}
