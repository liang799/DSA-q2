// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
// DSA-q2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// I suggest that we move all these to a seperate file:
class Sport {
public:
    string name; // For future cases similar to this, please open an issue on github
    char symbol;
    int vacancy;
    int leftover_vacancy; //intially same as vacancy
};

struct SpStudent {
    string name;
    double gpa;
    char choices[3];
    char allocated = '#';
    int allocatedChoice = 999;
    bool win[3];
};

int main()
{
    ifstream read("vac.txt");
    string line; //to hold one row of string from vac file
    string bracket = "(";
    string name;
   
    char letter, vac;
    int actvac = 0;
    vector<Sport> sports;
	Sport asport;

    //read vacancy file
    while (!read.eof()) {

        getline(read, line); //Copy read to line

        int find = line.find(bracket);
        name = line.substr(0, find); //Find the name of the sport and assign to string variable name
      
        letter = line.front(); //Get symbol
        vac = line.back(); //Get vacancy
        actvac = vac - '0'; //Convert vacancy from char to int, the ASCII values of the characters are subtracted from each other
        
        asport.name = name;
        asport.symbol = letter; 
        asport.vacancy = actvac;
        asport.leftover_vacancy = actvac;

        sports.push_back(asport);
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
        read >> aStudent.win[0] >> aStudent.win[1] >> aStudent.win[1];
        getline(read, line);
        stud.push_back(aStudent);
    }
    read.close();

    vector<SpStudent>::iterator it=stud.begin(); //Round 1
    vector<Sport>::iterator i=sports.begin();

    while (it!=stud.end())
    {  
        i = sports.begin();
        while (i != sports.end())
        {
            if ((*it).choices[0] == (*i).symbol && (*i).leftover_vacancy > 0)
            {
                (*it).allocated = (*i).symbol;
                (*i).leftover_vacancy--;
            }
            else
                i++;
        }

            it++;
    }

    /*for (it = stud.begin(); it != stud.end(); ) {
        cout << (*it).name << endl;
        for (i = sports.begin(); i != sports.end();) {
            if ((*it).choices[0] == (*i).symbol) {
                if ((*i).leftover_vacancy > 0) {
                    (*it).allocated = (*i).symbol;
                    (*i).leftover_vacancy--;
                }
                else
                    i++;
            }
            else
                i++;
        }
    }
    */
    // test output
    for (it = stud.begin(); it != stud.end(); it++)
    {
        cout <<(*it).name<<" = "<<(*it).allocated << endl;
    }
    
    return 0;
}


