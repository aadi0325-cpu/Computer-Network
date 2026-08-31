#include <iostream>
#include <string>

using namespace std;

// Function to perform bitwise XOR operation between two binary strings
string performXOR(string a, string b) {
    string result = "";
    // Start from index 1 because the leading bit of the divisor always matches
    for (size_t i = 1; i < b.length(); i++) {
        if (a[i] == b[i]) {
            result += "0";
        } else {
            result += "1";
        }
    }
    return result;
}

// Function to perform Modulo-2 Division to calculate CRC remainder
string calculateCRC(string data, string generator) {
    int generatorLen = generator.length();
    
    // Extract the first block of data equal to the generator length
    string currentBlock = data.substr(0, generatorLen);
    
    int nextBitIndex = generatorLen;
    int dataLen = data.length();

    while (nextBitIndex <= dataLen) {
        // If the leading bit is 1, XOR with the generator
        if (currentBlock[0] == '1') {
            currentBlock = performXOR(generator, currentBlock);
        } else {
            // If leading bit is 0, XOR with a string of zeros
            string zeroStr(generatorLen, '0');
            currentBlock = performXOR(zeroStr, currentBlock);
        }

        // Pull down the next bit from the data string if available
        if (nextBitIndex < dataLen) {
            currentBlock += data[nextBitIndex];
        }
        nextBitIndex++;
    }
    
    return currentBlock; // This holds the final remainder
}

int main() {
    string message, generator;

    // 1. Inputs from the user
    cout << "Enter the binary message : ";
    cin >> message;
    cout << "Enter the generator divisor : ";
    cin >> generator;

    int genLen = generator.length();

    // --- SENDER SIDE ---
    // Append (generator length - 1) zeros to the original message
    string paddedMessage = message + string(genLen - 1, '0');
    
    // Calculate the CRC remainder bits
    string crcRemainder = calculateCRC(paddedMessage, generator);
    
    // Append the remainder to the original message to form the transmitted codeword
    string transmittedCodeword = message + crcRemainder;

    cout << "\n--- Sender Side ---" << endl;
    cout << "Padded Message: " << paddedMessage << endl;
    cout << "Calculated CRC Remainder: " << crcRemainder << endl;
    cout << "Transmitted Codeword: " << transmittedCodeword << endl;

    // --- RECEIVER SIDE ---
    string receivedCodeword;
    cout << "\n--- Receiver Side ---" << endl;
    cout << "Enter the received codeword: ";
    cin >> receivedCodeword;

    // Run the modulo-2 division on the received block using the same generator
    string receiverCheck = calculateCRC(receivedCodeword, generator);
    cout << "Receiver Side Remainder: " << receiverCheck << endl;

    // Check if the resulting remainder consists entirely of zeros
    bool errorDetected = false;
    for (char bit : receiverCheck) {
        if (bit == '1') {
            errorDetected = true;
            break;
        }
    }

    if (errorDetected) {
        cout << "STATUS: Error detected in data transmission! (Discard Frame)" << endl;
    } else {
        cout << "STATUS: No errors detected. Data received successfully." << endl;
    }

}