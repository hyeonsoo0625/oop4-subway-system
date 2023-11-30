#include "station.h"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

stack<Station> shortTime(string start, unordered_map<string, double>& d, unordered_map<string, Station>& stations, string end) //객체의 역 이름 넣기
{
    priority_queue<pair<double, string>>pq; // 시간, 이름
    unordered_map<string, Station> previous; // 이전 역 저장

    pq.push({ 0,start }); //시작 -> 시작, 출발 id
    d[start] = 0;

    while (!pq.empty()) {
        double time = -pq.top().first; //현재 노드까지의 비용
        string now = pq.top().second; // 현재 노드
        pq.pop();

        if (d[now] < time) // 이미 최단경로를 체크한 노드인 경우 패스
            continue;
        for (int i = 0; i < stations[now].getNeighbor().size(); i++) {
            double cost = time + stations[now].getNeighbor()[i].second.first;
            string next = stations[now].getNeighbor()[i].first.getName();

            if (cost < d[next]) {
                d[next] = cost;
                pq.push(make_pair(-cost, next));
                previous[next] = stations[now];
            }
        }
    }

    //경로 추적
    stack<Station> route;
    for (Station station = stations[end]; station.getName() != start; station = previous[station.getName()]) {
        route.push(station);
    }
    route.push(stations[start]);

    return route;
}
