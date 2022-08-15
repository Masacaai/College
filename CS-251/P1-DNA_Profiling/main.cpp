/*
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    An app that is able to build DNA strands using 
    the provided ourvector implementation and then 
    determine who the DNA matches to in a database. 

    Creative Component:
    The option to add a person to either small.txt 
    or large.txt along with the maximum number of 
    times each STR appears consecutively in their 
    DNA sequence.

    To test this feature, use the following command:
    > add_person <name>

    This function allows the user to choose between 
    either linking a name to an existing DNA file or 
    manually writing the record to the database file.

    If the DNA file chosen is already linked to a 
    record in the database, it notifies the user and 
    asks them to try again. It does this by running 
    all other functions in the program to find a 
    possible match. 
    
    If no match is found, it proceeds to write the 
    name and the STR counts of the chosen DNA file 
    to the database file. If a match is found, it 
    stops and request the user to select a file 
    with no pre-existing record.
    

*/

#include <string>
#include <sstream>
#include <fstream>
#include "ourvector.h"
using namespace std;

// Struct to hold name and an ourvector object with
// the number of maximum consecutive patterns of STR
// appearing in that person's DNA sequence
struct record {
    string name;
    ourvector<int> str_counts;
};

/* Function #1: load_db
   Purpose: Loads the database file and populates the ourvector objects 'strands' and 'people'
   Parameters: - string & file                          => To be loaded 
               - ourvector<ourvector<string>> & strands => To be populated inside the function
               - ourvector<record> & people             => To be populated inside the function
               - ourvector<string> & temp               => To serve as an intermediate ourvector 
                                                           to populate 'strands'
   Return value: No return value.
*/
void load_db(const string & file,
             ourvector<ourvector<string>> & strands,
             ourvector<record> & people,
             ourvector<string> & temp) {
    string buffer;

    cout << "Loading database..." << endl;
    ifstream infile(file);
    if (infile.fail()) {
        cout << "Error: unable to open '" << file << "'" << endl;
    } else {
        // To populate 'strands' with STRs
        getline(infile, buffer);
        stringstream line(buffer);
        getline(line, buffer, ',');           // To skip 'name'
        while (getline(line, buffer, ',')) {
            temp.clear();
            for (char c : buffer) {
                string l(1, c);               // Convert char to string
                temp.push_back(l);
            }
            strands.push_back(temp);
        }

        // To populate 'people' with records
        while (getline(infile, buffer)) {
            record temp;
            stringstream line(buffer);
            getline(line, temp.name, ',');
            while (getline(line, buffer, ',')) {
                temp.str_counts.push_back(stoi(buffer));
            }
            people.push_back(temp);
        }

        infile.close();
    }
}

/* Function #2: load_dna 
   Purpose: Loads the DNA file and populates the ourvector object 'dna' 
   Parameters: - string & file           => To be loaded
               - ourvector<string> & dna => To be populated inside the function
   Return value: No return value
*/
void load_dna(const string & file, ourvector<string> & dna) {
    string buffer;

    cout << "Loading DNA..." << endl;
    ifstream infile(file);
    if (infile.fail()) {
        cout << "Error: unable to open '" << file << "'" << endl;
    } else {
        getline(infile, buffer);
        for (char s : buffer) {
            string str(1, s);   // Convert char to string
            dna.push_back(str);
        }

        infile.close();
    }
}

/* Function #3: numMatches
   Purpose: Finds the maximum number of consecutive repeats of a particular STR
   Parameters: - ourvector<string> & strand => To get the STR 
               - ourvector<string> & dna    => To search for consecutive repetitions 
                                               of the STR in the DNA sequence
   Return value: Returns the maximum number of consecutive occurances of the STR in 
                 the DNA sequence as an integer
*/
int numMatches(ourvector <string> & strand, ourvector<string> & dna) {
    int max = 0;
    int count = 0;

    // Loops through DNA sequence
    for (int i = 0; i < dna.size(); ++i) {
        for (int j = 0; j < strand.size(); ++j) {
            if (i+j >= dna.size()) {
                break;
            }

            // Keep going if strings match.
            // If they don't, reset count and break out of iteration.
            if (dna.at(i+j) != strand.at(j)) {
                count = 0;
                break;
            }

            // If you reach the end of STR, increment count.
            if (j == strand.size()-1) {
                count++;
                i += strand.size() - 1;
            }
        }
       if (count > max) {
           max = count;
        }
    }
    return max;
}

