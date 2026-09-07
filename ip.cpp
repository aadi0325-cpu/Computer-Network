#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct IPv4 {
    int octets[4];
};

bool isValidIPv4(const string& ipStr, IPv4& ipObj) {
    stringstream ss(ipStr);
    string token;
    int count = 0;

    while (getline(ss, token, '.')) {
        if (count >= 4 || token.empty()) return false;

        for (char c : token) {
            if (!isdigit(c)) return false;
        }

        int val = stoi(token);
        if (val < 0 || val > 255) return false;

        if (token.length() > 1 && token[0] == '0') return false;

        ipObj.octets[count] = val;
        count++;
    }

    return count == 4;
}

int main() {
    string inputIp;
    cout << "Enter an IPv4 address : ";
    cin >> inputIp;

    IPv4 ip;
    if (!isValidIPv4(inputIp, ip)) {
        cout << "\nError: Invalid IPv4 address format or range!" << endl;
        return 1;
    }

    int firstOctet = ip.octets[0];
    char ipClass = ' ';
    string subnetMask = "";
    string networkId = "";
    string hostId = "";

    if (firstOctet >= 1 && firstOctet <= 126) {
        ipClass = 'A';
        subnetMask = "255.0.0.0";
        networkId = to_string(ip.octets[0]) + ".0.0.0";
        hostId = "0." + to_string(ip.octets[1]) + "." + to_string(ip.octets[2]) + "." + to_string(ip.octets[3]);
    } 
    else if (firstOctet == 127) {
        ipClass = 'A';
       
        subnetMask = "255.0.0.0";
        networkId = "127.0.0.0";
        hostId = "0." + to_string(ip.octets[1]) + "." + to_string(ip.octets[2]) + "." + to_string(ip.octets[3]);
    }
    else if (firstOctet >= 128 && firstOctet <= 191) {
        ipClass = 'B';
        subnetMask = "255.255.0.0";
        networkId = to_string(ip.octets[0]) + "." + to_string(ip.octets[1]) + ".0.0";
        hostId = "0.0." + to_string(ip.octets[2]) + "." + to_string(ip.octets[3]);
    } 
    else if (firstOctet >= 192 && firstOctet <= 223) {
        ipClass = 'C';
        subnetMask = "255.255.255.0";
        networkId = to_string(ip.octets[0]) + "." + to_string(ip.octets[1]) + "." + to_string(ip.octets[2]) + ".0";
        hostId = "0.0.0." + to_string(ip.octets[3]);
    } 
    else if (firstOctet >= 224 && firstOctet <= 239) {
        ipClass = 'D';
    } 
    else if (firstOctet >= 240 && firstOctet <= 255) {
        ipClass = 'E';
    }

   
    cout << "Your IP Address is valid:   "  << endl;
    cout << "your address belongs to Class: " << ipClass << endl;

    if (ipClass == 'A' || ipClass == 'B' || ipClass == 'C') {
        cout << "Subnet Mask:   " << subnetMask << endl;
        cout << "Network address:    " << networkId << endl;
        cout << "Host address:       " << hostId << endl;
    } else {
        cout << "Subnet Mask:   N/A (Class " << ipClass << " is not used for standard host subnets)" << endl;
        cout << "Network ID:    N/A" << endl;
        cout << "Host ID:       N/A" << endl;
    }

    return 0;
}