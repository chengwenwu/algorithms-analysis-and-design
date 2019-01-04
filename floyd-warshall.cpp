#include <iostream>
#include <algorithm>
#include <limits.h>
#include <string.h>
#define MAX_SIZE 10
using namespace std;
int W[MAX_SIZE][MAX_SIZE];//这个矩阵存放权值
int size = 0;//这个是真正的权值矩阵的大小
int** D = NULL;//这个存放最后计算的结果

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
  if(fromId > size)
    size = fromId;
  if(toId > size)
    size = toId;
  W[fromId][toId] = weight;
  return true;
}

void floydWarshall()
{
  size++;
  //为D和D0申请存储空间
  int** D0 = NULL;
  D = new int*[size];
  D0 = new int*[size];
  for(int i = 0; i < size; i++)
  {
    D[i] = new int[size];
    D0[i] = new int[size];
  }
  //初始化D0
  for(int i = 0; i <size; i++)
  {
    for(int j=0; j < size; j++)
      D0[i][j] = W[i][j];
  }
  //核心算法
  for(int k = 0; k < size; k++)
  {
    for(int i = 0; i <size; i++)
    {
      for(int j=0; j < size; j++)
      {
        int temp = D0[i][k] + D0[k][j];
        if(D0[i][k] == INT_MAX || D0[k][j] == INT_MAX)
          temp = INT_MAX;
        D[i][j]  = min(D0[i][j], temp);
      }
    }
    for(int i = 0; i <size; i++)
    {
      for(int j=0; j < size; j++)
        D0[i][j] = D[i][j];
    }
  }
  //释放D0的存储空间
  if(D0 == NULL)
  {
    for(int i = 0; i < size; i++)
      delete[]D0[i];
    delete[]D0;
  }

}

int main()
{
  //首先初始化权值矩阵
  for(int i = 0; i < MAX_SIZE; i++)
  {
    for(int j = 0; j < MAX_SIZE; j++)
    {
      if(i == j)
        W[i][j] = 0;
      else
        W[i][j] = INT_MAX;
    }
  }
  //建立一个图
  if(!(
    addEdge(0,1,3)&&addEdge(0,2,8)
    &&addEdge(0,4,-4)&&addEdge(1,3,1)
    &&addEdge(1,4,7)&&addEdge(2,1,4)
    &&addEdge(3,2,-5)&&addEdge(3,0,2)
    &&addEdge(4,3,6)
  ))
  {
    cout<<"Add Edge Error\n";
    return -1;
  }

  floydWarshall();

  //输出最后的结果
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
      cout<<D[i][j]<<"  ";
    cout<<endl;
  }
  //如果使用了D，这里必须释放D
  if(D != NULL)
  {
    for(int i = 0; i < size; i++)
      delete[]D[i];
    delete []D;
  }
  return 0;
}
