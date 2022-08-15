/* ---------------------------------------------
    Program 4: Divvy Bike Data Analysis
        Quantify and summarize Divvy Bike data
        and analyze patterns and similarities
        between a weekday (September 1st) and
        a weekend (September 4th).

    Course: CS 141, Fall 2021. Tues 9 AM lab
    System: Fedora 34 using JetBrains CLion
    Author: Mohammed Aaqel Shaik Abdul Mazeed
    Menu Option 5 Extra Credit URL:https://www.google.com/maps/place/41%C2%B052'44.6%22N+87%C2%B038'09.2%22W/@41.8790511,-87.6380683,859m/data=!3m2!1e3!4b1!4m5!3m4!1s0x0:0x0!8m2!3d41.8790471!4d-87.6358796
    Coordinates for the home I would like to live in: 41.87904707698284, -87.63587959382963

*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include <iomanip>    // For setprecision()

using namespace std;

// Class for creating Ride Objects
class Ride{

public:
    // Fully qualified constructor with default parameters
    Ride(string rideID = "0", string rideableType = "0", string startTimeDate = "0", string endTimeDate = "0", string startStation = "0", string endStation = "0", long double startLat = 0, long double startLng = 0, long double endLat = 0, long double endLng = 0, string riderType = "0"){
        Ride::rideID = rideID;
        Ride::rideableType = rideableType;
        Ride::startTimeDate = startTimeDate;
        Ride::endTimeDate = endTimeDate;
        Ride::startStation = startStation;
        Ride::endStation = endStation;
        Ride::startLat = startLat;
        Ride::startLng = startLng;
        Ride::endLat = endLat;
        Ride::endLng = endLng;
        Ride::riderType = riderType;
    }

    // Copy constructor
    Ride(const Ride & otherRide){
        rideID = otherRide.rideID;
        rideableType = otherRide.rideableType;
        startTimeDate = otherRide.startTimeDate;
        endTimeDate = otherRide.endTimeDate;
        startStation = otherRide.startStation;
        endStation = otherRide.endStation;
        startLat = otherRide.startLat;
        startLng = otherRide.startLng;
        endLat = otherRide.endLat;
        endLng = otherRide.endLng;
        riderType = otherRide.riderType;
    }

    // Getter methods
    string getID(){return rideID;}
    string getRideableType(){return rideableType;}
    string getStartTimeDate(){return startTimeDate;}
    string getEndTimeDate(){return endTimeDate;}
    string getStartStation(){return startStation;}
    string getEndStation(){return endStation;}
    long double getStartLat(){return startLat;}
    long double getStartLng(){return startLng;}
    long double getEndLat(){return endLat;}
    long double getEndLng(){return endLng;}
    string getRiderType(){return riderType;}

private:
    // Private data members
    string rideID;
    string rideableType;
    string startTimeDate;
    string endTimeDate;
    string startStation;
    string endStation;
    long double startLat;
    long double startLng;
    long double endLat;
    long double endLng;
    string riderType;
};

// Utility functions getting distant between two map points
// Attribution: https://www.geeksforgeeks.org/program-distance-two-points-earth/
// converting degrees to radians
long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                      pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
}

// Funtion for reading from datafile
void readDatafile(const string datafile, vector <Ride> & Rides){
    // Read from datafile into a vector of classes
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open(datafile);                // Open datafile
    assert( inStream.fail() == false );     // Ensure file open worked

    // Clear the vector in case it is used previously.
    Rides.clear();

    vector <string> row; // Store words in a row
    string line, word;
    getline(inStream, line, '\n'); // To ignore the datafile field header

    // Keep repeating while the file yields a line
    while (getline(inStream, line, '\n')){
        row.clear();
        stringstream s(line);
        while (getline(s,word, ',')){
            if (word.length() == 0){ // If word is empty (unclean data)
                row.push_back("0");
            }
            else {
                row.push_back(word);
            }
        }

        // Create a Ride object with given values from row and push it into existing Rides vector
        Ride r (row[0], row[1], row[2], row[3], row[4], row[5], stold(row[6]), stold(row[7]), stold(row[8]), stold(row[9]), row[10]);
        Rides.push_back(r);
    }

    // Close the datafile
    inStream.close();
}

// Function for selecting datafile, display total rides and clean data
void selectDatafile(vector <Ride> & Rides){
    int selection;
    string datafile;
    vector <unsigned long> missingData; // Vector that stores the indices of objects with missing data

    cout << "Select datafile:" << endl
    << "1. Small subset of data with 14 rides to help create your program" << endl
    << "2. Week day vs weekend rides" << endl
    << "3. All September 2021 data (not tested in Zybooks)" << endl
    << "Your selection--> ";
    cin >> selection;

    // Assign datafile depending on user selection
    if (selection == 1){ datafile = "divvyridesampledata.csv";}
    if (selection == 2){ datafile = "weekdayweekend.csv";}
    if (selection == 3){ datafile = "all_divvy_rides_september.csv";}

    readDatafile(datafile, Rides);
    unsigned long length = Rides.size(); // Stores the original length of the vector so the subsequent loop isn't affected when elements are deleted

    for (unsigned long i = 0; i < length; ++i){

        // If any data is missing, then add the index of this object to the vector missingData
        if((Rides.at(i).getID() == "0") ||
           (Rides.at(i).getRideableType() == "0") ||
           (Rides.at(i).getStartTimeDate() == "0") ||
           (Rides.at(i).getEndTimeDate() == "0") ||
           (Rides.at(i).getStartStation() == "0") ||
           (Rides.at(i).getEndStation() == "0") ||
           (Rides.at(i).getStartLat() == 0) ||
           (Rides.at(i).getStartLng()== 0) ||
           (Rides.at(i).getEndLat() == 0) ||
           (Rides.at(i).getEndLng() == 0) ||
           (Rides.at(i).getRiderType() == "0")){
            missingData.push_back(i);
        }
    }
    int rectifier = 0; // Deleting elements in a vector by index becomes difficult when the length of the vector changes after every element is deleted.
                       // So we introduce a rectifier variable that will allow us to delete only the elements required.

    // Iterate through missingData and delete the elements of Rides whose indices are found in missingData
    for (long unsigned int i = 0; i < missingData.size(); ++i){
        Rides.erase(Rides.begin() + missingData.at(i) - rectifier);
        rectifier++;
    }

    cout << "Total # of trips found in datafile: " << Rides.size() + missingData.size() << endl
    << "Total # of trips in clean data: " << Rides.size() << endl;

}

// Function for displaying overall trip information
void displayOverall(vector <Ride> Rides){
    int longestTripIndex = 0;
    long double totalMiles = 0;
    long double currentTripLength, longestTripLength;

    // Iterate through vector Rides to find the longest trip length and total miles travelled
    for (long unsigned int i = 0; i < Rides.size(); ++i){
        Ride currentTrip = Rides.at(i);
        currentTripLength = distance(currentTrip.getStartLat(), currentTrip.getStartLng(), currentTrip.getEndLat(), currentTrip.getEndLng());
        longestTripLength = distance(Rides.at(longestTripIndex).getStartLat(), Rides.at(longestTripIndex).getStartLng(), Rides.at(longestTripIndex).getEndLat(), Rides.at(longestTripIndex).getEndLng());

        if (currentTripLength > longestTripLength){
            longestTripIndex = i;
        }
        totalMiles += currentTripLength;
    }

    cout << "Total # of miles traveled: " << fixed << setprecision(0) << totalMiles << endl
    << "Average length of trips in miles: " << fixed << setprecision(1) << totalMiles / Rides.size() << endl << endl
    << "Longest trip information below: " << endl
    << "-------------------------------" << endl
    << "Trip ID: " << Rides.at(longestTripIndex).getID() << endl
    << "Trip start location: " << Rides.at(longestTripIndex).getStartStation() << endl
    << "Trip end location: " << Rides.at(longestTripIndex).getEndStation() << endl
    << "Trip distance in miles: " << distance(Rides.at(longestTripIndex).getStartLat(), Rides.at(longestTripIndex).getStartLng(), Rides.at(longestTripIndex).getEndLat(), Rides.at(longestTripIndex).getEndLng()) <<  endl;
}

// Function for displaying percentage of members vs casual riders
void displayPercentage( vector <Ride> Rides){
    double memberTotal = 0;
    double casualTotal = 0;

    // Calculate total members and casual riders
    for (long unsigned int i = 0; i < Rides.size(); ++i){
        if (Rides.at(i).getRiderType() == "member\r"){
            memberTotal++;
        }
        else {
            casualTotal++;
        }
    }
    cout << "Casual Rider Percentage: " << fixed << setprecision(1) << (casualTotal / Rides.size()) * 100 << "%" << endl
         << "Member Rider Percentage: " << fixed << setprecision(1) << (memberTotal / Rides.size()) * 100 << "%" << endl;
}

// Function for displaying weekday vs weekend usage
void displayWeekdayVsWeekend(vector <Ride> Rides){
    int selection;
    double largestNumberOfRides = 0;
    vector <int> weekends = {4,5,11,12,18,19,25,26}; // Stores all the weekends in September
    bool isWeekend = false;
    vector <int> ridesPerHourWeekday (24,0);
    vector <int> ridesPerHourWeekend (24,0);

    cout << "Select type of display:" << endl
         << "1. Counts of rides per hour in the day" << endl
         << "2. Proportional 50 column graph with @ for weekday and + for weekend" << endl
         << "Your selection--> ";
    cin >> selection;

    // Loop through Rides vector to log rides per hour for weekday and weekend
    for (long unsigned int i = 0; i < Rides.size(); ++i){
        // This expression extracts the hour from startTimeDate and returns it as an integer value
        int hour = stoi(Rides.at(i).getStartTimeDate().substr(9,Rides.at(i).getStartTimeDate().find(':') - 9));
        // Update the values based on whether it's a weekday or weekend
        if (Rides.at(i).getStartTimeDate().at(2) == '1'){
            ridesPerHourWeekday.at(hour)++;
        }
        else {
            ridesPerHourWeekend.at(hour)++;
        }
    }

    // Loop through both weekend and weekday vectors and update largestNumberOfRides accordingly
    for (int i = 0; i < 24; ++i){
        if (ridesPerHourWeekday.at(i) > largestNumberOfRides){
            largestNumberOfRides = ridesPerHourWeekday.at(i);
        }
        if (ridesPerHourWeekend.at(i) > largestNumberOfRides){
            largestNumberOfRides = ridesPerHourWeekend.at(i);
        }
    }

    if (selection == 1){
        cout << "LargestNumberOfRides is: " << largestNumberOfRides << endl;
        cout << "Rides per hour for weekday and weekend:" << endl;

        // Display table
        for (int i = 0; i < 24; ++i){
            cout << i << ":\t" << ridesPerHourWeekday.at(i) << "\t" << ridesPerHourWeekend.at(i) << endl;
        }
    }

    else { // Display ASCII graph
        for (int i = 0; i < 24; ++i){
            cout << i << ":\t";
            for (int j = 0; j < trunc((ridesPerHourWeekday.at(i) / largestNumberOfRides) * 50) ; ++j){ // trunc allows us to convert double type literals into the
                cout << "@";                                                                              // greatest int value less than or equal to our current value
            }
            cout << endl << "\t";
            for (int j = 0; j < trunc((ridesPerHourWeekend.at(i) / largestNumberOfRides) * 50) ; ++j){
                cout << "+";
            }
            cout << endl;
        }
    }

}

// Function for finding the closest station
void findClosestStation(vector <Ride> Rides){
    long double latitude;
    long double longitude;
    long double currentDistance;
    long double closestDistance;
    int closestStationIndex = 0;


    cout << "Input latitude and longitude of the home: ";
    cin >> latitude >> longitude;
    streamsize ss = cout.precision(); // Captures original precision value to be reverted to later
    cout << fixed << setprecision(1) << "You entered: " << latitude << " for latitude and " << longitude << " for longitude" << endl;

    // Iterate through Rides vector to find the shortest distance between given coordinates and a Divvy station
    for ( long unsigned int i = 0; i < Rides.size(); ++i){
        currentDistance = distance(latitude,longitude,Rides.at(i).getStartLat(), Rides.at(i).getStartLng());
        closestDistance = distance(latitude,longitude,Rides.at(closestStationIndex).getStartLat(), Rides.at(closestStationIndex).getStartLng());
        if ( currentDistance < closestDistance){
            closestStationIndex = i;
        }
    }
    cout << fixed << setprecision(ss) << "Closest Divvy station is: " << Rides.at(closestStationIndex).getStartStation() << " at " << Rides.at(closestStationIndex).getStartLat() << ", " << Rides.at(closestStationIndex).getStartLng() << ", ";
    cout << fixed << setprecision(1) << closestDistance << " miles away." << endl;
}

// Function to display main menu
void mainMenu(){
    cout << endl << "Select a menu option:" << endl
         << "1. Select datafile, display rides totals and clean data" << endl
         << "2. Display overall trip information" << endl
         << "3. Display percentage of members vs. casual riders" << endl
         << "4. Display weekday vs weekend usage" << endl
         << "5. Extra Credit: find closest station" << endl
         << "6. Exit" << endl
         << "Your choice --> ";

}

int main() {
    bool checkFor1 = true;
    int choice = 0;
    vector <Ride> AllRides;

    cout << "Analyze Divvy bike ride information using September trip data." << endl
    << "First select option 1 to read and clean the data." << endl;

    //Main loop
    while (choice != 6){
        mainMenu();
        cin >> choice;

        // Calls the corresponding function based on player's choice.
        if (choice == 1){
            checkFor1 = false;
            selectDatafile(AllRides);
        }
        else {
            if (checkFor1) {
                cout << "First read in data by selecting menu option 1" << endl;
                continue;
            }
        }
        if (choice == 2){ displayOverall(AllRides);}
        if (choice == 3){ displayPercentage(AllRides);}
        if (choice == 4){ displayWeekdayVsWeekend(AllRides);}
        if (choice == 5){ findClosestStation(AllRides);}
    }

    return 0;
}