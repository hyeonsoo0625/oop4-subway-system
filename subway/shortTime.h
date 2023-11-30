#include "station.h"
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

vector<Station> shortTime(string start, unordered_map<string, double>& d, unordered_map<string, Station>& station, string end) //��ü�� �� �̸� �ֱ�
{
    priority_queue<pair<double, string>>pq; // �ð�, �̸�

    pq.push({ 0,start }); //���� -> ����, ��� id
    d[start] = 0;
    vector<Station> route;//��� ���� ����
    bool dest = false;//��� �Ǵܿ��
    route.push_back(start);

    while (!pq.empty()) {
        double time = -pq.top().first; //���� �������� ���
        string now = pq.top().second; // ���� ���
        Station lowcostnode;//��� ���� ����
        pq.pop();

        if (now == end)
            dest = true;
        if (d[now] < time) // �̹� �ִܰ�θ� üũ�� ����� ��� �н�
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