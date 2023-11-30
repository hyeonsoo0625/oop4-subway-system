#include "station.h"
#include "shortTime.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;




vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

int main() {
    string start, end;
    int a;
    cout << "출발지 : ";
    cin >> start;
    cout << "도착지 : ";
    cin >> end;
    unordered_map<string, double> d;
    unordered_map<string, Station> station; //역 이름, 역 객체

    // 역 간 정보 정리
    ifstream in("subway_20224527.txt");
    string line;
    string name1;
    string name2;
    int lineNum;
    while (getline(in, line)) {// 역:역:시간:거리
        vector<string> v = split(line, ':');
        lineNum = stoi(v[0]);
        name1 = v[1];
        name2 = v[2];
        if (station.find(name1) == station.end()) {
            station[name1] = Station(name1);
            station[name1].setLine(lineNum);
        }
        if (station.find(name2) == station.end()) {
            station[name2] = Station(name2);
        }
        double time = stod(v[3]);
        double distance = stod(v[4]);

        station[name1].addNeighbor(station[name2], distance, time);
        station[name2].addNeighbor(station[name1], distance, time);
        d[name1] = 1e9;
    }
    d[name2] = 1e9;
    vector<Station> route = shortTime(start, d, station, end);
    for (Station station : route) {
        cout << station.getName()<<endl;
    }
    cout << "걸린 시간 : " << d[end];
}