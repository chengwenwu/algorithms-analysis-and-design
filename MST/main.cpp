// I can reuse the code in BFS and DFS to creat a graph
//and priority tree should be build based on array and binary tree
#include "pritree.hpp"
#include "pritree.cpp"
int main()
{
  Pritree<char> pritree;
  pritree.insert('a');
  pritree.insert('d');
  pritree.insert('e');
  pritree.insert('T');
  pritree.insert('c');
  pritree.insert('C');
  pritree.insert('H');
  pritree.insert('G');
  pritree.insert('Y');
  pritree.insert('H');
  pritree.insert('G');
  pritree.insert('Y');
  for(int counter = 0; counter < 15; counter++)
  {
      cout<<pritree.popHead()<<" ";
  }
  cout<<endl;
  return 0;
}
