#include <bits/stdc++.h>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

enum HeapType {BINARY, BINOMIAL, FIBONACCI};

class Graph
{
    private:
        int V;
        list< pair<int, int> > *adj;
    public:
        Graph(int V);
        void addEdge(int u, int v, int w);
        void primMST(int s,int heap_type);
};

#endif // GRAPH_H

