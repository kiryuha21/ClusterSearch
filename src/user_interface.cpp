#include "../include/user_interface.h"

int user_interface::enter_alg_name() {
    string input;
    cin >> input;
    while (input < "1" and input > "7") {
        cout << "Incorrect input, enter valid algorithm number";
        cin >> input;
    }
    return stoi(input);
}

bool user_interface::correct_positive_num_value(string value, bool can_be_negative) {
    if (!can_be_negative) {
        for (auto i : value) {
            if (numbers_set.find(i) == numbers_set.end()) {
                cout << "incorrect value, enter correct positive number\n";
                return false;
            }
        }
        return true;
    }
    for (size_t i = 0; i < value.size(); ++i) {
        if (numbers_set.find(value[i]) == numbers_set.end() && value[0] != '-') {
            cout << "incorrect value, enter correct positive number\n";
            return false;
        }
    }
    return true;
}

void user_interface::cloud_actions(cloud & cloud) {
    const string action_list = "enter number to perform action\n1- fill cloud\n2 - move all cloud points on x value\n3 - move all cloud points on y value\n4 - turn all points around cloud center on angle value\n5 - turn all cloud around coordinates center on angle value\n6 - print action list\n7 - end work with cloud\n";
    string input;
    cout << action_list;
    bool cloud_not_exist = cloud.is_empty();
    int action_num;
    while (true) {
        cout << "enter new action (enter 6 to see action list)\n";
        cin >> input;
        action_num = stoi(input);
        if (action_num < 1 or action_num > 7 or input.size() != 1 or (cloud_not_exist and action_num != 1 and action_num != 7)) {
            cout << "Incorrect input, enter correct value\n";
            continue;
        }
        if (action_num == 7) {
            cout << "end of work with cloud\n";
            break;
        }
        else {
            switch (action_num) {
                case 1: {
                    string points_count_s, x_start_s, x_end_s, y_end_s, y_start_s;
                    double x_start, x_end, y_start, y_end;
                    int points_count;
                    cout << "Enter points' amount\n";
                    bool correct_values = false;
                    while (!correct_values) {
                        cin >> points_count_s;
                        correct_values = correct_positive_num_value(points_count_s, false);
                        if (stoi(points_count_s) < 1 && correct_values) {
                            correct_values = false;
                            cout << "Incorrect input, enter correct value\n";
                        }
                    }
                    points_count = stoi(points_count_s);

                    cout << "Enter x start\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> x_start_s;
                        correct_values = correct_positive_num_value(x_start_s, true);
                    }
                    x_start = stod(x_start_s);

                    cout << "Enter x end\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> x_end_s;
                        correct_values = correct_positive_num_value(x_end_s, true);
                    }
                    x_end = stod(x_end_s);

                    cout << "Enter y start\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> y_start_s;
                        correct_values = correct_positive_num_value(y_start_s, true);
                    }
                    y_start = stod(y_start_s);

                    cout << "Enter y end\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> y_end_s;
                        correct_values = correct_positive_num_value(y_end_s, true);
                    }
                    y_end = stod(y_end_s);

                    cloud.fill_cloud(points_count, x_start, x_end, y_start, y_end);
                    cloud_not_exist = false;
                    break;
                }
                case 2: {
                    cout << "Enter x shift\n";
                    bool correct_values = false;
                    string dx_s;
                    double dx;
                    while (!correct_values) {
                        cin >> dx_s;
                        correct_values = correct_positive_num_value(dx_s, true);
                    }
                    dx = stod(dx_s);
                    cloud.move_x(dx);
                    break;
                }
                case 3: {
                    cout << "Enter y shift\n";
                    bool correct_values = false;
                    string dy_s;
                    double dy;
                    while (!correct_values) {
                        cin >> dy_s;
                        correct_values = correct_positive_num_value(dy_s, true);
                    }
                    dy = stod(dy_s);
                    cloud.move_y(dy);
                    break;
                }
                case 4: {
                    cout << "Enter angle value for rotation\n";
                    bool correct_values = false;
                    string angle_s;
                    double angle;
                    while (!correct_values) {
                        cin >> angle_s;
                        correct_values = correct_positive_num_value(angle_s, true);
                    }
                    angle = stod(angle_s);
                    cloud.angle_cloud_center_turn(angle);
                    break;
                }
                case 5: {
                    cout << "Enter angle value for rotation\n";
                    bool correct_values = false;
                    string angle_s;
                    double angle;
                    while (!correct_values) {
                        cin >> angle_s;
                        correct_values = correct_positive_num_value(angle_s, true);
                    }
                    angle = stod(angle_s);
                    cloud.angle_start_point_turn(angle);
                    break;
                }
                case 6: {
                    cout << action_list;
                    break;
                }
                default: {
                    cout << "this shouldn't happen...\n";
                    break;
                }
            }
        }
    }
}

void user_interface::create_field_manually() {
    int action_num;
    string input;
    const string action_input = "Enter 1 to create new cloud\nEnter 2 to end finishing clouds and create field\n";
    while (true) {
        cout << action_input;
        cin >> input;
        action_num = stoi(input);
        if (action_num < 1 or action_num > 2 or input.size() != 1) {
            cout << "Incorrect input, enter correct value\n";
            continue;
        }
        if (action_num == 2) {
            cout << "end of cloud input\n";
            break;
        }
        cloud new_cloud;
        cloud_actions(new_cloud);
        main_field.add_cloud(new_cloud);
        cout << "enter new action\n";
    }
}

