#include <iostream>
using namespace std;

int main() {
    string word;
    int code;

    cout << "Enter word to be coded: ";
    cin >> word;
    cout << endl << "Enter code: ";
    cin >> code;

    for(int i = 0; i < word.size(); ++i){
        for(int j = 0; j < code; ++j){
            if( word[i] == 'z'){
                word[i] = 'a';
            }
            else{
                word[i]++;
            }
        }
    }
    cout << endl << word;
    return 0;
}
