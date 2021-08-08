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
    static bool compareGPA(const SpStudent& moi, const SpStudent& rival) {
		return (moi.gpa > rival.gpa);
    }
    bool stolen = 0;
    bool assigned = 0;
};
