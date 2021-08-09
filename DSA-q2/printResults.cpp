#include "printResults.h"
#include "Sport.h"
#include "SpStudent.h"
#include <vector>
#include <iostream>
using std::vector; using std::cout; using std::endl;

void printResults(int round, vector<SpStudent> allocated, vector<Sport> sports, char verbose)
{
    if (round == 2) {
        cout << "\nSummary " << endl;
        cout << "--------------------------";
    } else {
		cout << "\n # Round "<< round <<" Output " << endl;
        cout << "============================= ";
    }

	for (vector<Sport>::iterator itr = sports.begin(); itr != sports.end(); itr++) {
		cout << "\n## " << (*itr).name << endl;
		for (vector<SpStudent>::iterator it = allocated.begin(); it != allocated.end(); it++) {
            if ((*it).allocated == (*itr).symbol)
                cout << "    - " << (*it).name << " " << (*it).gpa << " " << (*it).allocatedChoice << endl;
        }
    }
    cout << "============================= " << endl;

    if (verbose == 'y') {
		cout << "\n# Debugging: " << endl;
		cout << "======================================" << endl;
		cout << "## Leftover Vacancy " << endl;
		for (vector<Sport>::iterator i = sports.begin(); i != sports.end(); i++)
			cout << "    " << (*i).symbol << ": " << (*i).vacancy << endl;
		cout << "\n## Steal attempts" << endl;
		for (vector<Sport>::iterator i = sports.begin(); i != sports.end(); i++) 
			cout << "    " << (*i).symbol << ": " << (*i).steal << endl;
		cout << "======================================" << endl;
    }
}
