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
    string name;
    string symbol;
    int vacancy;
    
};

int main()
{
    Sport asport;
    ifstream read;
    string line; //to hold one row of string from vac file
    read.open("vac.txt");
   
    char letter, vac;
    int actvac=0, i = 0;

    //read vacancy file
 
    while (read) 
    {
        getline(read, line);
        letter = line.front();
        vac = line.back();
        actvac = vac - '0'; //Convert space from char to int, the ASCII values of the characters are subtracted from each other
        
        asport.symbol = letter;
        asport.vacancy = actvac;

        cout << asport.symbol;
        cout << asport.vacancy << endl;

    }
    read.close();
    
    return 0;
}


