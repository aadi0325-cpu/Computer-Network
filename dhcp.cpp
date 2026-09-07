#include <iostream>
#include <string>

using namespace std;

int main()
{
    string client[10];
    string ip[10];

    int n;

    cout << "Enter number of clients: ";
    cin >> n;

    if (n > 10)
    {
        cout << "Maximum 10 clients allowed." << endl;
        return 0;
    }

    // DHCP IP pool
    int startIP = 100;

    cout << "\nDHCP Server Started..." << endl;
    cout << "IP Pool: 192.168.1.100 - 192.168.1.109" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Client " << i + 1 << " Name: ";
        cin >> client[i];

        // Automatically assign IP
        ip[i] = "192.168.1." + to_string(startIP + i);

        cout << "IP Address Assigned: " << ip[i] << endl;
    }

    // Display DHCP table
    cout << "\n------ DHCP Allocation Table ------" << endl;

    cout << "Client\t\tIP Address" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << client[i] << "\t\t" << ip[i] << endl;
    }

    return 0;
}