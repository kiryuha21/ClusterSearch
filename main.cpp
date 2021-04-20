#include "user_interface.h"

int main() {
    user_interface iface;
    try {
        iface.create_field("main_output.txt");
    }
    catch (const int& ex) {
        cout << "File open error\n";
        return OPEN_ERR;
    }
    iface.find(1);
    return 0;
}
