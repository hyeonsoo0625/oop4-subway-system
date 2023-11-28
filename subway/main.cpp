#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <map>
using namespace std;

class Station {
private:
    string name;
    vector<pair<Station, pair<double, double>>> neighborStations;
    vector<int> lines;
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
    void addLine(int line) {
        lines.push_back(line);
    }
};
unordered_map<string, Station> station; //역 이름, 역 객체

unordered_map<string, int> d;

void dijkstra(string start) //객체의 역 이름 넣기
{
    priority_queue<pair<double, string>>pq; // 시간, 이름

    pq.push({ 0,start }); //시작 -> 시작, 출발 id
    d[start] = 0;

    while (!pq.empty()) {
        int time = -pq.top().first; //현재 노드까지의 비용
        string now = pq.top().second; // 현재 노드
        pq.pop();

        if (d[now] < time) // 이미 최단경로를 체크한 노드인 경우 패스
            continue;
        for (int i = 0; i < station[now].getNeighbor().size(); i++) {
            int cost = time + station[now].getNeighbor()[i].second.first;
            if (cost < d[station[now].getNeighbor()[i].first.getName()]) {
                d[station[now].getNeighbor()[i].first.getName()] = cost;
                pq.push(make_pair(-cost, station[now].getNeighbor()[i].first.getName()));
            }
        }
    }
}



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
    dijkstra(start);
    cout << "걸린 시간 : " << d[end];
}