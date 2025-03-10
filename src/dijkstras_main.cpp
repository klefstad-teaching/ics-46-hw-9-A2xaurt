//dijkstras_main.cpp
#include "dijkstras.h"

int main()
{
    Graph G;
    file_to_graph("src/small.txt",G);
    vector<int> previous(G.numVertices);
    vector<int> distances=dijkstra_shortest_path(G,0,previous);
    for(int i=0; i<G.numVertices; ++i)
    {
        vector<int> shortest_path=extract_shortest_path(distances,previous,i);
        print_path(shortest_path,distances[i]);
    }
}