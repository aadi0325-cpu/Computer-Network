#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Function to extract the first octet and determine the IP class
void findIPClass(const string& ipAddress) {
    stringstream ss(ipAddress);
    string firstOctetStr;
    
    // Read characters up to the first dot '.'
    if (getline(ss, firstOctetStr, '.')) {
        try {
            int firstOctet = stoi(firstOctetStr);
            
            // Check if the octet value is within the valid IPv4 range
            if (firstOctet < 0 || firstOctet > 255) {
                cout << "Invalid IP Address. First octet must be between 0 and 255." << endl;
                return;
            }

            // Determine the class based on standard networking ranges
            if (firstOctet >= 0 && firstOctet <= 127) {
                cout << "Class: A" << endl;
                if (firstOctet == 127) {
                    cout << "Note: 127.x.x.x is reserved for loopback testing." << endl;
                }
            } 
            else if (firstOctet >= 128 && firstOctet <= 191) {
                cout << "Class: B" << endl;
            } 
            else if (firstOctet >= 192 && firstOctet <= 223) {
                cout << "Class: C" << endl;
            } 
            else if (firstOctet >= 224 && firstOctet <= 239) {
                cout << "Class: D (Multicast)" << endl;
            } 
            else if (firstOctet >= 240 && firstOctet <= 255) {
                cout << "Class: E (Experimental)" << endl;
            }
        } 
        catch (...) {
            cout << "Invalid format. Ensure you enter numbers separated by dots." << endl;
        }
    } else {
        cout << "Invalid IP format." << endl;
    }
}

int main() {
    string ip;
    
    cout << "Enter an IPv4 address in dotted-decimal format (e.g., 192.168.1.1): ";
    cin >> ip;
    
    findIPClass(ip);
}