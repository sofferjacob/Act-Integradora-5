#include <iostream>
#include <string>
#include "get_input.h"

using namespace std;

Ip getInput(bool& exit) {
    string line;
    cout << "Enter IP address: ";
    cin >> line;
    try {
        if (line[0] == 'q') {
            exit = true;
            return Ip();
        }
        Ip res(line, false);
        return res;
    }
    catch (...) {
        cout << "Invalid IP address, try again." << endl;
        return getInput(exit);
    }
}