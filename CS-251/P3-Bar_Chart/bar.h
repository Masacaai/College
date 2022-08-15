/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains the Bar class used in barchart.h.
*/

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

// Bar
class Bar {
 private:
    // Private member variables
    string name, category;
    int value;

 public:

    // Parameterized constructor with default values
    Bar(string name = "", int value = 0, string category = "") {
        this->name = name;
        this->value = value;
        this->category = category;
    }

    // Accessor methods
    string getName()     {return name;}
    int getValue()       {return value;}
    string getCategory() {return category;}

    // Comparison operators
    bool operator<(const Bar &other) const  {return value < other.value;}
    bool operator<=(const Bar &other) const {return value <= other.value;}
    bool operator>(const Bar &other) const  {return value > other.value;}
    bool operator>=(const Bar &other) const {return value >= other.value;}
};

