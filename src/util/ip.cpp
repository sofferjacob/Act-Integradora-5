/*
ip.cpp
IP class methods definition
Jacobo Soffer | A01028653
Modified: 10/05/21
*/
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "ip.h"

Ip::Ip() : address(""), weight(0) {}

Ip::Ip(std::string ip, bool hasPort) : weight(0) {
    setAddress(ip, hasPort);
}

std::string Ip::getAddress() {
    return address;
}

void Ip::setAddress(std::string ip, bool hasPort) {
    if (hasPort) {
        address = ip.substr(0, ip.find(":"));
    }
    else {
        address = ip;
    }
    int strPos = address.find(".");
    int lastPos = 0;
    while (strPos != std::string::npos) {
        octets.push_back(stoi(address.substr(lastPos, strPos - lastPos)));
        lastPos = strPos + 1;
        strPos = address.find(".", lastPos);
    }
    octets.push_back(stoi(address.substr(lastPos, address.length() - (lastPos))));
    if (octets.size() != 4) {
        throw std::invalid_argument("Invalid IP address");
    }
    int wPos4 = (octets[0] * 16) + ((2 * 255) + 1 + (4 * 255) + 1 + (8 * 255) + 1);
    int wPos3 = (octets[1] * 8) + ((2 * 255) + 1 + (4 * 255) + 1);
    int wPos2 = (octets[2] * 4) + ((255 * 2) + 1);
    int wPos1 = (octets[3] * 2);
    weight = wPos1 + wPos2 + wPos3 + wPos4;
}

std::vector<int> Ip::getOctets() {
    return octets;
}

int Ip::getWeight() {
    return weight;
}

bool Ip::operator >(const Ip& other) {
    return weight > other.weight;
}

bool Ip::operator >=(const Ip& other) {
    return weight >= other.weight;
}

bool Ip::operator <(const Ip& other) {
    return weight < other.weight;
}

bool Ip::operator <=(const Ip& other) {
    return weight <= other.weight;
}

bool Ip::operator ==(const Ip& other) {
    return address == other.address;
}

bool Ip::operator !=(const Ip& other) {
    return address != other.address;
}