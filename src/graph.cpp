#include <stdexcept>
#include <sstream>
#include <set>
#include <fstream>
#include <iostream>
#include "graph.h"

using namespace std;

Graph::Graph() {}

Graph::Graph(std::istream& input) {
    loadGraphList(input);
}

Graph::Graph(std::string filename) {
    ifstream file(filename);
    if (!file.good()) {
        file.close();
        throw invalid_argument("File not found");
    }
    loadGraphList(file);
    file.close();
}

void Graph::loadGraphList(std::istream& input) {
    std::string line;
    getline(input, line);
    vector<int> meta;
    split(line, meta);
    numNodes = meta[0];
    numEdges = meta[1];
    data = Map<vector<Ip> >(numNodes + 20);
    for (int i = 0; i < numNodes; i++) {
        getline(input, line);
        data.addAt(Ip(line, false), std::vector<Ip>());
    }
    while (std::getline(input, line)) {
        vector<Ip> res;
        split(line, res);
        data.at(res[0]).push_back(res[1]);
    }
}

void Graph::split(std::string line, std::vector<Ip>& res) {
    int strPos = line.find(" ");
    int lastPos = 0;
    vector<string> parts;
    while (strPos != std::string::npos) {
        parts.push_back(line.substr(lastPos, strPos - lastPos));
        lastPos = strPos + 1;
        strPos = line.find(" ", lastPos);
    }
    parts.push_back(line.substr(lastPos, line.size() - lastPos));
    res.push_back(Ip(parts[3], -1));
    res.push_back(Ip(parts[4], -1));
}

void Graph::split(std::string line, std::vector<int>& res) {
    int strPos = line.find(" ");
    int lastPos = 0;
    while (strPos != std::string::npos) {
        res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
        lastPos = strPos + 1;
        strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

vector<Ip> Graph::getAdj(Ip key) {
    return data.at(key);
}