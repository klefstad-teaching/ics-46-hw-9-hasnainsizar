#include "dijkstras.h"
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> distances(n, INF);
    vector<bool> visited(n, false);

    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b){return a.second > b.second;};
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

    distances[source] = 0;
    pq.push({source, 0});

    while (!pq.empty()){
        int u = pq.top().first;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({v,distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    for (int v = destination; v!= -1; v = previous[v]){path.push_back(v);}
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for (int i : v){cout << i << " ";}
    cout << "\nTotal cost is " << total << endl;
}
