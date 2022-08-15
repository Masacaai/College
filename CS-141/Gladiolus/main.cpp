/* ---------------------------------------------
    Program 1: Gladiolus
        Prompt for the number of sections and display
        an ASCII gladiolus flower, with the sections centered
        above each other.

    Course: CS 141, Fall 2021. Tues 9 AM lab
    System: Fedora 34 using JetBrains CLion
    Author: Mohammed Aaqel Shaik Abdul Mazeed
    
    Original ASCII graphics gives:
   ---------------------------------------------
                __/    \_/    \__
                  \     |     /
                  _\/  \|/  \/_
                    \   |   /
                     o  o  o
                     o     o
                     o  o  o
                    /   |   \
                   /\  /|\  /\
                  /     |     \
                /`\    /`\    /`\
                    SNOWFLAKE
   ---------------------------------------------
*/

#include <iostream>   // for cin and cout
#include <iomanip>    // for setw. The number in setw(...) is the total of blank spaces including the printed item.
#include <cmath>      // for pow()


using namespace std;  // so that we don't need to preface every cin and cout with std::

// Entire program is given inside of main(), which is acceptable since this is the first program.
int main() {

    // Display the menu and get the user choice
    int menuOption = 0;
    cout << "Program 1: Gladiolus            \n"
         << "Choose from among the following options:  \n"
         << "   1. Display original graphic  \n"
         << "   2. Display Gladiolus         \n"
         << "   3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;

    // Handle menu option of 3 to exit
    if( menuOption == 3) {
        exit( 0);
    }
        // Handle menu option of 1 to display custom ASCII graphics
    else if( menuOption == 1) {

        // Display a line across the top
        for( int i=0; i<42; i++) {
            cout << "-";
        }
        cout << endl;
        // Display ASCII graphics for snowflake.

        cout << setw(12) << " " << "__/    \\_/    \\__\n";
        cout << setw(12) << " " << "  \\     |     /\n";
        cout << setw(12) << " " << "  _\\/  \\|/  \\/_\n";
        cout << setw(12) << " " << "    \\   |   /\n";
        cout << setw(12) << " " << "     o  o  o\n";
        cout << setw(12) << " " << "     o     o\n";
        cout << setw(12) << " " << "     o  o  o\n";
        cout << setw(12) << " " << "    /   |   \\\n";
        cout << setw(12) << " " << "   /\\  /|\\  /\\\n";
        cout << setw(12) << " " << "  /     |     \\\n";
        cout << setw(12) << " " << "/`\\    /`\\    /`\\\n";
        cout << endl;
        cout << setw(16) << " " << "SNOWFLAKE";

        cout << endl;

        // Display a line across the bottom
        for( int i=0; i<42; i++) {
            cout << "-";
        }
        cout << endl;
    } //end if( menuOption == 1)  // menu option to display custom graphic

    else if( menuOption == 2) {
        // Prompt for and get the number of flower sections.

        int numberOfSections = 0;
        cout << "Number of sections -> ";
        cin >> numberOfSections;

        // Place your code starting here
        // ...
        int section = 1; // Iterating variable for first loop
        int row = 1; // Iterating variable for second loop
        int numberOfRows = 1; // Number of rows in a section
        int spaces = 0; // Spaces before the first character in each line
        int maxRows = (numberOfSections * 2) - 1; // Number of rows in the final section
        int sectionWidth = numberOfRows + 4; // width of the middle row in a section
        int maxWidth = maxRows + 4; // Maximum width in the final section
        int midSpace; // spaces in between characters in each row

        // Loop that iterates through the different sections
        while ( section <= numberOfSections ) {
            midSpace = 4;
            spaces = (maxWidth / 2) - 2;
            cout << setw(spaces + 4);
            cout << "---" << endl;

            // Loop that iterates through rows in each section
            while (row <= numberOfRows) {
                cout << setw(spaces + 1);
                cout << "(";

                // If we're at the middle row, then print the '@' symbol.
                if ( row == (numberOfRows / 2) + 1) {
                    cout << setw( sectionWidth / 2 );
                    cout << "@";
                    cout << setw( sectionWidth / 2 );
                    cout << ")" << endl;
                }
                    // Else, print the ending parenthesis after a certain number of spaces.
                else {
                    cout << setw(midSpace);
                    cout << ")" << endl;
                }
                row++;

                // Update the spaces and midSpace variables after each row depending on our position in the section
                if (row <= (numberOfRows / 2) + 1 ) {
                    spaces -= 1;
                    midSpace += 2;
                }
                else {
                    spaces += 1;
                    midSpace -= 2;
                }
            }
            section++; // Update the iterating variable section
            row = 1; // Reset the value of variable after a section ends
            numberOfRows += 2; // Increment the variable for the next section
            sectionWidth = numberOfRows + 4; // Reset the variable after numberOfRows is updated
        }
        cout << setw(spaces + 3);
        cout << "---" << endl;

        // This section of the code creates the stem and leaves of the flower
        int stem = 1; // Iterating variable for creating the stem
        int leaf = 0;

        while ( stem <= numberOfSections * 2) {
            if ((stem % 2) == 0 ) {
                cout << setw(spaces + 2);
                cout << "|" << endl;
            }
            else {
                if (stem == 3 + 4 * leaf)  {
                    cout << setw(spaces + 2);
                    cout << "\\|" << endl;
                    leaf += 1;
                }
                else {
                    cout << setw(spaces + 3);
                    cout << "|/" << endl;
                }
            }
            stem++; // Increments variable for the next iteration
        }
    } //end if( menuOption == 2) // menu option to display building

    cout << "Exiting" << endl;
    return 0;
}// end main()
