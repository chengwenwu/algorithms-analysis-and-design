#include <iostream>
#include <limits.h>
#include <queue>
#define MAX_SIZE 10
using namespace std;

enum{white,black,gray};
int W[MAX_SIZE][MAX_SIZE];//这个矩阵存放权值
int parent[MAX_SIZE];//这里面是各个节点的父节点
int color[MAX_SIZE];
int num = 0;//这个是真正的权值矩阵的大小

void reset()
{
  for(int i = 0; i < MAX_SIZE; i++)
  {
    parent[i] = -1;
    color[i] = white;
  }
}
/*
@fromId:边的起始顶点Id
@toId:边指向的顶点Id
@weight:边上的权值
这里顶点Id必须是从0开始的依次递增的数字，并且顶点编号必须连续，不能跳过某一个数字
*/
bool addEdge(int fromId, int toId, int weight)
{
  if(fromId >= MAX_SIZE || fromId < 0 || toId >= MAX_SIZE || toId < 0)
    return false;
  if(fromId > num)
    num = fromId;
  if(toId > num)
    num = toId;
  W[fromId][toId] = weight;
  return true;
}

void bfs(int source)//会更新父节点数组
{
  reset();
  queue<int> que;
  que.push(source);
  while(que.size() != 0)
  {
    int head = que.front();
    color[head] = black;
    que.pop();
    for(int i = 0; i < num; i++)//遍历它的每一个邻居节点
    {
      if(W[head][i] != 0 && color[i] == white)//判断有没有路径，如果有在判断是不是白色节点
      {
        color[i] = gray;
        que.push(i);
        parent[i] = head;
      }
    }

  }
}

int fordFulkerson(int source, int sink)
{
  int maxFlow = 0;
  bfs(source);
  while(parent[sink] != -1)
  {
    //找到该路径中容量最小的边
    int capacity = INT_MAX;
    int tempV = sink;
    while(tempV != source)
    {
      int tempP = parent[tempV];
      if(W[tempP][tempV] < capacity)
        capacity = W[tempP][tempV];
      tempV = tempP;
    }
    maxFlow += capacity;
    //更新残余网络
    tempV = sink;
    while(tempV != source)
    {
      int tempP = parent[tempV];
      W[tempP][tempV] -= capacity;
      tempV = tempP;
    }

    bfs(source);
  }
  return maxFlow;
}

int main()
{
  //首先初始化权值矩阵以及父节点
  for(int i = 0; i < MAX_SIZE; i++)
  {
    parent[i] = -1;
    color[i] = white;
    for(int j = 0; j < MAX_SIZE; j++)
        W[i][j] = 0;
  }
  //建立一个图
  if(!(
    addEdge(0,1,10)&&addEdge(0,5,10)
    &&addEdge(1,2,4)&&addEdge(1,4,8)
    &&addEdge(1,5,2)&&addEdge(2,3,10)
    &&addEdge(4,2,6)&&addEdge(4,3,10)
    &&addEdge(5,4,9)
  ))
  {
    cout<<"Add Edge Error\n";
    return -1;
  }
  //因为建图过程中size是最大的顶点编号，所以正真顶点数需要加一
  num++;
  cout<<"Max flow is "<<fordFulkerson(0,3);

  return 0;
}
