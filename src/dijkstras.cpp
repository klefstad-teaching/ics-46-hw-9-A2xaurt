//dijkstras.cpp
#include "dijkstras.h"

void print_path(const vector<int> &v, int total)
{
    for(int i : v)
        cout<<i<<' ';
    cout<<endl<<"Total cost is "<<total<<endl;
}

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous)
{
    int numVertices=G.size();
    vector<int> distances(numVertices,INF);
    vector<bool> visited(numVertices,false);
    distances[source]=0;
    previous[source]=UNDEFINED;
    priority_queue<pair<int,int>> minHeap;
    minHeap.push({source,0});
    while(!minHeap.empty())
    {
        int u=minHeap.top().first;
        minHeap.pop();
        if(visited[u])
            continue;
        visited[u]=true;
        for(Edge edge : G[u])
        {
            int v=edge.dst;
            int weight=edge.weight;
            if(!visited[v]&&distances[u]+weight<distances[v])
            {
                distances[v]=distances[u]+weight;
                previous[v]=u;
                minHeap.push({v,distances[v]});
            }
        }
    }
    return distances;
}