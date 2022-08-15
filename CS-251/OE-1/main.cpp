#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Reads in data from file and stores it in corresponding vectors
void read(string file, string & header, vector<string> & stockName, vector<double> & stockPrice) {
    string buffer;
    ifstream infile(file);

    if (infile.fail()) {
        cout << "Error: unable to open '" << file << "'" << endl;
    } else {
        getline(infile, header); // Gets the header text and stores it in header

        while(getline(infile, buffer)) {
            stockName.push_back(buffer.substr(0,buffer.find(",")));
            stockPrice.push_back(stod(buffer.substr(buffer.find(",") + 1)));
        }
        cout << endl << "Data loaded." << endl;
    }
}

// Calculates mean of all stock prices
double calcMean(vector<double> & prices) {
    double mean;
    double sum = 0.0;

    for (int i = 0; i < prices.size(); ++i) {
        sum += prices.at(i);
    }
    mean = sum / prices.size();
    return mean;
}

// Prints all stocks with prices above a given limit
void aboveLimit(vector<string> stockName, vector<double> stockPrice, double limit) {
    cout << endl;
    for (int i = 0; i < stockPrice.size(); ++i) {
        if (stockPrice.at(i) > limit) {
            cout << stockName.at(i) << ": " << stockPrice.at(i) << endl;
        }
    }
}

// Prints all stocks with prices below a given limit
void belowLimit(vector<string> stockName, vector<double> stockPrice, double limit) {
    cout << endl;
    for (int i = 0; i < stockPrice.size(); ++i) {
        if (stockPrice.at(i) < limit) {
            cout << stockName.at(i) << ": " << stockPrice.at(i) << endl;
        }
    }
}

// Prints out all company names in alphabetical order
void alphaOrder(vector<string> stockName, vector<double> stockPrice) {
    cout << endl;
    while (stockName.size() > 0) {
        int lowIndex = 0;
        for (int i = 1; i < stockName.size(); ++i) {
            if (stockName.at(i) < stockName.at(lowIndex)) {
                lowIndex = i;
            }
        }
        cout << stockName.at(lowIndex) << ": " << stockPrice.at(lowIndex) << endl;
        stockName.erase(stockName.begin() + lowIndex);
    }
}

// Displays the records
void display(vector<string> stockName, vector<double> stockPrice) {
    cout << endl;
    for (int i = 0; i < stockName.size(); ++i) {
        cout << stockName.at(i) << ": " << stockPrice.at(i) << endl;
    }
}

int main() {
    string headerText;
    string command, arg;
    double limit, mean;
    vector<string> stockName;
    vector<double> stockPrice;

    cout << "Welcome to the stock tracker!" << endl;
    while (true) {
        cout << endl;
        cout << "Available commands:" << endl
             << "read <filename>       - Reads data from the file given as argument." << endl
             << "display alpha         - Displays stocks in alphabetical order." << endl
             << "display normal        - Displays stocks in the order they are in the datafile" << endl
             << "display above <limit> - Displays stocks with prices above the limit given as argument." << endl
             << "display below <limit> - Displays stocks with prices below the limit given as argument." << endl
             << "display mean          - Displays the mean price of all stocks." << endl << endl;
        cout << "Enter command or # to exit: ";
        cin >> command;

        if (command == "read") {
            cin >> arg;
            stockName.clear();
            stockPrice.clear();
            read(arg, headerText, stockName, stockPrice);
        }
        else if (command == "display") {
            cin >> arg;
            if(stockName.size() == 0) {
                cout << "Please read a file!" << endl;
            }
            else {
                if (arg == "alpha") {
                    alphaOrder(stockName, stockPrice);
                }
                else if (arg == "normal") {
                    display(stockName, stockPrice);
                }
                else if (arg == "above") {
                    cin >> limit;
                    aboveLimit(stockName, stockPrice, limit);
                }
                else if (arg == "below") {
                    cin >> limit;
                    belowLimit(stockName, stockPrice, limit);
                }
                else if (arg == "mean") {
                    cout << "Mean: " << calcMean(stockPrice) << endl;
                }
                else {
                cout << "Please enter a valid option!" << endl;
                }
            }
        }
        else if (command == "#") {
            break;
        }
        else {
            cout << "Please enter a valid option!" << endl;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
