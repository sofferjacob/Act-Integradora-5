#include <iostream>
#include <fstream>
#include "util/get_input.h"
#include "graph.h"

using namespace std;

int main() {
    cout << "Act. Integradora 5" << endl;
    cout << "Jacobo Soffer | A01028653" << endl;
    cout << "Enter 'q' at any prompt to exit the program" << endl;
    cout << "Loading graph..." << endl;
    Graph graph("bitacoraGrafos.txt");
    while (true) {
        bool exit = false;
        Ip input = getInput(exit);
        if (exit) {
            break;
        }
        if (!graph.data.exists(input)) {
            cout << "Error: Address not found in graph" << endl;
            continue;
        }
        vector<Ip> adj = graph.data.at(input);
        cout << "Adjacent nodes:" << endl;
        ofstream file("results.txt");
        file << "IP: " << input.getAddress() << endl;
        file << "Adjacent nodes:" << endl;
        for (int i = 0; i < adj.size(); i++) {
            file << "#" << (i + 1) << ": " << adj[i].getAddress() << endl;
            cout << "#" << (i + 1) << ": " << adj[i].getAddress() << endl;
        }
        file.close();
    }
    return 0;
}