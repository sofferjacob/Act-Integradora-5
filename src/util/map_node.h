#ifndef _MAP_NODE_H
#define _MAP_NODE_H

#include <vector>
#include "ip.h"

template<class T>
class MapNode {
public:
    MapNode();
    T& getData();
    void setData(T);
    void clearData();
    std::vector<int> overflow;
    bool taken();
    Ip getKey();
    void setKey(Ip);
private:
    T data;
    Ip key;
    bool hasData;
};

template<class T>
MapNode<T>::MapNode() : hasData(false) {}

template<class T>
T& MapNode<T>::getData() {
    return data;
}

template<class T>
void MapNode<T>::setData(T d) {
    if (hasData) throw "Node taken";
    data = d;
    hasData = true;
}

template<class T>
void MapNode<T>::clearData() {
    hasData = false;
}

template<class T>
bool MapNode<T>::taken() {
    return hasData;
}

template<class T>
Ip MapNode<T>::getKey() {
    if (!hasData) throw "Invalid operation: Empty node";
    return key;
}

template<class T>
void MapNode<T>::setKey(Ip k) {
    key = k;
}

#endif