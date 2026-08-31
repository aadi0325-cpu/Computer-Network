#include <iostream>
#include <string>
using namespace std;

int main() {

    string input;
    int b[8];
\
    cout << "Enter 7-bit Hamming Code: ";
    cin >> input;

    if (input.length() != 7) {
        cout << "Please enter exactly 7 bits.";
        return 0;
    }

    for (int i = 1; i <= 7; i++) {
        if (input[i - 1] != '0' && input[i - 1] != '1') {
            cout << "Invalid input! Enter only 0 and 1.";
            return 0;
        }

        b[i] = input[i - 1] - '0';
    }

    int c1 = b[1] ^ b[3] ^ b[5] ^ b[7];
    int c2 = b[2] ^ b[3] ^ b[6] ^ b[7];
    int c4 = b[4] ^ b[5] ^ b[6] ^ b[7];

    int error = c1 + 2 * c2 + 4 * c4;

    cout << "\nInput Code: " << input;

    if (error == 0) {
        cout << "\nNo Error";
        cout << "\nCorrect Code: " << input;
    }
    else {
        cout << "\nError at position: " << error;

        b[error] ^= 1;

        cout << "\nCorrected Code: ";

        for (int i = 1; i <= 7; i++) {
            cout << b[i];
        }
    }

    return 0;
}
