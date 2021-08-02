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
        read >> aStudent.win[0] >> aStudent.win[1] >> aStudent.win[2];
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
                break;
            }
            else
                i++;
        }

            it++;
    }
    it = stud.begin();
    i = sports.begin();
    cout << " Round 1 Output " << endl;
    cout << "================== " << endl;
    for (it = stud.begin(); it != stud.end(); it++)
    {
        cout <<(*it).name<<" = "<<(*it).allocated << endl;
    }
    cout << "================== " << endl;
    cout << " Leftover Vacancy " << endl;
    for (i = sports.begin(); i != sports.end(); i++)
    {
        cout << (*i).leftover_vacancy << endl;
    }

    it = stud.begin();
    i = sports.begin(); //reset
    
    //Round 2 test
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

    it = stud.begin();
    i = sports.begin(); //reset

    cout << " Round 2 Output " << endl;
    cout << "================== " << endl;
    for (it = stud.begin(); it != stud.end(); it++)
    {

        cout << (*it).name << " = " << (*it).allocated << " " << endl;
    }
    cout <<"================== "<< endl;
    cout << " Leftover Vacancy " << endl;
    for(i=sports.begin();i!=sports.end();i++)
    {
        cout << (*i).leftover_vacancy << endl;
    }

    return 0;
}