/* Function #4: process
   Purpose: Processes the given DNA sequence and STRs provided to populate 'dna_str_counts'
   Parameters: - ourvector<ourvector<string>> & strands => To get the STR patterns we need to search for
               - ourvector<string> & dna                => To get the DNA sequence
               - ourvector<int> & dna_str_counts        => To be populated inside the function
   Return value: No return value
*/
void process(ourvector<ourvector<string>> & strands,
             ourvector<string> & dna,
             ourvector<int> & dna_str_counts) {
    string buffer;
    if (strands.size() == 0) {
        cout << "No database loaded." << endl;
    } else if (dna.size() == 0) {
        cout << "No DNA loaded." << endl;
    } else {
        cout << "Processing DNA..." << endl;

        // For every strand in the database file, run numMatches
        for (int i = 0; i < strands.size(); ++i) {
            int str = numMatches(strands.at(i), dna);
            dna_str_counts.push_back(str);
        }
    }
}

/* Function #5: display
   Purpose: Display the current state of the program and its variables
   Parameters: - ourvector<record> & people             => To display the records of people
               - ourvector<string> & dna                => To display the DNA sequence
               - ourvector<ourvector<string>> & strands => To display the STRs in consideration
               - ourvector<int> & dna_str_counts        => To display the counts of STRs processed
                                                           in the given DNA sequence
   Return value: No return value
*/
void display(
    ourvector<record> & people,
    ourvector<string> & dna,
    ourvector<ourvector<string>> & strands,
    ourvector<int> & dna_str_counts) {

    if (people.size() == 0) {
        cout << "No database loaded." << endl;
    } else {
        cout << "Database loaded: " << endl;
        for (int i = 0; i < people.size(); ++i) {
            cout << people.at(i).name;
            for (int j = 0; j < people.at(i).str_counts.size(); ++j) {
                cout << " " << people.at(i).str_counts.at(j);
            }
            cout << endl;
        }
    }

    cout << endl;

    if (dna.size() == 0) {
        cout << "No DNA loaded." << endl << endl;
    } else {
        cout << "DNA loaded: " << endl;
        for (int i = 0; i < dna.size(); ++i) {
            cout << dna.at(i);
        }
        cout << endl;
    }
    cout << endl;

    if (dna_str_counts.size() == 0) {
        cout << "No DNA has been processed." << endl;
    } else {
        cout << "DNA processed, STR counts: " << endl;
        for (int i = 0; i < strands.size(); ++i) {
            for (int j = 0; j < strands.at(i).size(); ++j) {
                cout << strands.at(i).at(j);
            }
            cout << ": " << dna_str_counts.at(i) << endl;
        }
    }
    cout << endl;
}

/* Function #6: search 
   Purpose: Searches the loaded database for a match with the processed DNA sequence
   Parameters: - ourvector<int> & dna_str_counts => To get the counts of STRs in the processed DNA
               - ourvector<record> & people      => To get the records of people to match
               - ourvector<string> & dna         => To check if DNA has been loaded
               - bool & found                    => To be updated inside the program if a match is found
   Return value: No return value
*/
void search(ourvector<int> & dna_str_counts,
            ourvector<record> & people,
            ourvector<string> & dna,
            bool & found) {
    string name;

    if (people.size() == 0) {
        cout << "No database loaded." << endl;
    } else if (dna.size() == 0) {
        cout << "No DNA loaded." << endl;
    } else if (dna_str_counts.size() == 0) {
        cout << "No DNA processed." << endl;
    } else {
        cout << "Searching database..." << endl;

        for (int i = 0; i < people.size(); ++i) {
            found = true;
            for (int j = 0; j < people.at(i).str_counts.size(); ++j) {
                // Keep going if numbers match.
                // If there is any difference, set 'found' to false and break
                if (people.at(i).str_counts.at(j) != dna_str_counts.at(j)) {
                    found = false;
                    break;
                }
            }
            // Here, 'found' will only be true when the program is able to go
            // through the entire loop without finding a deviation, thereby 
            // verifying our match.
            if (found) {
                name = people.at(i).name;
                break;
            }
        }

        if (found) {
            cout << "Found in database!  DNA matches: " << name << endl;
        } else {
            cout << "Not found in database." << endl;
        }
    }
}

/* Function #7: writeFile
   Purpose: Appends data to the database files
   Parameters: - string & db_file                => To be opened and data appended to
               - string & name                   => To write the name to the file
               - ourvector<int> & dna_str_counts => To write the values of STR counts
   Return value: No return value
*/
void writeFile(string & db_file,
               string & name,
               ourvector<int> & dna_str_counts) {
    ofstream outfile;
    outfile.open(db_file, ios::app);  // Open file in append mode
    outfile << name;
    for (int i = 0; i < dna_str_counts.size(); ++i) {
        outfile << "," << dna_str_counts.at(i);
    }
    outfile << endl;
}

