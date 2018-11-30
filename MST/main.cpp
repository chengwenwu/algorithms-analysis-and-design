// I can reuse the code in BFS and DFS to creat a graph
//and priority tree should be build based on array and binary tree
#include "graph.hpp"
#include <iostream>
int main()
{
  Graph graph;
	graph.setGraphType(directed);
	if(!(graph.addEdge(1,2) && graph.addEdge(2,3)&&
			graph.addEdge(3,1)&& graph.addEdge(2,4)&&
			graph.addEdge(5,1)&& graph.addEdge(5,6)&&
			graph.addEdge(5,7)&&graph.addEdge(7,6))
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
  cout<<endl;
	graph.stronglyConnectCompents(1);

  Graph graph1;
	graph1.setGraphType(undirected);
	if(!(graph1.addEdge(1,2,9) && graph1.addEdge(1,4,1)&&
			graph1.addEdge(2,3,3)&& graph1.addEdge(2,5,4)&&
			graph1.addEdge(2,6,3)&& graph1.addEdge(3,6,12)&&
      graph1.addEdge(3,5,1)&&graph1.addEdge(3,4,5)&&
      graph1.addEdge(4,7,8)&&graph1.addEdge(5,9,6)&&
      graph1.addEdge(6,7,5)&&graph1.addEdge(6,8,2)&&
      graph1.addEdge(7,8,2)&&graph1.addEdge(8,9,1))
  )
	{
		cout<<"Add edge error!\n";
		exit(-1);
	}
  cout<<"\nprim:\n";
  graph1.prim(1);
  cout<<"\nkruskal: \n";
  graph1.kruskal();
  return 0;
}
