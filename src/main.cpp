#include "/home/kiryuha21/CLionProjects/clusters/include/user_interface.h"

int main() {
    user_interface iface;
    string action;
    cout << "Enter way of creating field [manually / file]\n";
    cin >> action;
    while (action != "manually" and action != "file") {
        cout << "Enter correct way of creating field [manually / file]\n";
        cin >> action;
    }
    if (action == "manually") {
        iface.create_field();
    } else {
        cout << "Enter file's name\n";
        string file_name;
        cin >> file_name;
        cout << "*beginning of a work with field*";
        try {
            iface.create_field(file_name);
        }
        catch (const int& ex) {
            cout << "File open error\n";
            return OPEN_ERR;
        }
    }
    iface.find(1);
    cout << "end of the programm\n";
    return 0;
}
