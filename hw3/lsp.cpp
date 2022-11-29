// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include <iostream>
#include <queue>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;
#define INF 0x3f3f3f3f
#define MAX 10000000


string result = "result.txt";
ofstream writeFile(result.data());
int max_scr;
int max_dst;
int max_dist = 0;

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

// This class represents a directed graph using
// adjacency list representation
class Graph {
	int V; // # of vertices

	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	list<pair<int, int> >* adj;

public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int u, int v, int w);

	// prints shortest path from s
	void shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
	// Create a priority queue to store vertices that
	// are being preprocessed. This is weird syntax in C++.
	// Refer below link for details of this syntax
	priority_queue<iPair, vector<iPair>, greater<iPair> >
		pq;

	// Create a vector for distances and initialize all
	// distances as infinite (INF)
	vector<int> dist(V, INF);

	// Insert source itself in priority queue and initialize
	// its distance as 0.
	pq.push(make_pair(0, src));
	dist[src] = 0;

	/* Looping till priority queue becomes empty (or all
	distances are not finalized) */
	while (!pq.empty()) {
		// The first vertex in pair is the minimum distance
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted distance (distance must be first item
		// in pair)
		int u = pq.top().second;
		pq.pop();

		// 'i' is used to get all adjacent vertices of a
		// vertex
		list<pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {
			// Get vertex label and weight of current
			// adjacent of u.
			int v = (*i).first;
			int weight = (*i).second;

			// If there is shorted path to v through u.
			if (dist[v] > dist[u] + weight) {
				// Updating distance of v
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	// Print shortest distances stored in dist[]
	for (int i = 0; i < V; ++i){
        if(dist[i]>max_dist){
            max_scr = src;
            max_dst = i;
            max_dist = dist[i];
        }
        // writeFile <<src<<" to "<< i<<" : "<<dist[i]<<"\n";
		//printf("%d \t\t %d\n", i, dist[i]);
    }

}


// Driver program to test methods of graph class
int main()
{

	// create the graph given in above figure
	int V = 16000;
	Graph g(V);

    int numbers[3];
    int idx = 0;

    string filename("16000.graph");
    int number;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file >> number) {
        numbers[idx%3] = number;
        if(idx%3==2){
            g.addEdge(numbers[0], numbers[1], numbers[2]);
            writeFile<<numbers[0]<<" "<<numbers[1]<<" "<<numbers[2]<<"\n";
        }
        idx++;
    }
    input_file.close();

    /*
    for(int i=0; i<V;i++){
        cout<<i<<"th Vertex Distance from Source : "<<max_dist<<"\n";
        g.shortestPath(i);
    }
    */
    writeFile<<max_scr<<" "<<max_dst<<" "<<max_dist<<"\n";
    writeFile.close();
	return 0;
}
