/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains the BarChart class used in barchartanimate.h.
*/

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h"  // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RESET("\033[0m");

// Color codes for Mimir (light mode)
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Codio (light/dark mode)
// const string CYAN("\033[1;36m");
// const string GREEN("\033[1;32m");
// const string GOLD("\033[1;33m");
// const string RED("\033[1;31m");
// const string PURPLE("\033[1;35m");
// const string BLUE("\033[1;34m");
// const string WHITE("\033[1;37m");
// const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

// BarChart
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars. It keeps track of the number of elements stored (size) and the
    // capacity of the array (capacity). This is not a dynamic array, so it
    // does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    string frame;
    int capacity;
    int size;

 public:
    // default constructor:
    BarChart() {
        bars = nullptr;
        frame = "";
        capacity = 0;
        size = 0; 
    }

    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
        bars = new Bar[n];
        frame = "";
        capacity = n;
        size = 0;
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
        this->bars = new Bar[other.capacity];
        this->frame = other.frame;
        this->capacity = other.capacity;
        this->size = other.size;

        for (int i = 0; i < other.size; ++i) {
            this->bars[i] = other.bars[i];
        }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {

        if (this == &other) {
            return *this;
        }

        delete[] bars;

        this->bars = new Bar[other.capacity];
        this->frame = other.frame;
        this->capacity = other.capacity;
        this->size = other.size;

        for (int i = 0; i < other.size; ++i) {
            this->bars[i] = other.bars[i];
        }
        return *this;
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
        if (bars != nullptr) {
            delete[] bars;
        }
        bars = nullptr;
        frame = "";
        size = 0;
        capacity = 0;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
        if (bars != nullptr) {
            delete[] bars;
        }
    }

    // setFrame
    void setFrame(string frame) {this->frame = frame;}

    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {return frame;}

    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) {
        if (size == capacity) {
            return false;
        }
        Bar temp(name, value, category);

        // Insert temp into position
        bars[size] = temp;
        size++;
        return true;
    }

    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {return size;}

    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {

        if (i < 0 || i >= size) {
            throw out_of_range("BarChart: i out of bounds");
        }
        return bars[i];
    }

    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
        sort(bars, bars + size, greater<Bar>());
        output << "frame: " << frame << endl;
        for (int i = 0; i < size; ++i) {
            output << bars[i].getName() << " " << bars[i].getValue() << " " << bars[i].getCategory() << endl;
        }
    }

    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60;  // this is number of BOXs that should be printed
                          // for the top bar (max value)
        string color;
    	sort(bars, bars + size, greater<Bar>());
        int bigNum = bars[0].getValue();
        if (top < 0 || top > size) {
            top = size;
        }

        for (int i = 0; i < top; ++i) {
            if (colorMap.count(bars[i].getCategory()) == 1) {
                color = colorMap[bars[i].getCategory()];
            }
            else {
                color = BLACK;
            }
            string barstr = "";
            int len = static_cast<int>(((bars[i].getValue() * 1.0) / bigNum) * lenMax);

            for (int j = 0; j < len; ++j) {
                barstr += BOX;
            }
            output << color << barstr << " " << bars[i].getName() << " " << bars[i].getValue() << endl;
        }
    }
};