// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;
#include "Sport.h"
#include "SpStudent.h"
#include "printResults.h"

int main()
{
    string studentFile, vacancyFile, line, numVac;
    char special, verbose;
    vector<Sport> sports;
    Sport asport;

    cout << "Reading files" << endl;
    cout << "---------------" << endl;
    cout << "Please enter a valid vacancy file:  ";
    cin >> vacancyFile;
    cout << "Please enter a valid student file:  ";
    cin >> studentFile;
    cout << "Verbose? (y/n)  ";
    cin >> verbose;

    ifstream read(vacancyFile);
	if(!read){
        cerr << "\nERROR: FILE NOT FOUND - Unable to read " << vacancyFile;
        cerr << "\nPlease place the file in the same directory as the exectuable.\n\n";
		return -1;
	}
    /*--------------------------------- Reading files ---------------------------------*/
    while (!read.eof()) {
        getline(read, line);
		line.erase( remove(line.begin(),line.end(),' '), line.end() ); //stripping whitespace
        numVac = line.substr(line.find( ":" )+1); 

        if (line.back() > 'A' && line.back() < 'Z') {
            special = numVac[0];
        } else {
			asport.name = line.substr(0, line.find( "(" ));
            asport.vacancy = stoi(numVac);
            asport.vacancy = asport.vacancy;
            asport.symbol = line.front();
            sports.push_back(asport);
        }
    }
    read.close();

    read.open(studentFile);
	if(!read){
        cerr << "ERROR: FILE NOT FOUND - Unable to read " << studentFile;
        cerr << "\nPlease place the file in the same directory as the exectuable.\n\n";
		return -1;
	}
    SpStudent aStudent;
    vector<SpStudent> stud;

    while (!read.eof()) {
        // Read aStudent name
        getline(read, aStudent.name);

        // Read gpa
        getline(read, line);
        aStudent.gpa = stod(line);

        // Read choices
        getline(read, line);
		line.erase( remove(line.begin(),line.end(),' '), line.end() );
        for (int i = 0; i != 3; ++i)
            aStudent.choices[i] = line[i];

        // Read winning record(s)
        getline(read, line);
		line.erase( remove(line.begin(),line.end(),' '), line.end() ); 
        for (int i = 0; i != 3; ++i) 
            aStudent.win[i] = line[i] - '0'; //converting to int

        stud.push_back(aStudent);
    }
    read.close();

    /*--------------------------------- Round 1 ---------------------------------*/
    vector<SpStudent>::iterator it;
    vector<Sport>::iterator i;
    vector<SpStudent> noWin; 
    vector<SpStudent> allocated;   
    vector<SpStudent> noAllocated; 

	// Prioritize students with winning record, if no winning record: noWin. If no vaccancy left: noAllocated
    for (it = stud.begin(); it != stud.end(); it++) {
        for (i = sports.begin(); i != sports.end(); i++){
            // Find the sport that is special set the steal attempts
            if ((*i).symbol == special && (*i).steal == 0)
                (*i).steal = 3;

            if ((*it).choices[0] == (*i).symbol) {
                if ((*i).vacancy > 0 && (*it).win[0] == true) {
                    // Check if special has been assgined any students
                    if ((*i).symbol == special && (*i).steal > 0)
                        (*i).steal--;
                    if ((*i).symbol == special && (*i).steal == 0)
                        (*i).steal = -1;

					(*it).allocated = (*i).symbol;
					(*i).vacancy--;
                    (*it).allocatedChoice = "Choice 1";
					allocated.push_back(*it);
                    break;
                } else if((*i).vacancy > 0 && (*it).win[0] == false) { 
                    noWin.push_back(*it); 
                    break;
                } else {
                    noAllocated.push_back(*it);
                    break;
                }
            } 
        }
    }
	sort(noWin.begin(), noWin.end(), SpStudent::compareGPA); //sort according to higher gpa

	// Prioritize students with higher gpa, if student still does not get choice, assign to noAllocated
    for (vector<SpStudent>::iterator itr = noWin.begin(); itr != noWin.end(); itr++) {
        for (i = sports.begin(); i != sports.end(); i++) {
            if ((*itr).choices[0] == (*i).symbol ) {
                if ((*i).vacancy > 0) { 
					(*itr).allocated = (*i).symbol;
					(*itr).allocatedChoice = "Choice 1";
					(*i).vacancy--;
                    allocated.push_back(*itr);
					break;
                } else {
					noAllocated.push_back(*itr);
					break;
                }
            }
        }
    }

    printResults(1, allocated, sports, verbose);
    
    /*-------------------------------- - Round 2 -------------------------------- - */
    // Iterators i & it are declared in Round 1
    vector<Sport>::iterator fin; //old iterator
    cout << "\n# Round 2" << endl;
    cout << "============================= " << endl;
    for (it = allocated.begin(); it != allocated.end(); it++) { 
        for (i = sports.begin(); i != sports.end(); i++) {
            
            // Check if special able to steal students and if special have vacancy
            if ((*i).symbol==special && (*i).steal>0 && (*i).vacancy>0) {
                for (int x = 1; x < 3; x++) { //Check all choices of each student 
                    if ((*it).choices[x]==special && (*it).win[x]==true) { //Check if choices have special and win record
                        for (fin = sports.begin(); (*it).allocated != (*fin).symbol && fin != sports.end(); fin++) {} //Find allocated sport location to increment back 
						cout << (*it).name << " " << (*it).gpa << " stolen from " << (*fin).name << " to " << (*i).name << endl;
                        (*it).allocatedChoice = "STOLEN";
						(*fin).vacancy++; //Increment old sport
						(*it).allocated = special;
						(*i).vacancy--; //Decrement special
						(*i).steal--; //Decrement no. of steal
						break;
                    }
                }
            }
        }
    }
    printResults(2, allocated, sports, verbose);

    /*--------------------------------- Round 3 ---------------------------------*/
    noWin.clear();
    // Iterators i & it are declared in Round 1
    vector<SpStudent> noAllocated2; //students who are not allocated  after round 3

    for (it = noAllocated.begin(); it != noAllocated.end(); it++) {
        for (i = sports.begin(); i != sports.end(); i++) {
            if ((*it).choices[1] == (*i).symbol) {
                if ((*i).vacancy > 0 && (*it).win[1] == true) {
                    (*it).allocated = (*i).symbol;
					(*it).allocatedChoice = "Choice 2";
                    (*i).vacancy--;
                    allocated.push_back(*it);
                    break;
                } else if ((*i).vacancy > 0 && (*it).win[1] == false) {
                    noWin.push_back(*it);
                    break;
                } else {
                    noAllocated2.push_back(*it);
                    break;
                }
            }
        }
    }
    sort(noWin.begin(), noWin.end(), SpStudent::compareGPA);

    // Students with no win so prioritize GPA
    for (vector<SpStudent>::iterator itr = noWin.begin(); itr != noWin.end(); itr++) {
        for (i = sports.begin(); i != sports.end(); i++) {
            if ((*itr).choices[1] == (*i).symbol) {
                if ((*i).vacancy > 0) {
                    (*itr).allocated = (*i).symbol;
					(*itr).allocatedChoice = "Choice 2";
                    (*i).vacancy--;
                    allocated.push_back(*itr);
                    break;
                } else {
                    noAllocated2.push_back(*it);
                    break;
                }
            }
        }
    }
    printResults(3, allocated, sports, verbose);

    /*--------------------------------- Round 4 ---------------------------------*/
    noWin.clear();
    noAllocated.clear();
    // Iterators i & it are declared in Round 1

    for (it = noAllocated2.begin(); it != noAllocated2.end(); it++) {
        for (i = sports.begin(); i != sports.end(); i++) {
            if ((*it).choices[2] == (*i).symbol) {
                if ((*i).vacancy > 0 && (*it).win[2] == true) {
                    (*it).allocated = (*i).symbol;
					(*it).allocatedChoice = "Choice 3";
                    (*i).vacancy--;
                    allocated.push_back(*it);
                    break;
                } else if((*i).vacancy > 0 && (*it).win[2] == false){
                    noWin.push_back(*it);
                    break;
                } else {
                    noAllocated.push_back(*it);
                    break;
                }
            }
        }
    }
    sort(noWin.begin(), noWin.end(), SpStudent::compareGPA);

    // Students with no win so prioritize GPA
    for (vector<SpStudent>::iterator itr = noWin.begin(); itr != noWin.end(); itr++) {
        for (i = sports.begin(); i != sports.end(); i++) {
            if ((*itr).choices[2] == (*i).symbol) {
                if ((*i).vacancy > 0) {
                    (*itr).allocated = (*i).symbol;
					(*itr).allocatedChoice = "Choice 3";
                    (*i).vacancy--;
                    allocated.push_back(*itr);
                    break;
                } else{
                    noAllocated.push_back(*itr);
                    break;
                }
            }
        }
    }
    printResults(4, allocated, sports, verbose);

    /*--------------------------------- Final Round ---------------------------------*/
	default_random_engine generator;
    uniform_int_distribution<int> random_sport(0, sports.size()-1);

    for (it = noAllocated.begin(); it != noAllocated.end(); it++) {
        while ((*it).allocatedChoice == "Not allocated") {
			i = sports.begin() + random_sport(generator);
			if ((*i).vacancy > 0) {
				(*it).allocated = (*i).symbol;
				(*i).vacancy--;
                (*it).allocatedChoice = "Random";
				allocated.push_back(*it);
			}
        }
    }
    printResults(5, allocated, sports, verbose);

    ofstream fout("results.csv");
    fout << "Student, GPA, Allocation, Sport" << endl;
	for (vector<SpStudent>::iterator it = allocated.begin(); it != allocated.end(); it++)
        fout << (*it).name << ", " << (*it).gpa << ", " << (*it).allocatedChoice << ", " << (*it).allocated << endl;
    fout.close();
    
    cout << "\nNOTE: " << endl;
    cout << "Results outputed to results.csv" << endl;

    return 0;
}
