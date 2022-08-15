#include <iostream>
using namespace std;

int main() {
    int month;
    int day;
    int numberOfDays;

    string MONTHS [] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (month = 0; month < 12; month++) {
        if (month == 1 ) {
            numberOfDays = 28;
        }
        else if ((month == 3) || (month == 5) || (month == 8) || (month == 10)) {
            numberOfDays = 30;
        }
        else {
            numberOfDays = 31;
        }
        cout << MONTHS[month] << endl;
        for (day = 1; day <= numberOfDays; day++) {
            cout << day << " ";
            if ((day % 7) == 0) {
                cout << endl;
            }
        }
        cout << endl << endl;
    }

    return 0;
}