/* Function #8: add_person
   Purpose: Adds a person and their STR counts to either of the two databases available
   Parameters: - string & name                          => To get the name of the person
               - ourvector<int> & dna_str_counts        => To be populated inside the function when writing STR counts to file
               - ourvector<ourvector<string>> & strands => To be used to load the database when checking existing records
               - ourvector<record> & people             => To be used to load the database when checking existing records
               - ourvector<string> & dna                => To determine the database file to load
               - ourvector<string> & temp               => To be used to load the database when checking existing records
   Return value: No return value
*/
void add_person(
    string & name,
    ourvector<int> & dna_str_counts,
    ourvector<ourvector<string>> & strands,
    ourvector<record> & people,
    ourvector<string> & dna,
    ourvector<string> & temp) {

    string dna_file;
    string db_file;
    bool found = true;
    char choice;
    int tempint;

    cout << "Do you want "
         << name
         << " linked to an existing DNA file? (Y/N): ";
    cin >> choice;
    choice = toupper(choice);
        
    while (true) {
        if (choice == 'Y') {
            cout << "Which DNA file do you want "
                 << name
                 << " linked to?: ";
            cin >> dna_file;
            cout << endl;

            while (true) {
                tempint = stoi(dna_file.substr(0, dna_file.find('.')));
                if (tempint >= 1 && tempint <= 4) {  // Since 1-4.txt is assigned to small.txt
                    db_file = "small.txt";
                    break;
                } else if (tempint >= 5 && tempint <= 20) {  // Since 5-20.txt is assigned to large.txt
                    db_file = "large.txt";
                    break;
                } else {
                    cout << "Enter the name of an existing DNA file!" << endl;
                }
            }

            cout << "Attempting to check if given DNA file is"
                 << "already linked to a name in the database..." << endl;
            load_db(db_file, strands, people, temp);
            load_dna(dna_file, dna);
            process(strands, dna, dna_str_counts);
            search(dna_str_counts, people, dna, found);
            if (found) {
                cout << "This DNA file is already linked to an existing person in the database. Please try again." << endl;
            } else {
                writeFile(db_file, name, dna_str_counts);
                cout << name << " has been added to " << db_file << " and linked to DNA file " << dna_file << "." << endl;
            }
            break;
        } else if (choice == 'N') {
            cout << "Which file do you want " << name << " added to? : ";
            cin >> db_file;
            cout << endl;
            cout << "Enter the maximum number of times each of "
                 << "the following STRs appear consecutively in "
                 << name << "'s DNA sequence:" << endl;
            load_db(db_file, strands, people, temp);

            // Loop through every STR, prompting user for count values
            for (int i = 0; i < strands.size(); ++i) {
                for (int j = 0; j < strands.at(i).size(); ++j) {
                    cout << strands.at(i).at(j);
                }
                cout << ": ";
                cin >> tempint;
                dna_str_counts.push_back(tempint);
            }

            writeFile(db_file, name, dna_str_counts);
            cout << name << " has been added to " << db_file << "." << endl;
            break;
        } else {
            cout << "Please enter a valid option!" << endl;
        }
    }
}

/* Function #9: main 
   Purpose: The main function of the program
   Parameters: No parameters
   Return value: Returns 0
*/
int main() {
    string command, arg;                    // Command and argument
    ourvector<ourvector<string>> strands;   // Holds STRs from database file selected
    ourvector<record> people;               // Holds records of people found in database
    ourvector<string> dna;                  // Holds DNA sequence from DNA file selected
    ourvector<int> dna_str_counts;          // Holds STR counts obtained from processed DNA
    ourvector<string> temp;                 // Temporary ourvector object used when populating 'strands'
    bool found;

    cout << "Welcome to the DNA Profiling Application." << endl;
    while (true) {
        cout << "Enter command or # to exit: ";
        cin >> command;
        if (command == "load_db") {
            cin >> arg;
            strands.clear();
            people.clear();
            temp.clear();
            dna_str_counts.clear();
            load_db(arg, strands, people, temp);
        } else if (command == "load_dna") {
            cin >> arg;
            dna_str_counts.clear();
            dna.clear();
            load_dna(arg, dna);
        } else if (command == "process") {
            dna_str_counts.clear();
            process(strands, dna, dna_str_counts);
        } else if (command == "process_all") {
            dna_str_counts.clear();
            process(strands, dna, dna_str_counts);
        } else if (command == "display") {
            display(people, dna, strands, dna_str_counts);
        } else if (command == "search") {
            found = true;
            search(dna_str_counts, people, dna, found);
        } else if (command == "add_person") {
            cin >> arg;
            dna_str_counts.clear();
            strands.clear();
            dna.clear();
            people.clear();
            temp.clear();
            add_person(arg, dna_str_counts, strands, people, dna, temp);
        } else if (command == "#") {
            break;
        } else {
            cout << "Please enter a valid command!" << endl;
        }
    }
    return 0;
}
