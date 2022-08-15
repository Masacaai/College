    /* ---------------------------------------------
        Program 3: Typing
            Create a typing tutor program that prompts for
            words to type, keeping track whether you
            spell them correctly, within a time limit.

        Pair Programming:

     1) Course: CS 141, Fall 2021. Tues 9 AM lab
        System: Fedora 34 using JetBrains CLion
        Author: Mohammed Aaqel Shaik Abdul Mazeed

     2) Course: CS 141, Fall 2021. Tues 11 AM lab
        System: Windows 10 using JetBrains CLion
        Author: Jose Cuellar

*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <vector>     // Input file is stored in a vector
#include <cassert>    // For the assert statement used to validate file open
#include <cctype>     // Allows using the toupper() function
#include <ctime>      // Timer functions

using namespace std;

// Read words from dictionary.txt into a vector.
void readFromDictionary( vector <string> & vect)
{
    // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "dictionary.txt");       // Open dictionary file
    assert( inStream.fail() == false );     // Ensure file open worked

    // Clear the vector in case it is used previously.
    vect.clear();

    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while( inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        vect.push_back( newWord);
    }

    // Close the dictionary file
    inStream.close();
}

// Read words from misspelledWords.txt into a vector.
void readFromMisspelledWords( vector <string> & vect, bool correct)
{
    // Read in misspelledWords.txt into vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open("misspelledWords.txt");       // Open file
    assert( inStream.fail() == false );     // Ensure file open worked

    // Clear vector in case it is used previously.
    vect.clear();

    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    int count = 1;
    while( inStream >> newWord) {           // While there is another word to be read

        vector <string> notRequiredWords; // Create a vector to handle the words that aren't required.
        if (correct){
            if (count % 2 == 0){ // If count is even, then it is a correct word.
                vect.push_back( newWord);
            }
            else {
                notRequiredWords.push_back( newWord); // Get rid of words that aren't spelled correctly.
            }
        }
        else{
            if (count % 2 != 0){ // If count is odd, then it is a misspelled word.
                vect.push_back( newWord);
            }
            else {
                notRequiredWords.push_back( newWord); // Get rid of words that are spelled correctly.
            }
        }
        count++;
    }
    // Close the file
    inStream.close();
}


//Function to calculate score
void scoreCalc(int time, int correct, int wrong, int & score, long unsigned int len = 5, bool isThisFromDictionary = false){
    int correctMultiplier = 3;
    int wrongMultiplier = correctMultiplier * 2;

    if ( time > 15){ // If elapsed time is more than 15 seconds
        cout << "Elapsed time: " << time << " seconds. " << (time - 15) * 3 << " points for finishing " << time - 15 << " seconds late." << endl;
        score -= (time - 15) * 3;
    }
    else { // If time elapsed is less than 15 seconds
        cout << "Elapsed time: " << time << " seconds. " << (15 - time) * 2 << " point bonus for finishing " << 15 - time << " seconds early." << endl;
        score += (15 - time) * 2;
    }

    if (isThisFromDictionary){ // If we're using dictionary.txt (option 2), then scoring is done differently, utilizing wordLength.
        correctMultiplier = len - 4;
        wrongMultiplier = correctMultiplier * 2;
    }
    cout << correct * correctMultiplier << " points: " << correct << " spelled correctly x " << correctMultiplier << " points each" << endl;
    score += correct * correctMultiplier;

    if (wrong != 0){
        cout << wrong * wrongMultiplier << " point penalty: " << wrong << " spelled incorrectly x " << wrongMultiplier << " points each" << endl;
        score -= wrong * wrongMultiplier;
    }
}
// Function for commonly misspelled words
void commonlyMisspelledWords(vector <string> correct, vector <string> wrong, vector <int> & scores){
    string correctWords[5]; // Handles the correct words to check with
    string wrongWords[5]; // Handles the words misspelled by the user
    string wordToCheck;
    int numOfCorrectWords = 0;
    int numOfWrongWords = 0;
    int elapsedTime = 0;
    int score = 0;

    cout << "Using commonly misspelled words" << endl;

    for (int i = 0; i < 5; ++i){
        int a = rand() % 114; // Pick a random number between 0..113
        correctWords[i] = correct[a]; //Add it to correctWords to check later.
        cout << wrong[a] << " ";
    }

    cout << endl << "Type in those words within goal of 15 seconds:" << endl;

    // Declare a variable to hold a time, and set it to the current time
    time_t startTime = time( NULL);

    for(int i = 0; i < 5; ++i){
        cin >> wordToCheck;
        if (wordToCheck == correctWords[i]){
            numOfCorrectWords++; //If the word is spelled correctly, then increment the number of correct words.
            wrongWords[i] = " ";
        }
        else {
            wrongWords[i] = wordToCheck;
            numOfWrongWords++;
        }
    }
    //Find the difference between the current time and the start time
    elapsedTime = difftime( time( NULL), startTime);
    if (numOfWrongWords == 0){
        cout << "No misspelled words!" << endl;
    }
    else {
        cout << "Misspelled words:" << endl;
        for (int i = 0; i < 5; ++i) {
            if (wrongWords[i] != " ") {
                cout << wrongWords[i] << " should be: " << correctWords[i] << endl;
            }
        }
    }
    scoreCalc(elapsedTime,numOfCorrectWords, numOfWrongWords, score);
    scores.push_back(score);
    cout << "Score: " << score;
}

// Function for random words
void randomWords( vector <string> dictionary, long unsigned int len, vector <int> & scores){
    string words[5]; // Handle words to check for spelling
    string wordToCheck;
    int numOfCorrectWords = 0;
    int numOfWrongWords = 0;
    string wrongWords[5];
    int elapsedTime = 0;
    int score = 0;

    cout << "Using full dictionary" << endl;
    int i = 0;

    while (i < 5){
        int a = rand() % dictionary.size(); //Picks a random number between 0..263533
        if (dictionary[a].length() == len){
            words[i] = dictionary[a];
            cout << words[i] << " ";
            i++;
        }

    }

    cout << endl << "Type in those words within goal of 15 seconds:" << endl;

    // Declare a variable to hold a time, and set it to the current time
    time_t startTime = time( NULL);

    for(int i = 0; i < 5; ++i){
        cin >> wordToCheck;
        if (wordToCheck == words[i]){
            numOfCorrectWords++;
            wrongWords[i] = " ";
        }
        else {
            wrongWords[i] = wordToCheck;
            numOfWrongWords++;
        }
    }
    //Find the difference between the current time and the start time
    elapsedTime = difftime( time( NULL), startTime);
    if (numOfWrongWords == 0){
        cout << "No misspelled words!" << endl;
    }
    else {
        cout << "Misspelled words:" << endl;
        for (int i = 0; i < 5; ++i) {
            if (wrongWords[i] != " ") {
                cout << wrongWords[i] << " should be: " << words[i] << endl;
            }
        }
    }
    scoreCalc(elapsedTime,numOfCorrectWords, numOfWrongWords, score, len, true);
    scores.push_back(score);
    cout << "Score: " << score;

}

// Function for displaying words from lists
void displayWordLists(vector <string> dict, vector <string> correct, vector <string> wrong){
    char choice;
    int start, end;
    vector <string> list;

    cout << "Displaying word list entries." << endl
    << "Which words do you want to display?" << endl
    << "A. Dictionary of all words" << endl
    << "B. Wrongly spelled common misspelled words" << endl
    << "C. Correctly spelled common misspelled words" << endl
    << "Your choice --> ";
    cin >> choice;
    choice = toupper(choice);

    if(choice == 'A'){ // Assign the vector to list depending on the choice picked by player
        list = dict;
        cout << "Enter the start and end indices between 0 and 263532: ";
    }
    if(choice == 'B'){
        list = wrong;
        cout << "Enter the start and end indices between 0 and 113: ";
    }
    if(choice == 'C'){
        list = correct;
        cout << "Enter the start and end indices between 0 and 113: ";
    }

    cin >> start;
    cin >> end;
    for (int i = start; i <= end; ++i){
        cout << i << ". " << list[i] << endl;
    }


}

// Function for binary searching through dictionary
void binarySearch(vector <string> dict){
    string word;
    int low, mid, high;
    int count = 1;
    bool found = false;

    cout << "Enter the word to lookup: ";
    cin >> word;

    low = 0;
    high = dict.size() - 1;

    while ( low <= high) {
        mid = (low+high)/2;
        cout << count << ". Comparing to: " << dict[mid] << endl;
        if (word == dict[mid]){
            cout << word << " was found." << endl;
            found = true;
            break;
        }
        else if (word < dict[mid]){
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
        count++;
    }

    if (!found){
        cout << word << " was NOT found." << endl;
    }
}

// Function for setting word length
void setWordLength(long unsigned int  & len){
    cout << "Enter new wordLength: ";
    cin >> len;
    cout << endl;
}

// Function to display main menu
void mainMenu(){
    cout << endl << "Select a menu option:" << endl
         << "1. Spell commonly misspelled words (timed)" << endl
         << "2. Type random words from full dictionary (timed)" << endl
         << "3. Display some words from one of the lists" << endl
         << "4. Use binary search to lookup a word in full dictionary" << endl
         << "5. Set word length to use with full dictionary" << endl
         << "6. Exit the program" << endl
         << "Your choice --> ";

}
int main() {
    srand(1);
    int choice = 0;
    int bestScore = 0;
    long unsigned int wordLength = 5;
    vector <int> scores;
    scores.push_back(0);
    vector<string> dictionary;
    vector<string> correctMisspelled;
    vector<string> wrongMisspelled;

    //Read all the words from the files into their respective vectors
    readFromDictionary(dictionary);
    readFromMisspelledWords(correctMisspelled, true);
    readFromMisspelledWords(wrongMisspelled, false);

    cout << "There are 263533 words in the full dictionary." << endl
         << "There are 114 commonly misspelled words." << endl;

    //Main loop
    while (choice != 6){
        mainMenu();
        cin >> choice;

        // Calls the corresponding function based on player's choice.
        if (choice == 1){commonlyMisspelledWords(correctMisspelled, wrongMisspelled, scores);}
        if (choice == 2){
            randomWords( dictionary, wordLength, scores);
            wordLength++;
        }
        if (choice == 3){displayWordLists(dictionary, correctMisspelled, wrongMisspelled);}
        if (choice == 4){ binarySearch(dictionary);}
        if (choice == 5){setWordLength(wordLength);}
        if (choice == 6){ cout << endl << "Exiting program" << endl;}
    }

    bestScore = scores.at(0); // Search for highest score in the vector of scores accumulated over the course of the session.
    for (long unsigned int i = 0; i < scores.size(); ++i){
        if(scores.at(i) > bestScore){
            bestScore = scores.at(i);
        }
    }
    cout << "Best score was " << bestScore;
    return 0;
}
