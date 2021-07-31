// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
// DSA-q2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

class Sport {
public:
    string name; //Do we need this? We have to say which student gets which sport
    string symbol;
    int vacancy;
    
};

int main()
{
    ifstream read;
    string line; //to hold one row of string from vac file
    read.open("vac.txt");
   
    char letter, vac;
    int actvac=0, i = 0;
    vector<Sport> sports;

    //read vacancy file
    while (!read.eof()) 
    {
        getline(read, line);
        letter = line.front();
        vac = line.back();
        actvac = vac - '0'; //Convert space from char to int, the ASCII values of the characters are subtracted from each other
        
        // Create an instance
		Sport asport;

        // Setter:
        asport.symbol = letter;
        asport.vacancy = actvac;

        //Test Output
        cout << asport.symbol;
        cout << asport.vacancy << endl;
        sports.push_back(asport);
    }
    read.close();


    // Don't believe me? I didnt say that
    vector<Sport>::iterator it;
    for (it = sports.begin(); it != sports.end(); ++it) {
        cout << (*it).vacancy;
    }
    
    return 0;
}


