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
    unordered_map<string, int> d;
    unordered_map<string, Station> station; //역 이름, 역 객체

    // 역 정보 정리
    ifstream stationInfo("subway_information.txt");
    string stationl;
    while (getline(stationInfo, stationl)) {// id:역이름
        vector<string> v = split(stationl, ':');
        int id = stoi(v[0]);
        string name = v[1];
        station[name] = Station(name);
        d[name] = 1e9;
    }


    // 역 간 정보 정리
    ifstream in("subway_20224527.txt");
    string line;

    while (getline(in, line)) {// 역:역:시간:거리
        vector<string> v = split(line, ':');
        string name1 = v[0];
        string name2 = v[1];
        double time = stod(v[2]);
        double distance = stod(v[3]);

        station[name1].addNeighbor(station[name2], distance, time);
        station[name2].addNeighbor(station[name1], distance, time);

    }
    shortTime(start, d, station);
    cout << "걸린 시간 : " << d[end];
}