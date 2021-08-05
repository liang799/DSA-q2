// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "sport.h"
#include "SpStudent.h"

void printResults(int round, vector<SpStudent> winners, vector<SpStudent> nowin, vector<Sport> sports)
{
    cout << "\n Round "<< round <<" Output " << endl;
    cout << "================== " << endl;
    vector<SpStudent>::iterator itr;
    for (vector<SpStudent>::iterator it = winners.begin(); it != winners.end(); it++)
		cout << (*it).name << " = " << (*it).allocated << endl;
	for (vector<SpStudent>::iterator itr = nowin.begin(); itr != nowin.end(); itr++)
		cout << (*itr).name << " = " << (*itr).allocated << endl;
	cout << "================== " << endl;
	cout << " Leftover Vacancy " << endl;
	for (vector<Sport>::iterator i = sports.begin(); i != sports.end(); i++)
		cout << (*i).leftover_vacancy << endl;
}

int main()
{
    ifstream read("vac.txt");
    string line; //to hold one row of string from vac file
    //string name;

    char letter, vac;
    int actvac = 0;
    vector<Sport> sports;
    Sport asport;
    char special;

    //read vacancy file
    while (!read.eof()) {
        getline(read, line); //Copy read to line

        //int find = line.find( "(" ); // I suggest we remove this line as special don't have "("
        //name = line.substr(0, find); //Find the name of the sport and assign to string variable name

        letter = line.front(); //Get symbol
        vac = line.back(); //Get vacancy
        if (line.back() > 'A' && line.back() < 'Z') {
            special = letter;
        } else {
            actvac = vac - '0'; //Convert vacancy from char to int, the ASCII values of the characters are subtracted from each other

            //asport.name = name;
            asport.symbol = letter;
            asport.vacancy = actvac;
            asport.leftover_vacancy = actvac;

            sports.push_back(asport);
        }
    }
    read.close();

    read.open("student.txt");
    unsigned int lineNum = 1;
    SpStudent aStudent;
    vector<SpStudent> stud;

    while (!read.eof()) {
        getline(read, aStudent.name);
        read >> aStudent.gpa;
        getline(read, line); // getline is needed to remove the line
        read >> aStudent.choices[0] >> aStudent.choices[1] >> aStudent.choices[2];
        getline(read, line);
        read >> aStudent.win[0] >> aStudent.win[1] >> aStudent.win[2];
        getline(read, line);
        stud.push_back(aStudent);
    }
    read.close();

    /* -------------------Round 1 ----------------------------------*/
    vector<SpStudent>::iterator it;
    vector<Sport>::iterator i;
    vector<SpStudent> noWinning; // first choice but no winning record
    for (it = stud.begin(); it != stud.end(); it++) {
        i = sports.begin();

        for (i = sports.begin(); i != sports.end(); i++){
            //find the sport that is special set the steal attempts
            if ((*i).symbol == special)
                (*i).steal = 3;

            //prioritize students with winning record
            if ((*it).choices[0] == (*i).symbol && (*i).leftover_vacancy > 0) {
                if ((*it).win[0] == true) {
                    (*it).allocated = (*i).symbol;
                    (*i).leftover_vacancy--;
                    break;
                } else {
                    noWinning.push_back(*it); //add to vector
                    break;
                }
            }
        }
    }

    // removing all the non winners
    vector<SpStudent> winner = stud;   // first choice with winning
    int tmp;
    for (it = stud.begin(), tmp = 0; it != stud.end(); it++, tmp++) {
        i = sports.begin();
        for (i = sports.begin(); i != sports.end(); i++) {
            if ( (*it).win[0] == 0 ) {
                winner.erase(winner.begin() + tmp);
                tmp--; // need to decrement as the size of winner got smaller by 1
                break;
            } else
                break;
        }
    }

    // vector of people with first choice, but no winning record
    // gpa and sports choice are all over the place.
    // sort according to gpa. the higher gpa go first, get choice
    // https://stackoverflow.com/questions/12787165/sort-vector-of-class-in-c
	sort(noWinning.begin(), noWinning.end(), SpStudent::compareGPA);

    // check results
    //for (vector<SpStudent>::iterator it = noWinning.begin(); it != noWinning.end(); it++)
        //cout << (*it).name << ", " << (*it).gpa << endl;

	i = sports.begin();
    for (vector<SpStudent>::iterator itr = noWinning.begin(); itr != noWinning.end(); itr++) {
        i = sports.begin();
        while (i != sports.end()) {
            //prioritize students with winning record
            if ((*itr).choices[0] == (*i).symbol && (*i).leftover_vacancy > 0 ) {
				(*itr).allocated = (*i).symbol;
				(*i).leftover_vacancy--;
                break;
            } else
                i++;
        }
    }

    printResults(1, winner, noWinning, sports);
    
    /* --------------Round 2---------------------------------*/
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


