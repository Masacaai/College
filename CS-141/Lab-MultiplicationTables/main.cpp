#include <iostream>
using namespace std;

int main() {

    for ( int i = 1 ; i <= 10; i++) {
        if (i != 10) {
            cout << " ";
        }
        for (int j = 1; j <= 10; j++) {
            cout << i*j;
            if ( (i*(j+1)) / 10 == 0 ) {
                if ( i*(j+1) == 10 ) {
                    cout << "  ";
                }
                else {
                    cout << "   ";
                }
            }
            else if ( i*(j+1) / 100 == 0 ) {
                cout << "  ";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
