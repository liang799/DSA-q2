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
    string symbol;
    int vacancy;
    int leftover_vaccany; //intially same as vacancy
};

struct SpStudent {
    string name;
    double gpa;
    char choices[3];
    char allocated = '#';
    int allocatedChoice = 9999;
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
        asport.leftover_vaccany = actvac;

        //Test Output
        cout << asport.symbol;
        cout << asport.vacancy << endl;
        cout << asport.name<< endl;
        cout << "             " << endl;
        sports.push_back(asport);
    }
    read.close();


    // Don't believe me? I didnt say that
    /*
    vector<sport>::iterator it;
    for (it = sports.begin(); it != sports.end(); ++it) {
        cout << (*it).vacancy;
    }
    */
    read.open("student.txt");
    unsigned int lineNum = 1;
	SpStudent student;
    vector<SpStudent> students;
    vector<SpStudent>::iterator it;

    while (!read.eof()) {
		getline(read, student.name);
		cout << student.name << ", ";
		read >> student.gpa;
		cout << student.gpa << endl;
		getline(read, line); // getline is needed to remove the line
		read >> student.choices[0] >> student.choices[1] >> student.choices[2];
		getline(read, line);
		read >> student.win[0] >> student.win[1] >> student.win[1];
		getline(read, line);
        students.push_back(student);
    }
    read.close();

    for (it = students.begin(); it != students.end(); ++it)
        cout << (*it).name << endl;


    list <Sport> choice;
    list <Sport> ::iterator it2;

    
    return 0;
}


