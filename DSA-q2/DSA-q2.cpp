// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "Sport.h"
#include "SpStudent.h"
#include "printResults.h"

int main()
{
    ifstream read("vac.txt");
    string line; //to hold one row of string from vac file
    char letter, vac;
    int actvac = 0;
    vector<Sport> sports;
    Sport asport;
    char special;

    /*--------------------------------- Reading files ---------------------------------*/
    while (!read.eof()) {
        getline(read, line); //copy read to line
		line.erase( remove(line.begin(),line.end(),' '), line.end() ); //stripping whitespace, oh yea, but has nothing to do with strippers
        letter = line.front(); //get symbol
        vac = line.back(); //get vacancy

        if (line.back() > 'A' && line.back() < 'Z') {
            special = vac;
        } else {
            actvac = vac - '0'; //convert vacancy from char to int, the ASCII values of the characters are subtracted from each other
			asport.name = line.substr(0, line.find( "(" )); //find the name of the sport and assign to string variable name
            asport.symbol = letter;
            asport.vacancy = actvac;
            asport.leftover_vacancy = actvac;
            sports.push_back(asport);
        }
    }
    read.close();

    read.open("student.txt");
    SpStudent aStudent;
    vector<SpStudent> stud;

    while (!read.eof()) {
        // Read aStudent name
        getline(read, aStudent.name);

        // Read gpa
        getline(read, line);
        aStudent.gpa = stod(line); //string to double

        // Read choices
        getline(read, line);
		line.erase( remove(line.begin(),line.end(),' '), line.end() ); //strip whitespace
        for (int i = 0; i != 3; ++i)
            aStudent.choices[i] = line[i];

        // Read winning record(s)
        getline(read, line);
		line.erase( remove(line.begin(),line.end(),' '), line.end() ); //strip whitespace
        for (int i = 0; i != 3; ++i) 
            aStudent.win[i] = line[i] - '0'; //convert char to int then assign

        stud.push_back(aStudent); //push object to vector
    }
    read.close();

    /*--------------------------------- Round 1 ---------------------------------*/
    vector<SpStudent>::iterator it;
    vector<SpStudent>::iterator find=stud.begin();
    vector<Sport>::iterator i;
    vector<Sport>::iterator fin=sports.begin();
    vector<SpStudent> noWin; //students who do not have a winning record
    vector<SpStudent> allocated;   //students who are allocated a sport
    vector<SpStudent> noAllocated; //students who are not allocated

	// Prioritize students with winning record, if no winning record: noWin. If no vaccancy left: noAllocated
    for (it = stud.begin(); it != stud.end(); it++) {
        for (i = sports.begin(); i != sports.end(); i++){
            // Find the sport that is special set the steal attempts
            if ((*i).symbol == special && (*i).steal == 0)
                (*i).steal = 3;

            if ((*it).choices[0] == (*i).symbol) {
                if ((*i).leftover_vacancy > 0 && (*it).win[0] == true) {
                    // Check if special has been assgined any students
                    if ((*i).symbol == special && (*i).steal > 0)
                        (*i).steal--;
                    if ((*i).symbol == special && (*i).steal == 0)
                        (*i).steal = -1;

					(*it).allocated = (*i).symbol;
					(*i).leftover_vacancy--;
					allocated.push_back(*it);
                    break;
                } else if((*i).leftover_vacancy > 0 && (*it).win[0] == false) {
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
                if ((*i).leftover_vacancy > 0) {
					(*itr).allocated = (*i).symbol;
					(*i).leftover_vacancy--;
				   allocated.push_back(*itr);
					break;
                } else {
					noAllocated.push_back(*itr);
					break;
                }
            }
        }
    }

    printResults(1, allocated, sports);
    
    /*--------------------------------- Round 2 ---------------------------------*/
    for (it = stud.begin(); it != stud.end(); it++) { //IMPORTANT: pleaase use allocated vector instead of stud
        for (i = sports.begin(); i != sports.end(); i++) {
            
            // Check if special able to steal students and if special have vacancy
            if ((*i).symbol==special && (*i).steal>0 && (*i).vacancy>0) {
              
                for (int x = 0; x < 3;x++) { //Check all choices of each student 
                    if ((*it).choices[x]==special && (*it).win[x]==true) { //Check if choices have special and win record
                        for (fin = sports.begin(); (*it).allocated != (*fin).symbol && fin !=sports.end(); ) //Find allocated sport location to increment back 
                        {
                            fin++;
                            cout << "gay" << endl;
                        }
                        (*fin).leftover_vacancy++;

                            (*it).allocated = special;
                            (*i).leftover_vacancy--;
                            (*i).steal--;
                            allocated.push_back(*it);
                            break;
                        
                    }
                    
                    
                }
            }
        }
    }
    printResults(2, allocated, sports);
    return 0;
}
