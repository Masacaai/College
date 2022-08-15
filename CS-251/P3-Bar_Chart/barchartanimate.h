/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains the BarChartAnimate class used in application.cpp
    to create a Bar chart animation program.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used in autograder, do not remove
#include "barchart.h"
  
using namespace std;

// BarChartAnimate
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts. It keeps track of the number of elements stored (size) and 
    // the capacity of the array (capacity). This IS a dynamic array, so it 
    // must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string title;
    string xlabel;
    string source;

    // getBarChart:
    // This function is used to retreieve barcharts from files. it takes
    // in the filestream and number of rows and returns a BarChart to be
    // added to a C-style array.
    BarChart getBarChart(ifstream &file, int n){
        string buffer, frame;
        BarChart bc(n);

        for (int i = 0; i < n; ++i) {
            string name, category;
            int value;
            getline(file, buffer);
            stringstream line(buffer);
            getline(line, frame, ',');
            getline(line, name, ',');
            getline(line, buffer, ','); // Skip unneeded data
            getline(line, buffer, ',');
            value = stoi(buffer);
            getline(line, category, ',');
            bc.setFrame(frame);
            bc.addBar(name, value, category);
        }
        return bc;
    }

    // createColorMap:
    // This function populates the colorMap to be used in the animate()
    // function. It iterates through all the bars and adds their category
    // to the colorMap if it isn't already present. If number of categories
    // exceeds the number of colord available, it loops back to reuse colors.
    void createColorMap() {
        long unsigned int k = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < barcharts[i].getSize(); ++j) {
                if (colorMap.count(barcharts[i][j].getCategory()) != 1) {
                    colorMap[barcharts[i][j].getCategory()] = COLORS.at(k);
                    if (k != COLORS.size() - 1) {
                        k++;
                    } else {
                        k = 0;
                    }
                }
            }
        }
    }

 public:
    // a parameterized constructor:
    // The barcharts C-array is constructed with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        barcharts = new BarChart[4];
        size = 0;
        capacity = 4;
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        if (barcharts != nullptr) {
            for (int i = 0; i < size; ++i) {
                barcharts[i].clear();
            }
            delete[] barcharts;
        }
    }

    
    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, it doubles the capacity.
    void addFrame(ifstream &file) {
        string buffer;
        int rows;

        if (size == capacity) {
            int newCapacity = capacity * 2;
            BarChart* newBarcharts = new BarChart[newCapacity];

            for (int i = 0; i < size; ++i) {
                newBarcharts[i] = barcharts[i];
            }

            for (int i = 0; i < size; ++i) {
                barcharts[i].clear();
            }
            delete[] barcharts;
            barcharts = newBarcharts;
            capacity = newCapacity;
        }

        getline(file, buffer);
        if (!file.eof()) {
            getline(file, buffer);
            rows = stoi(buffer);
            BarChart bc(rows); 
            bc = getBarChart(file, rows);
            barcharts[size] = bc;
            size++;
        }
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, it pauses between each frame with usleep().
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), it outputs CLEARCONSOLE in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
        
        if (endIter < 0 || endIter > size) {
            endIter = size;
        }
        
        createColorMap();
        for (int i = 0; i < endIter; ++i) {          
            usleep(3 * microsecond); 	
		    output << CLEARCONSOLE;
            output << BLACK << title << endl << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl << "Frame: " << barcharts[i].getFrame() << endl;
        }
	}

    // animate (overloaded):
    // this function is the same as the one above, except it's overloaded to be
    // used in the creative component. It takes in additional parameters of speed,
    // startFrame and endFrame to control the animation.
    void animate(ostream &output, int top, double speed, string startFrame, string endFrame) {
		unsigned int microsecond = 50000;
        int start = 0;
        int end = size - 1;
        createColorMap();

        for (int i = 0; i < size; ++i) {
            if (barcharts[i].getFrame() == startFrame) {
                start = i;
            }
            if (barcharts[i].getFrame() == endFrame) {
                end = i;
            }
        }
        for (int i = start; i < end + 1; ++i) {          
            usleep((3 * microsecond) / speed); 	
		    output << CLEARCONSOLE;
            output << BLACK << title << endl << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl << "Frame: " << barcharts[i].getFrame() << endl;
        }
        output << RESET;
	}

    // Returns the size of the BarChartAnimate object.
    int getSize(){return size;}

    //
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){
        if (i < 0 || i >= size) {
            throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];}
};
