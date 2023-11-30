#pragma once
#include <iostream>
#include <vector>
using namespace std;


class Station {
private:
    string name;
    vector<pair<Station, pair<double, double>>> neighborStations;
    int line;
public:
    Station(string name) {
        this->name = name;
    }
    Station() {}
    string getName() {
        return name;
    }
    vector<pair<Station, pair<double, double>>> getNeighbor() {
        return neighborStations;
    }
    void addNeighbor(Station station, double distance, double time) {
        neighborStations.push_back(make_pair(station, make_pair(time, distance)));
    }
    void setLine(int lineNum) {
        line = lineNum;
    }
};