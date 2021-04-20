#pragma once

#include "field.h"
#include "Dbscan.h"

#define OPEN_ERR (-2)

class user_interface
{
private:
    field main_field;
    const set <int> numbers_set = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 46 };
public:
    int enter_alg_name();
    bool correct_positive_num_value(string value);
    void cloud_actions(cloud & cloud);
    void create_field_manually();
    void create_field(string filename = "");
};

