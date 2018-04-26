#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Graph.h"
#include "Graph.cpp"
#include "BinaryHeap.cpp"
#include "BinomialHeap.cpp"
#include "FibonacciHeap.cpp"

using namespace std;

int main()
{
	char Random;
	int V, start, stop, source, n, edges, rangeStart, rangeEnd;
	float avg_deg;
	do
	{
		cout<<"Enter R for Random Graph generation and S for specified Graph Input"<<endl;
		cin>>Random;
	}while(Random != 'R' && Random != 'r' && Random != 'S' && Random != 's');

	if(Random == 'R' || Random == 'r')
	{
		cout << "Enter the number of vertices in the graph : ";
		cin >> V;
		Graph g(V);
		cout << "Enter the source vertex : ";
		cin >> source;
		cout<< "Enter the average degree: ";
		cin>>avg_deg;
		cout<<"Enter the range start and range end: ";
		cin>>rangeStart>>rangeEnd;
		edges = (int)(avg_deg * V);
		map<pair<int,int>,int>m;
		cout<<"Edge number "<<edges<<endl;
		cout<<"Edges are: "<<endl;
		for(int i = 0; i < edges; i++)
		{
			srand (time(NULL));
			int random_number = -1;
			while(random_number == -1)
			{
				random_number =rand()%(V*V);
				if(m[make_pair(random_number/V,random_number%V)] || random_number/V == random_number%V)
					random_number = -1;
				else
				{
					int weight = rand()%(rangeEnd - rangeStart) + rangeStart;
					m[make_pair(random_number/V,random_number%V)] = 1;
					cout<<random_number/V<<" - "<<random_number%V<<": "<<weight<<endl;
					g.addEdge(random_number/V, random_number%V, weight);
				}
			}
		}
  
		cout << "-----BINARY HEAPS-----" << endl;
		start = clock();
		g.primMST(source, BINARY);
		stop = clock();
		cout << "Execution time using Binary Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

		cout << "-----BINOMIAL HEAPS-----" << endl;
		start = clock();
		g.primMST(source, BINOMIAL);
		stop = clock();
		cout << "Execution time using Binomial Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

		cout << "-----FIBONACCI HEAPS-----" << endl;
		start = clock();
		g.primMST(source, FIBONACCI);
		stop = clock();
		cout << "Execution time using Fibonacci Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
	}

	else
	{
		ifstream fin;
		fin.open("input2.txt", ios::in);
		fin >> V;
		Graph g(V);
		fin >> source;
		for (int i = 0; i < V; i++)
		{
			fin >> n;
			assert(n < V);
			for (int j = 0; j < n; j++)
			{
				int u, w;
				fin >> u >> w;
				assert(u < V && w >= 0);
				g.addEdge(i, u, w);
			}
		}

		fin.close();
    
		cout << "-----BINARY HEAPS-----" << endl;
		start = clock();
		g.primMST(source, BINARY);
		stop = clock();
		cout << "Execution time using Binary Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

		cout << "-----BINOMIAL HEAPS-----" << endl;
		start = clock();
		g.primMST(source, BINOMIAL);
		stop = clock();
		cout << "Execution time using Binomial Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

		cout << "-----FIBONACCI HEAPS-----" << endl;
		start = clock();
		g.primMST(source, FIBONACCI);
		printf("HEllo");		
		stop = clock();
		cout << "Execution time using Fibonacci Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
	}
	return 0;
}
