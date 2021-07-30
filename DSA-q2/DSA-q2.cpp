// DSA Mini Project by Tian Pok, Harith, Lokesh. Topic 2
// DSA-q2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream read;
    string line;
    read.open("vac.txt");
    
    //read vacancy file
    while (read) {
        getline(read, line);
        cout << line << endl;
    }
    read.close();

    return 0;
}


