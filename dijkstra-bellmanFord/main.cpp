// I can reuse the code in BFS and DFS to creat a graph
//and priority tree should be build based on array and binary tree
#include "graph.hpp"
#include <iostream>
int main()
{
  Graph graph1;
  graph1.setGraphType(directed);
  if(!(graph1.addEdge(1,2,16) && graph1.addEdge(1,6,4)&&
      graph1.addEdge(1,5,8)&& graph1.addEdge(2,3,2)&&
      graph1.addEdge(4,3,6)&& graph1.addEdge(4,2,5)&&
      graph1.addEdge(5,2,7)&&graph1.addEdge(5,4,1)&&
      graph1.addEdge(6,5,3))
  )
  {
    cout<<"Add edge error!\n";
    exit(-1);
  }
  graph1.dijkstra(1);

  Graph graph2;
  graph2.setGraphType(directed);
  if(!(graph2.addEdge(1,2,6) && graph2.addEdge(1,5,7)&&
      graph2.addEdge(2,3,5)&& graph2.addEdge(3,2,-2)&&
      graph2.addEdge(2,4,-4)&& graph2.addEdge(2,5,8)&&
      graph2.addEdge(4,1,2)&&graph2.addEdge(4,3,7)&&
      graph2.addEdge(5,3,-3)&&graph2.addEdge(5,4,9))
  )
  {
    cout<<"Add edge error!\n";
    exit(-1);
  }
  graph2.bellmanFord(1);
  return 0;
}
