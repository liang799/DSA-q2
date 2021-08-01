// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
// DSA-q2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// I suggest that we move all these to a seperate file:
class Sport {
public:
    string name; //Do we need this? We have to say which student gets which sport. I would suggest that we create a vector instead of string to store the names. For future cases similar 
    // this, please open an issue on github
    string symbol;
    int vacancy;
};

struct SpStudent {
    string name;
    double gpa;
    char choices[3];
    bool win[3];
};

int main()
{
    ifstream read("vac.txt");
    string line; //to hold one row of string from vac file
    string bracket = "(";
    string name;
   
    char letter, vac;
    int actvac=0, i = 0;
    vector<Sport> sports;
	Sport asport;

    //read vacancy file
    while (!read.eof()) {

        getline(read, line); //Copy read to line

        int find = line.find(bracket);
        name = line.substr(0, find); //Find the name of the sport and assing to name
      
        letter = line.front(); //Get symbol
        vac = line.back(); //Get vacancy
        actvac = vac - '0'; //Convert vacancy from char to int, the ASCII values of the characters are subtracted from each other
        
        asport.name = name;
        asport.symbol = letter; 
        asport.vacancy = actvac;
        

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
    }
    read.close();

    
    return 0;
}


