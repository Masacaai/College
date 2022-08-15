/*
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    A program that is able to generate a personality quiz
    based on the five-factor model and match the player to
    a fictional character based on their answers.

    Creative Component:
    mine.people has the five-factor scores of a few of the
    most prominent superheroes.

*/
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "driver.h"

using namespace std;

/* readFile
 *
 * This function accepts a string filename and uses it to open the corresponding 
 * data file to read and store the data in a map that is returned.
*/
map<string, map<char, int>> readFile(string filename) {
    map<string, map<char, int>> data;
    map<char, int> temp;
    string buffer;

    ifstream infile(filename);
    if (infile.fail()) {
        cout << "Error: unable to open '" << filename << "'" << endl;
    } else {
        while (getline(infile, buffer)) {
            temp.clear();
            // Retrieves the text
            string name = buffer.substr(0, buffer.find("."));
            // Sets up a stringstream that starts AFTER the text
            stringstream line(buffer.substr(buffer.find(".") + 2));
            while (line >> buffer) {
                // Retrieves key
                char key = buffer.substr(0,buffer.find(":"))[0];
                // Retrieves value
                int num = stoi(buffer.substr(buffer.find(":") + 1));
                temp[key] = num;
            }
            data[name] = temp; 
        }
    }
    return data;
}

/* getQuestions
 *
 * This function accepts a map with data and populates a set of questions with
 * the map's keys and values.
*/
set<Question> getQuestions(const map<string, map<char, int>> & data) {
    set<Question> questions;
    Question temp;

    for (auto &d : data) {
        temp.questionText = d.first;
        temp.factors = d.second;
        questions.insert(temp);
    }
    return questions;
}

/* getPeople
 *
 * This function accepts a map with data and populates a set of people with
 * the map's keys and values.
*/
set<Person> getPeople(const map<string, map<char, int>> &  data) {
    set<Person> people;
    Person temp;

    for (auto &d : data) {
        temp.name = d.first;
        temp.scores = d.second;
        people.insert(temp);
    }
    return people;
}

/* main
 *
 * main function of the program. 
*/
int main() {
    map<string, map<char, int>> data;
    map<Question, int> answers;
    map<char, int> scores;
    set<Question> questions;
    set<Person> people;
    Question currentQn;
    int numQns, ans, testNum;
    string testName;

    data = readFile("questions.txt");
    questions = getQuestions(data);
    
    cout << "Welcome to the Personality Quiz!" << endl << endl
         << "Choose number of questions: ";
    cin >> numQns;
    cout << endl;

    for (int i = 0; i < numQns; ++i) {
        cout << "How much do you agree with this statement?" << endl;
        currentQn = randomQuestionFrom(questions);
        cout << "\"" << currentQn.questionText << ".\"" << endl << endl
             << "1. Strongly disagree" << endl
             << "2. Disagree" << endl
             << "3. Neutral" << endl
             << "4. Agree" << endl
             << "5. Strongly agree" << endl << endl
             << "Enter your answer here (1-5): ";
        cin >> ans;
        cout << endl;
        answers[currentQn] = ans;
    }
    
    scores = scoresFrom(answers);
    
    while (true) {
        cout << "1. BabyAnimals" << endl
             << "2. Brooklyn99" << endl
             << "3. Disney" << endl
             << "4. Hogwarts" << endl
             << "5. MyersBriggs" << endl
             << "6. SesameStreet" << endl
             << "7. StarWars" << endl
             << "8. Vegetables" << endl
             << "9. mine" << endl
             << "0. To end program." << endl << endl
             << "Choose test number (1-9, or 0 to end): ";
        cin >> testNum;

        if (testNum == 1) { testName = "BabyAnimals.people";  }
        if (testNum == 2) { testName = "Brooklyn99.people";   }
        if (testNum == 3) { testName = "Disney.people";       }
        if (testNum == 4) { testName = "Hogwarts.people";     }
        if (testNum == 5) { testName = "MyersBriggs.people";  }
        if (testNum == 6) { testName = "SesameStreet.people"; }
        if (testNum == 7) { testName = "StarWars.people";     }
        if (testNum == 8) { testName = "Vegetables.people";   }
        if (testNum == 9) { testName = "mine.people";         }
        if (testNum == 0) { break; }

        data = readFile(testName);
        people = getPeople(data);

        Person mostSimTo = mostSimilarTo(scores, people);
        cout << "You got " << mostSimTo.name << "!" << endl << endl;
    }
    cout << "Goodbye!" << endl;
    return 0;
}
