#include "station.h"
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

vector<Station> shortTime(string start, unordered_map<string, double>& d, unordered_map<string, Station>& station, string end) //객체의 역 이름 넣기
{
    priority_queue<pair<double, string>>pq; // 시간, 이름

    pq.push({ 0,start }); //시작 -> 시작, 출발 id
    d[start] = 0;
    vector<Station> route;//경로 저장 변수
    bool dest = false;//경로 판단요소
    route.push_back(start);

    while (!pq.empty()) {
        double time = -pq.top().first; //현재 노드까지의 비용
        string now = pq.top().second; // 현재 노드
        Station lowcostnode;//경로 저장 변수
        pq.pop();

        if (now == end)
            dest = true;
        if (d[now] < time) // 이미 최단경로를 체크한 노드인 경우 패스
            continue;
        for (int i = 0; i < station[now].getNeighbor().size(); i++) {
            double cost = time + station[now].getNeighbor()[i].second.first;
            if (cost < d[station[now].getNeighbor()[i].first.getName()]) {
                d[station[now].getNeighbor()[i].first.getName()] = cost;
                pq.push(make_pair(-cost, station[now].getNeighbor()[i].first.getName()));
                lowcostnode = station[now].getNeighbor()[i].first;
            }
        }
        if (!dest)
            route.push_back(lowcostnode);
    }
    return route;
}