/*
heap.h
Graph class declaration
Jacobo Soffer
A01028653
*/
#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include "util/ip.h"
#include "util/map.h"

class Graph {
private:
    int numNodes;
    int numEdges;
    // Parses a line and returns
    // the IP addresses
    void split(std::string line, std::vector<Ip>& res);
    // Parses a line containing numbers
    void split(std::string line, std::vector<int>& res);
public:
    // Default constructor
    // loadGraphList must be called before
    // using the object
    Graph();
    // Filename constructor
    // Takes the filename containing the graph
    // as the first argument.
    Graph(std::string);
    // Input stream constructor
    // Takes cin as the first argument for use with stdin redirection.
    Graph(std::istream&);
    // Adjacency list
    Map<std::vector<Ip> > data;
    // Loads the graph as an adj.list
    void loadGraphList(std::istream& input);
    // Returns a vector containing adj. nodes
    std::vector<Ip> getAdj(Ip);
};

#endif