/*
Jacobo Soffer Levy
A01028653
Hash map implementation
Modified: 29/05/21
*/
#ifndef _MAP_H
#define _MAP_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include "map_node.h"
#include "ip.h"

template<class T>
class Map {
public:
    // Constructor. Takes collision handling technique
    // as first argument (defaults to quadratic probe),
    // table size as second argument (defaults to 7)
    Map(int size = 7);
    // Add a key value pair to the map.
    void addAt(Ip, T);
    // Returns an element from the map. Takes the key as
    // an argument. If element does not exist
    // invalid_argument is thrown
    T& at(Ip);
    // Checks if a key exists on the map
    bool exists(Ip);
    // Removes a key value pair from the map.
    void remove(Ip);
    // Returns the number of collisions in the table
    int getCollisions();
private:
    int find(Ip);
    std::vector<MapNode<T> > data;
    int size;
    int maxSize;
    int collisions;
};

template<class T>
Map<T>::Map(int size) : maxSize(size), size(0), collisions(0) {
    data = std::vector<MapNode<T> >(maxSize);
}

template<class T>
void Map<T>::addAt(Ip key, T value) {
    if (size == maxSize) {
        throw std::out_of_range("Map is full");
    }
    int hashVal = key.getWeight();
    MapNode<T> node = data.at(hashVal);
    if (!node.taken()) {
        node.setData(value);
        node.setKey(key);
        data.at(hashVal) = node;
        return;
    }
    int i = 1;
    int currentHash = (hashVal + i * i) % maxSize;
    MapNode<T> currentNode = data.at(currentHash);
    while (currentNode.taken()) {
        i++;
        currentHash = (hashVal + i * i) % maxSize;
        currentNode = data.at(currentHash);
    }
    currentNode.setData(value);
    currentNode.setKey(key);
    node.overflow.push_back(currentHash);
    data.at(currentHash) = currentNode;
    data.at(hashVal) = node;
    size++;
    collisions++;
}

template<class T>
int Map<T>::find(Ip key) {
    int hashVal = key.getWeight();
    MapNode<T> node = data.at(hashVal);
    if (node.taken()) {
        if (node.getKey() == key) {
            return hashVal;
        }
        std::vector<int> others = node.overflow;
        for (int i = 0; i < others.size(); i++) {
            // It's safe to assume these nodes have
            // a value
            if (data.at(others[i]).getKey() == key) {
                return others[i];
            }
        }
        return -1;
    }
    return -1;
}

template<class T>
bool Map<T>::exists(Ip key) {
    int pos = find(key);
    return pos != -1;
}

template<class T>
T& Map<T>::at(Ip key) {
    int pos = find(key);
    if (pos == -1) {
        throw std::invalid_argument("Element does not exist");
    }
    return data.at(pos).getData();
}

template<class T>
void Map<T>::remove(Ip key) {
    int pos = find(key);
    if (pos == -1) {
        throw std::invalid_argument("Element does not exist");
    }
    int hashVal = key.getWeight();
    if (pos != hashVal) {
        MapNode<T> node = data.at(hashVal);
        std::vector<int> others = node.overflow;
        int otherPos;
        for (int i = 0; i < others.size(); i++) {
            if (others[i] == pos) {
                otherPos = i;
            }
        }
        node.overflow.erase(node.overflow.begin() + otherPos);
        data.at(hashVal) = node;
    }
    data.at(pos).clearData();
    size--;
}

template<class T>
int Map<T>::getCollisions() {
    return collisions;
}

#endif