#pragma once
#include <string>
using std::string;

class Sport {
public:
    string name;     
    char symbol;
    int vacancy;
    int leftover_vacancy; //intially same as vacancy
    unsigned int steal = 0;
};
