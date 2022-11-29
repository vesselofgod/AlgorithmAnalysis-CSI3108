// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#define INF 1e9
#define MAX 10000000

using namespace std;

string result = "result.txt";
ofstream writeFile(result.data());
int max_scr;
int max_dst;
int max_dist = 0;

class Graph {
    protected:
        int V;
        vector<pair<int, int>>* adj;

    public:
        Graph(int V);
        void addEdge(int u, int v, int w);
        void shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V){
	this->V = V;
	adj = new vector<pair<int, int>>[V];
}

void Graph::addEdge(int u, int v, int w){
	adj[u].push_back(make_pair(v, w));
}

void Graph::shortestPath(int src)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	vector<int> dist(V, INF);
    dist[src] = 0;
	pq.push(make_pair(0, src));

	while (pq.empty()==0) {
		int u = pq.top().second;
		pq.pop();

		for (int i = 0; i<adj[u].size(); ++i) {
			int v = adj[u][i].first;
			int weight = adj[u][i].second;
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	for (int i = 0; i < V; ++i){
        if(dist[i]>max_dist && dist[i]!=INF){
            max_scr = src;
            max_dst = i;
            max_dist = dist[i];
        }
    }
}

int main()
{
	int V = 32000;
	Graph g(V);

    int numbers[3];
    int idx = 0;

    string filename("32000.graph");
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
        }
        idx++;
    }
    input_file.close();

    for(int i=0; i<V;i++){
        g.shortestPath(i);
        cout<<"current scr vertex : "<<i<<", current longest path's length : "<<max_dist<<"\n";
    }

    writeFile<<max_scr<<" "<<max_dst<<" "<<max_dist<<"\n";
    writeFile.close();
	return 0;
}