/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This application uses BarChartAnimate (which uses BarChart, which uses Bar)
    to produce an animated bar chart.

	Creative Component:
	A fully-featured console-driven menu that allows the user to control various
	aspects of the animation. 

	Available commands:
	  read <filename>        - Reads data from the file given as argument.
	  setTop <int>           - Set the number of top records to display in animation. (-1 shows all records)
	  setStart <frame>       - Sets the start frame for animation. (-1 resets startFrame)
	  setEnd <frame>         - Sets the end frame for animation. (-1 resets endFrame)
	  setSpeed <factor>      - Sets the playback speed based on factor given as argument.
	  display                - Display the animated barchart.

	If the user attempts to display an animation before reading in a file,
	the program prompts the user to read a file first.
 
	The user can input any double as a factor for playback speed. 0.5 halves the playback speed,
	and 2 doubles it.

	If the user displays the animation without setting any variables, default values are used:
	  StartFrame - Starts the animation from the beginning.
	  EndFrame - Ends the animation at the final frame.
	  Speed - Plays the animation in 1x speed.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {
	string filename = "-1";
	string title, xlabel, source;
	string command = "";
	double speed = 1;
	int topRecords = -1;
	string startFrame = "-1";
	string endFrame = "-1";

	cout << "Welcome to the Animated Bar Chart Program!" << endl;
	while (command != "#") {
		cout << "Available commands:" << endl
			 << "  read <filename>        - Reads data from the file given as argument." << endl
			 << "  setTop <int>           - Set the number of top records to display in animation. (-1 shows all records)" << endl
			 << "  setStart <frame>       - Sets the start frame for animation. (-1 resets startFrame)" << endl
			 << "  setEnd <frame>         - Sets the end frame for animation. (-1 resets endFrame)" << endl
			 << "  setSpeed <factor>      - Sets the playback speed based on factor given as argument." << endl
			 << "  display                - Display the animated barchart." << endl
			 << "Enter commands or # to exit: ";
		cin >> command;
		cout << endl;

		if (command == "read") {
			cin >> filename;
			cout << "'" << filename << "' read." << endl;
		}

		if (command == "setTop") {
			cin >> topRecords;
			if (topRecords == -1) {
				cout << "All records will be shown." << endl;
			} else {
				cout << "The top " << topRecords << " records will be shown." << endl;
			}
		}
		if (command == "setStart") {
			cin >> startFrame;
			if (startFrame == "-1") {
				cout << "StartFrame is reset to the beginning." << endl;
			} else {
				cout << "'" << startFrame << "' set as start frame." << endl;
			}
		}
		if (command == "setEnd") {
			cin >> endFrame;
			if (endFrame == "-1") {
				cout << "EndFrame is reset to the end." << endl;
			} else {
				cout << "'" << endFrame << "' set as end frame." << endl;
			}
		}
		if (command == "setSpeed") {
			cin >> speed;
			cout << "Playback speed set to " << speed << "." << endl;
		}
		if (command == "display") {
			if (filename != "-1") {	
				ifstream inFile(filename);
				if (inFile.fail()) {
					cout << "Error: unable to open '" << filename << "'" << endl;
				} else {
					getline(inFile, title);
					getline(inFile, xlabel);
					getline(inFile, source);

					BarChartAnimate bca(title, xlabel, source);

					while (!inFile.eof()) {
						bca.addFrame(inFile);
					}

					bca.animate(cout, topRecords, speed, startFrame, endFrame);
				}
			} else {
				cout << "Please read a file first!" << endl;
			}
		}
		cout << endl;
	}
	cout << "Goodbye!" << endl;
    return 0;
}
