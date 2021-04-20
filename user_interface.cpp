#include "user_interface.h"

int user_interface::enter_alg_name() {
    string input;
    while (true) {
        cout << "Введите цифру для выбора алгоритма:\n1 - Forel\n2 - Sptr\n3- Dbscan";
        cin >> input;
        int alg_num = stoi(input);
        if (alg_num != 1 and alg_num != 2 and alg_num != 3 and input.size() != 1) {
            cout << "Некорректный ввод, введите верное число";
        }
        else {
            return alg_num;
        }
    }
}

bool user_interface::correct_positive_num_value(string value) {
    for (size_t i = 0; i < value.size(); ++i) {
        if (numbers_set.find(value[i]) == numbers_set.end()) {
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
    int action_num = -1;
    while (true) {
        cout << "enter new action\n";
        cin >> input;
        action_num = stoi(input);
        if (action_num < 1 or action_num > 7 or input.size() != 1 or (cloud_not_exist and action_num != 1 and action_num != 7)) {
            cout << "Incorrect input, enter correct value\n";
            continue;
        }
        if (action_num == 7) {
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
                        correct_values = correct_positive_num_value(points_count_s);
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
                        correct_values = correct_positive_num_value(x_start_s);
                    }
                    x_start = stod(x_start_s);

                    cout << "Enter x end\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> x_end_s;
                        correct_values = correct_positive_num_value(x_end_s);
                    }
                    x_end = stod(x_end_s);

                    cout << "Enter y start\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> y_start_s;
                        correct_values = correct_positive_num_value(y_start_s);
                    }
                    y_start = stod(y_start_s);

                    cout << "Enter y end\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> y_end_s;
                        correct_values = correct_positive_num_value(y_end_s);
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
                        correct_values = correct_positive_num_value(dx_s);
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
                        correct_values = correct_positive_num_value(dy_s);
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
                        correct_values = correct_positive_num_value(angle_s);
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
                        correct_values = correct_positive_num_value(angle_s);
                    }
                    angle = stod(angle_s);
                    cloud.angle_start_point_turn(angle);
                    break;
                }
                case 6: {
                    cout << action_list;
                    break;
                }
                case 7: {
                    cout << "end of work with cloud";
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
            break;
        }
        switch (action_num) {
            case 1: {
                cloud new_cloud;
                cloud_actions(new_cloud);
                main_field.add_cloud(new_cloud);
                break;
            }
            case 2: {
                cout << "end of cloud input";
                break;
            }
        }
        cout << "enter new action\n";
    }
}

void user_interface::create_field(const string filename) {
    if (filename != "") {
        ifstream fs(filename);
        if (!fs.is_open()) {
            throw OPEN_ERR;
        }
        main_field.read_from_file(fs);
        fs.close();
    }
    else {
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
            cout << "Enter file's name\n";
            string output_file;
            cin >> output_file;
            ofstream fs(output_file);
            if (!fs.is_open()) {
                throw OPEN_ERR;
            }
            this->main_field.write_to_file(fs);
            cout << "field successfully wrote to file\n";
            fs.close();
        }
        else if (output_choice == "3") {
            cout << instruction;
        }
        else if (output_choice == "-1") {
            cout << "work with field finished\n";
            break;
        }
        else {
            cout << "incorrect input\n";
        }
        cout << "enter new action (enter 3 to see the instruction)\n";
    }
}

void user_interface::find(const double EPS) {
    int choice = enter_alg_name();
    switch (choice) {
        case 3: {
            dbscan_find.assign_field(main_field);
            dbscan_find.find(EPS);
            break;
        }
        default: {
            cout << "incorrect value or not realized";
            break;
        }
    }

}
