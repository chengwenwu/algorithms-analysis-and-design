#include "bfs.hpp"
#include <iostream>
using namespace std;
int main()
{
	Graph graph;
	graph.setGraphType(undirected);
	if(!(graph.addEdge(1,2) && graph.addEdge(1,5)&&
			graph.addEdge(2,3)&& graph.addEdge(2,4)&&
			graph.addEdge(2,5)&& graph.addEdge(3,4)&&
			graph.addEdge(4,5))
	)
	{
		cout<<"Add edge error!\n";
		exit(-1);
	}
	if(!graph.bfs(1))
		cout<<"BFS Error\n";
	if(!graph.dfs(1))
		cout<<"DFS Error\n";
	graph.TopologicalSort();
	graph.stronglyConnectCompents(1);
	return 0;
}