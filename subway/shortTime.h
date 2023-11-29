#include "station.h"
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

void shortTime(string start, unordered_map<string, int>& d, unordered_map<string, Station>& station) //��ü�� �� �̸� �ֱ�
{
    priority_queue<pair<double, string>>pq; // �ð�, �̸�

    pq.push({ 0,start }); //���� -> ����, ��� id
    d[start] = 0;

    while (!pq.empty()) {
        int time = -pq.top().first; //���� �������� ���
        string now = pq.top().second; // ���� ���
        pq.pop();

        if (d[now] < time) // �̹� �ִܰ�θ� üũ�� ����� ��� �н�
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
