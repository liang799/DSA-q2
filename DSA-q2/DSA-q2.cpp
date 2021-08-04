// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;
#include "sport.h"
#include "SpStudent.h"

void printResults(int round, vector<SpStudent> students, vector<Sport> sports)
{
    cout << " Round "<< round <<" Output " << endl;
    cout << "================== " << endl;
    for (vector<SpStudent>::iterator it = students.begin(); it != students.end(); it++)
        cout <<(*it).name<<" = "<<(*it).allocated << endl;
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
    vector<Sport>::iterator i=sports.begin();
    vector<SpStudent> noWinning; // first choice but no winning record
    for (it=stud.begin(); it != stud.end(); it++)
    {  
        i = sports.begin();
        while (i != sports.end())
        {
            //find the sport that is special set the steal attempts
            if ((*i).symbol == special)
                (*i).steal = 3;

            //prioritize students with winning record
            if ((*it).choices[0] == (*i).symbol && (*i).leftover_vacancy > 0 )
            {
                if ((*it).win[0] == true) {
                    (*it).allocated = (*i).symbol;
                    (*i).leftover_vacancy--;
                    break;
                }
                else {
                    noWinning.push_back(*it); //add to list
                    break;
                }
            } 
            else
                i++;
        }
    }
    // list of people with first choice, but no winning record
    // gpa and sports choice are all over the place.



    
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

    return 0;
}