void user_interface::write_down_main_field() {
    cout << "Enter file's name\n";
    string output_file;
    cin >> output_file;
    ofstream fs(output_file);
    fs.exceptions(std::ifstream::failbit);
    this->main_field.write_to_file(fs);
    cout << "field successfully wrote to file\n";
    fs.close();
}

void user_interface::create_field(const string& filename) {
    if (!filename.empty()) {
        try {
            ifstream fs(filename);
            fs.exceptions(std::ifstream::failbit);
            cout << "*beginning of a work with field*\n";
            main_field.read_from_file(fs);
            fs.close();
        }
        catch (ifstream::failure&) {
            throw ifstream::failure("problem while opening or reading file");
        }
    } else {
        create_field_manually();
    }
    cout << "field created\n";
    const string instruction = "Enter 1 to show field\nEnter 2 to write field to file\nEnter 3 to see the instruction\nEnter -1 to end work with field\n";
    cout << instruction;
    string output_choice;
    while (output_choice != "-1") {
        cin >> output_choice;
        if (output_choice == "1") {
            main_field.show_field();
        }
        else if (output_choice == "2") {
            write_down_main_field();
        }
        else if (output_choice == "3") {
            cout << instruction;
        }
        else if (output_choice == "-1") {
            cout << "*work with field finished*\n";
            break;
        }
        else {
            cout << "incorrect input\n";
        }
        cout << "enter new action (enter 3 to see the instruction)\n";
    }
}

void user_interface::enter_alg_variables(double& EPS, size_t& cluster_min_size) {
    cout << "enter EPS\n";
    string EPS_s;
    bool valid_input = false;
    while (!valid_input) {
        valid_input = true;
        cin >> EPS_s;
        try {
            EPS = stod(EPS_s);
        }
        catch (invalid_argument&) {
            cout << "invalid argument, try again\n";
            valid_input = false;
        }
    }
    cout << "enter minimum points' amount in cluster\n";
    string min_points_s;
    valid_input = false;
    while (!valid_input) {
        valid_input = true;
        cin >> min_points_s;
        try {
            cluster_min_size = stoi(min_points_s);
        }
        catch (invalid_argument&) {
            cout << "invalid argument, try again\n";
            valid_input = false;
        }
    }
}

void user_interface::find() {
    const string instruction = "Enter algorithm number:\n1 for Forel\n2 for SPtr\n3 for Dbscan\nAnother actions:\nEnter 4 to see the instruction\nEnter 5 to show final field\nEnter 6 to write field to plot file\nEnter 7 to finish finding clusters\n";
    cout << instruction;
    int choice = enter_alg_name();
    size_t cluster_min_size;
    double EPS;
    while (choice != 7) {
        switch (choice) {
            case 1: {
                main_field.set_label(0);
                enter_alg_variables(EPS, cluster_min_size);
                Forel forel_find(main_field);
                forel_find.find(EPS, cluster_min_size);
                found_clusters = forel_find.get_final_field();
                if (!found_clusters.empty()) {
                    cout << "clusters found!\n";
                } else {
                    cout << "there are no clusters found with given values\n";
                }
                break;
            }
            case 2: {
                enter_alg_variables(EPS, cluster_min_size);
                main_field.set_label(0);
                Sptr sptr_find(main_field);
                sptr_find.find(EPS, cluster_min_size);
                found_clusters = sptr_find.get_final_field();
                if (!found_clusters.empty()) {
                    cout << "clusters found!\n";
                } else {
                    cout << "there are no clusters found with given values\n";
                }
                break;
            }
            case 3: {
                enter_alg_variables(EPS, cluster_min_size);
                main_field.set_label(0);
                Dbscan dbscan_find(main_field);
                dbscan_find.find(EPS, cluster_min_size);
                found_clusters = dbscan_find.get_final_field();
                if (!found_clusters.empty()) {
                    cout << "clusters found!\n";
                } else {
                    cout << "there are no clusters found with given values\n";
                }
                break;
            }
            case 4: {
                cout << instruction;
                break;
            }
            case 5: {
                for (const point& i : found_clusters) {
                    cout << i.get_x() << "\t" << i.get_y() << "\t" << i.get_label() << endl;
                }
                break;
            }
            case 6 : {
                make_plot_file();
                break;
            }
            default: {
                cout << "incorrect value\n";
                break;
            }
        }
        cout << "Enter new action (enter 4 to see the instructions) \n";
        choice = enter_alg_name();
    }

}

void user_interface::make_plot_file() {
    if (found_clusters.empty()) {
        cout << "clusters haven't been found yet or there are no clusters found with given values\n";
        return;
    }
    int color_count = found_clusters[found_clusters.size() - 1].get_label();

    vector<int> colors(color_count - 4);
    srand(time(nullptr));
    for (int& i : colors) {
        i = abs(65536 * rand() + 256 * rand() + rand());
    }

    cout << "enter file's name to write points with colors\n";
    string filename;
    cin >> filename;
    ofstream fs(filename);
    fs.exceptions(std::ifstream::failbit);

    for (const point& i : found_clusters) {
        fs << i.get_x() << " " << i.get_y() << " " << colors[i.get_label() - 5] << endl;
    }
    fs.close();
}
