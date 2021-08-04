#pragma once
#include <string>
using std::string;

struct SpStudent {
    string name;
    double gpa;
    char choices[3];
    char allocated = '#';
    int allocatedChoice = 999;
    bool win[3];
    bool compareGPA(SpStudent);
    bool stolen = 0;
};
