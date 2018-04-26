#include "Graph.h"
#include "BinaryHeap.h"
#include "BinomialHeap.h"
#include "FibonacciHeap.h"
#include "Heap.h"
#define INF 0x3f3f3f3f

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<pair<int, int> > [V];
}

void Graph::addEdge(int u,int v,int w)
{
    adj[u].push_back(make_pair(v,w));
   adj[v].push_back(make_pair(u,w));
}

void Graph::primMST(int src, int heap_type)
{
    Heap *heap;
    switch(heap_type)
    {
        case BINARY: heap = new BinaryHeap(); break;
        case BINOMIAL: heap = new BinomialHeap(); break;
        case FIBONACCI: heap = new FibonacciHeap(); break;
    }

    vector<int> key(V,INF);
    vector<int> parent(V,-1);
    vector<bool> inMST(V,false);
    key[0] = 0;
parent[0] = -1;
    (*heap).push(make_pair(0, src));
    key[src] = 0;

    while((*heap).top() != make_pair(-1, -1))
    {
        int u = (*heap).top().second;
        (*heap).pop();

        inMST[u] = true;
        list<pair<int,int> >::iterator it;
        for(it = adj[u].begin();it!=adj[u].end();it++)
        {
            int v = (*it).first;
            int weight = (*it).second;

            if(!inMST[v] && key[v] > weight)
            {
                key[v] = weight;
                (*heap).push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    printf("Edge \t Weight\n");
    for(int i=1;i<V;i++)
    {
        cout << parent[i] << " - "  << i << " - " << key[i] << endl;
    }

    printf("Number of Operations performed : %d \n", (*heap).getOperations());
    return;
}

