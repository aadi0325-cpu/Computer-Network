#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

struct IPv4 {
    int octets[4];
};

bool isValidIPv4(const string& ipStr, IPv4& ipObj) {
    stringstream ss(ipStr);
    string token;
    int count = 0;

    while (getline(ss, token, '.')) {

        // Maximum 4 octets
        if (count >= 4 || token.empty())
            return false;

        // Check that every character is a digit
        for (char c : token) {
            if (!isdigit(static_cast<unsigned char>(c)))
                return false;
        }

        // Prevent numbers like 001, 025, etc.
        if (token.length() > 1 && token[0] == '0')
            return false;

        int val = stoi(token);

        // Each octet must be between 0 and 255
        if (val < 0 || val > 255)
            return false;

        ipObj.octets[count] = val;
        count++;
    }

    // IPv4 must contain exactly 4 octets
    return count == 4;
}

int main() {

    string inputIp;

    cout << "Enter an IPv4 address: ";
    cin >> inputIp;

    IPv4 ip;

    if (!isValidIPv4(inputIp, ip)) {
        cout << "\nError: Invalid IPv4 address format or range!"
             << endl;
        return 1;
    }

    int firstOctet = ip.octets[0];

    char ipClass = ' ';
    string subnetMask = "";
    string networkId = "";
    string hostId = "";

    // Class A
    if (firstOctet >= 1 && firstOctet <= 126) {

        ipClass = 'A';
        subnetMask = "255.0.0.0";

        networkId =
            to_string(ip.octets[0]) + ".0.0.0";

        hostId =
            "0." + to_string(ip.octets[1]) +
            "." + to_string(ip.octets[2]) +
            "." + to_string(ip.octets[3]);
    }

    // Loopback address 127.x.x.x
    else if (firstOctet == 127) {

        ipClass = 'A';
        subnetMask = "255.0.0.0";

        networkId = "127.0.0.0";

        hostId =
            "0." + to_string(ip.octets[1]) +
            "." + to_string(ip.octets[2]) +
            "." + to_string(ip.octets[3]);
    }

    // Class B
    else if (firstOctet >= 128 && firstOctet <= 191) {

        ipClass = 'B';
        subnetMask = "255.255.0.0";

        networkId =
            to_string(ip.octets[0]) + "." +
            to_string(ip.octets[1]) + ".0.0";

        hostId =
            "0.0." + to_string(ip.octets[2]) +
            "." + to_string(ip.octets[3]);
    }

    // Class C
    else if (firstOctet >= 192 && firstOctet <= 223) {

        ipClass = 'C';
        subnetMask = "255.255.255.0";

        networkId =
            to_string(ip.octets[0]) + "." +
            to_string(ip.octets[1]) + "." +
            to_string(ip.octets[2]) + ".0";

        hostId =
            "0.0.0." + to_string(ip.octets[3]);
    }

    // Class D
    else if (firstOctet >= 224 && firstOctet <= 239) {

        ipClass = 'D';
    }

    // Class E
    else if (firstOctet >= 240 && firstOctet <= 255) {

        ipClass = 'E';
    }

    // Display result
    cout << "\nYour IP Address is valid." << endl;

    cout << "Your address belongs to Class: "
         << ipClass << endl;

    if (ipClass == 'A' ||
        ipClass == 'B' ||
        ipClass == 'C') {

        cout << "Subnet Mask: "
             << subnetMask << endl;

        cout << "Network Address: "
             << networkId << endl;

        cout << "Host Address: "
             << hostId << endl;
    }
    else {

        cout << "Subnet Mask: N/A "
             << "(Class " << ipClass
             << " is not used for standard host subnets)"
             << endl;

        cout << "Network ID: N/A" << endl;

        cout << "Host ID: N/A" << endl;
    }

    return 0;
}