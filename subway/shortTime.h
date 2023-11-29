#include "station.h"
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

void shortTime(string start, unordered_map<string, int>& d, unordered_map<string, Station>& station) //객체의 역 이름 넣기
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
