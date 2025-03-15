#include "dijkstras.h"
#include <algorithm>


int main()
{
    Graph G;
    string filename;
    cout << "Enter graph file name: ";
    cin >> filename;

    file_to_graph(filename, G);

    int source = 0;
    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int i = 0; i < G.numVertices; ++i){
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }
    return 0;
}