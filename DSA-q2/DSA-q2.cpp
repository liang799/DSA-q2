// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "sport.h"
#include "SpStudent.h"

void printResults(int round, vector<SpStudent> allocated, vector<Sport> sports)
{
    cout << "\n Round "<< round <<" Output " << endl;
    cout << "================== " << endl;
    vector<SpStudent>::iterator itr;
    for (vector<SpStudent>::iterator it = allocated.begin(); it != allocated.end(); it++)
		cout << (*it).name << " = " << (*it).allocated << endl;
	cout << "================== " << endl;
	cout << " Leftover Vacancy " << endl;
	for (vector<Sport>::iterator i = sports.begin(); i != sports.end(); i++)
		cout << (*i).leftover_vacancy << endl;
}

int main()
{
    ifstream read("vac.txt");
    string line; //to hold one row of string from vac file

    char letter, vac;
    int actvac = 0;
    vector<Sport> sports;
    Sport asport;
    char special;

    // Read vacancy file
    while (!read.eof()) {
        getline(read, line); //copy read to line
		line.erase( remove(line.begin(),line.end(),' '), line.end() ); //stripping whitespace, oh yea, but has nothing to do with strippers
        letter = line.front(); //get symbol
        vac = line.back(); //get vacancy

        if (line.back() > 'A' && line.back() < 'Z') {
            special = letter;
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
    vector<Sport>::iterator i;
    vector<SpStudent> noWin; //students who do not have a winning record
    vector<SpStudent> allocated;   //students who are allocated a sport
    vector<SpStudent> noAllocated; //students who are not allocated
    for (it = stud.begin(); it != stud.end(); it++) {
        for (i = sports.begin(); i != sports.end(); i++){
            // Find the sport that is special set the steal attempts
            if ((*i).symbol == special)
                (*i).steal = 3;

            // Prioritize students with winning record
            if ((*it).choices[0] == (*i).symbol) {
                if ((*i).leftover_vacancy > 0 && (*it).win[0] == true) {
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

    // Sort according to higher gpa
	sort(noWin.begin(), noWin.end(), SpStudent::compareGPA);

    for (vector<SpStudent>::iterator itr = noWin.begin(); itr != noWin.end(); itr++) {
        for (i = sports.begin(); i != sports.end(); i++) {
            // Prioritize students with higher gpa 
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
    while (it != stud.end())
    {
        i = sports.begin();

        for (int x = 0; x < 3;) // Check all 3 sports competition
        {
            if ((*it).win[x] == 1) // Check if choices 1-3 is 1
            {
                while (i != sports.end())
                {

                    if ((*i).symbol == (*it).choices[x] && (*i).leftover_vacancy > 0) // To find the location of *i.symbol so that can decrement *i.leftover_vacancy
                    {

                        (*it).allocated = (*it).choices[x]; // Allocate new sport.
                        (*i).leftover_vacancy--; //Decrement new sport. Idk how to increment the old sport as need to find the location.
                        break;
                    }
                    else
                        i++;

                }
               
                break; 
            }
            else
                x++;



        }


        it++;
    }

    return 0;
}


