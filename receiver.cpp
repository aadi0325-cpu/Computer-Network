#include <iostream>
#include <string>
using namespace std;

string xorOperation(string a, string b)
{
    string result = "";

    for (int i = 1; i < b.length(); i++)
    {
        if (a[i] == b[i])
            result += '0';
        else
            result += '1';
    }
    return result;
}

string mod2Division(string dividend, string divisor)
{
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);

    while (pick < dividend.length())
    {
        if (temp[0] == '1')
            temp = xorOperation(divisor, temp) + dividend[pick];
        else
            temp = xorOperation(string(divisor.length(), '0'), temp) + dividend[pick];

        pick++;
    }

    if (temp[0] == '1')
        temp = xorOperation(divisor, temp);
    else
        temp = xorOperation(string(divisor.length(), '0'), temp);

    return temp;
}

int main()
{
    string receivedData, generator;

    cout << "Enter Received Codeword: ";
    cin >> receivedData;

    cout << "Enter Generator: ";
    cin >> generator;

    string remainder = mod2Division(receivedData, generator);

    bool error = false;

    for (char bit : remainder)
    {
        if (bit != '0')
        {
            error = true;
            break;
        }
    }

    if (error)
        cout << "\nError Detected in Transmission!" << endl;
    else
        cout << "\nNo Error Detected. Data Accepted." << endl;

    return 0;
}